#ifndef PRODUCTCARD_H
#define PRODUCTCARD_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFrame>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class ProductCard : public QFrame {
    Q_OBJECT

public:
    explicit ProductCard(const QString &productName, const QString &productPrice, const QString &productImage, QWidget *parent = nullptr);

signals:
    void addToCart(const QString &productName, const QString &productPrice);

private slots:
    void onImageDownloaded(QNetworkReply *reply);

private:
    QLabel *imageLabel;
    QLabel *nameLabel;
    QLabel *priceLabel;
    QPushButton *addButton;
    QNetworkAccessManager *manager;
};

#endif // PRODUCTCARD_H
