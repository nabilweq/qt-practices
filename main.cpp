#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "productcard.h"

class OdooPOSWindow : public QMainWindow {
    Q_OBJECT

public:
    OdooPOSWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        QHBoxLayout *productLayout = new QHBoxLayout();
        QVBoxLayout *cartLayout = new QVBoxLayout();

        QScrollArea *scrollArea = new QScrollArea(this);
        scrollArea->setWidgetResizable(true);
        scrollArea->setStyleSheet("background-color: lightblue;");

        scrollWidget = new QWidget();
        scrollLayout = new QVBoxLayout(scrollWidget);
        scrollArea->setWidget(scrollWidget);

        cartList = new QListWidget(this);
        cartList->setStyleSheet("background-color: white; color: black");

        totalLabel = new QLabel("Total: $0.00", this);
        checkoutButton = new QPushButton("Checkout", this);

        productLayout->addWidget(scrollArea);
        productLayout->addLayout(cartLayout);

        cartLayout->addWidget(cartList);
        cartLayout->addWidget(totalLabel);
        cartLayout->addWidget(checkoutButton);

        // Set size policy and stretching for productLayout
        // productLayout->setSpacing(20); // Set spacing between widgets
        // productLayout->setContentsMargins(20, 20, 20); // Set margins around the layout

        mainLayout->addLayout(productLayout);

        // Connect signals and slots
        connect(checkoutButton, &QPushButton::clicked, this, &OdooPOSWindow::checkout);

        // Initialize network manager
        manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, &OdooPOSWindow::onNetworkReply);

        loadProducts();
    }

private slots:
    void addToCart(const QString &productName, const QString &productPrice) {
        cartList->addItem(productName + " - " + productPrice);
        updateTotal();
    }

    void checkout() {
        cartList->clear();
        updateTotal();
    }

    void onNetworkReply(QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
            QJsonArray jsonArray = json_doc.array();

            int productCount = 0;
            QHBoxLayout *currentRowLayout = nullptr;
            QWidget *currentRowWidget = nullptr;

            for (const QJsonValue &value : jsonArray) {
                if (productCount >= 20) {
                    break;
                }

                QJsonObject productObject = value.toObject();
                QString title = productObject["title"].toString();
                QString price = QString::number(productObject["id"].toInt()) + ".00";
                QString imageUrl = productObject["url"].toString();

                ProductCard *card = new ProductCard(title, price, imageUrl, this);
                connect(card, &ProductCard::addToCart, this, &OdooPOSWindow::addToCart);

                card->setFixedSize(200, 300);

                if (productCount % 3 == 0) {
                    currentRowWidget = new QWidget();
                    currentRowLayout = new QHBoxLayout(currentRowWidget);
                    scrollLayout->addWidget(currentRowWidget);
                }

                currentRowLayout->addWidget(card);

                ++productCount;
            }
        } else {
            qWarning() << "Network error: " << reply->errorString();
        }
        reply->deleteLater();
    }

    void updateTotal() {
        double totalPrice = 0.00;

        for (int i = 0; i < cartList->count(); ++i) {
            QString itemText = cartList->item(i)->text();
            QString priceText = itemText.split(" - ").last();
            totalPrice += priceText.toDouble();
        }

        totalLabel->setText(QString("Total: $%1").arg(totalPrice, 0, 'f', 2));
    }

    void loadProducts() {
        QUrl url("https://jsonplaceholder.typicode.com/photos/"); // Sample url to fetch dummy data
        qDebug() << "Requesting products from URL:" << url.toString();
        QNetworkRequest request(url);
        manager->get(request);
    }

private:
    QListWidget *cartList;
    QLabel *totalLabel;
    QPushButton *checkoutButton;
    QWidget *scrollWidget;
    QVBoxLayout *scrollLayout;
    QNetworkAccessManager *manager;
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OdooPOSWindow window;
    window.show();

    return app.exec();
}
