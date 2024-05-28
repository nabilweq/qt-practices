#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QScreen>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QUrl>

class MainWindow : public QWidget {
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setGeometry(100, 100, 400, 200); // Set window position and size (x, y, width, height)

        // Get the primary screen
        QScreen *primaryScreen = QGuiApplication::primaryScreen();

        // Calculate the center position of the window
        int screenWidth = primaryScreen->geometry().width();
        int screenHeight = primaryScreen->geometry().height();
        int windowWidth = frameGeometry().width();
        int windowHeight = frameGeometry().height();
        int x = (screenWidth - windowWidth) / 2;
        int y = (screenHeight - windowHeight) / 2;

        // Move the window to the center of the screen
        move(x, y);

        // Set background image
        setStyleSheet("background-image: url(./assets/images/1.jpg);");

        // Create layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Create and style the text field
        inputField = new QLineEdit(this);
        inputField->setPlaceholderText("Enter a number");
        inputField->setStyleSheet("background-color: white;");
        layout->addWidget(inputField);

        // Create and style the button
        button = new QPushButton("Send API Request", this);
        button->setStyleSheet("background-color: yellow; color: black;");
        layout->addWidget(button);

        // Connect the button's clicked signal to a custom slot
        connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

        // Setup network access manager
        manager = new QNetworkAccessManager(this);
        connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onNetworkReply);
    }

private slots:
    void onButtonClicked() {
        QString inputText = inputField->text();
        qDebug() << "Button clicked with input:" << inputText;

        bool ok;
        int number = inputText.toInt(&ok);
        if (!ok || number <= 0) {
            qDebug() << "Invalid number input.";
            return;
        }

        QUrl url(QString("https://jsonplaceholder.typicode.com/todos/%1").arg(number));
        QNetworkRequest request(url);
        manager->get(request);
    }

    void onNetworkReply(QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

            if (!json_doc.isNull() && json_doc.isObject()) {
                QJsonObject json_obj = json_doc.object();
                qDebug() << "Network response JSON:" << json_obj;

                // Assuming the JSON response has a field called "title"
                if (json_obj.contains("title") && json_obj["title"].isString()) {
                    QString buttonName = json_obj["title"].toString();
                    button->setText(buttonName);
                }
            } else {
                qDebug() << "Failed to create JSON doc.";
            }
        } else {
            qDebug() << "Network error:" << reply->errorString();
        }
        reply->deleteLater();
    }

private:
    QLineEdit *inputField;
    QPushButton *button;
    QNetworkAccessManager *manager;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}