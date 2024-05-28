#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        QStackedWidget *stackedWidget = new QStackedWidget(this);
        
        // First Page
        QWidget *page1 = new QWidget();
        QVBoxLayout *page1Layout = new QVBoxLayout(page1);
        QLabel *label1 = new QLabel("This is Page 1");
        QPushButton *goToPage2Button = new QPushButton("Go to Page 2");
        page1Layout->addWidget(label1);
        page1Layout->addWidget(goToPage2Button);

        // Second Page
        QWidget *page2 = new QWidget();
        QVBoxLayout *page2Layout = new QVBoxLayout(page2);
        QLabel *label2 = new QLabel("This is Page 2");
        QPushButton *goToPage1Button = new QPushButton("Go to Page 1");
        page2Layout->addWidget(label2);
        page2Layout->addWidget(goToPage1Button);

        // Add pages to stacked widget
        stackedWidget->addWidget(page1);
        stackedWidget->addWidget(page2);

        setCentralWidget(stackedWidget);

        // Connect buttons to switch pages
        connect(goToPage2Button, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentWidget(page2);
        });

        connect(goToPage1Button, &QPushButton::clicked, [=]() {
            stackedWidget->setCurrentWidget(page1);
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

#include "main.moc"
