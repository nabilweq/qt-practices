#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fetchProductsButton_clicked();
    void on_checkoutButton_clicked();
    void handleProductResponse(QNetworkReply *reply);
    void handleCheckoutResponse(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QJsonArray products;
};

#endif
