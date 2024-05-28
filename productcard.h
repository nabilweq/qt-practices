#ifndef PRODUCTCARD_H
#define PRODUCTCARD_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class ProductCard : public QWidget {
    Q_OBJECT

public:
    ProductCard(const QString &productName, const QString &productPrice, const QString &productImage, QWidget *parent = nullptr);

signals:
    void addToCart(const QString &productName, const QString &productPrice);

private:
    QLabel *nameLabel;
    QLabel *priceLabel;
    QLabel *imageLabel;
    QPushButton *addButton;
};

#endif // PRODUCTCARD_H
