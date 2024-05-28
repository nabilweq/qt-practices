#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <tuple>
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

        // Create the scroll area and a widget to hold the product cards
        QScrollArea *scrollArea = new QScrollArea(this);
        QWidget *scrollWidget = new QWidget();
        QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);

        scrollWidget->setLayout(scrollLayout);
        scrollArea->setWidget(scrollWidget);
        scrollArea->setWidgetResizable(true);
        scrollArea->setStyleSheet("background-color: lightblue;");

        // Create the cart list and set a background color
        cartList = new QListWidget(this);
        cartList->setStyleSheet("background-color: lightgreen;");

        QLabel *totalLabel = new QLabel("Total: $0.00", this);

        QPushButton *checkoutButton = new QPushButton("Checkout", this);

        productLayout->addWidget(scrollArea);
        productLayout->addLayout(cartLayout);

        cartLayout->addWidget(cartList);
        cartLayout->addWidget(totalLabel);
        cartLayout->addWidget(checkoutButton);

        mainLayout->addLayout(productLayout);

        // Connect signals and slots
        connect(checkoutButton, &QPushButton::clicked, this, &OdooPOSWindow::checkout);

        // Load products
        loadProducts(scrollLayout);
    }

private slots:
    void addToCart(const QString &productName, const QString &productPrice) {
        cartList->addItem(productName + " - " + productPrice);
        cartList->setStyleSheet("background-color: red;");
        updateTotal();
    }

    void checkout() {
        cartList->clear();
        updateTotal();
    }

private:
    QListWidget *cartList;

    void loadProducts(QVBoxLayout *scrollLayout) {
        // Example list of products with images
        QList<std::tuple<QString, QString, QString>> products = {
            {"Product 1", "$10.00", "./assets/images/1.jpg"},
            {"Product 2", "$20.00", "./assets/images/1.jpg"},
            {"Product 3", "$30.00", "./assets/images/1.jpg"},
            {"Product 4", "$40.00", "./assets/images/1.jpg"},
            {"Product 5", "$50.00", "./assets/images/1.jpg"}
        };

        // Add product cards to the scroll layout
        for (const auto &product : products) {
            ProductCard *card = new ProductCard(std::get<0>(product), std::get<1>(product), std::get<2>(product), this);
            scrollLayout->addWidget(card);

            connect(card, &ProductCard::addToCart, this, &OdooPOSWindow::addToCart);
        }
    }

    void updateTotal() {
        // Example implementation to update the totalprice
        int itemCount = cartList->count();
        double totalPrice = 0.00;

        for (int i = 0; i < itemCount; ++i) {
            QString itemText = cartList->item(i)->text();
            QString priceText = itemText.split(" - ").last();
            totalPrice += priceText.mid(1).toDouble();
        }

        QLabel *totalLabel = findChild<QLabel *>();
        totalLabel->setText(QString("Total: $%1").arg(totalPrice, 0, 'f', 2));
    }
};

#include "main.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    OdooPOSWindow window;
    window.show();

    return app.exec();
}
