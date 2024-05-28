#include "productcard.h"
#include <QPixmap>

ProductCard::ProductCard(const QString &productName, const QString &productPrice, const QString &productImage, QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    imageLabel = new QLabel(this);
    QPixmap pixmap(productImage);
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));

    nameLabel = new QLabel(productName, this);
    nameLabel->setStyleSheet("color: black;"); // Set text color to black
    priceLabel = new QLabel(productPrice, this);
    priceLabel->setStyleSheet("color: black;"); // Set text color to black
    addButton = new QPushButton("Add to Cart", this);

    layout->addWidget(imageLabel);
    layout->addWidget(nameLabel);
    layout->addWidget(priceLabel);
    layout->addWidget(addButton);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, [=]() {
        emit addToCart(productName, productPrice);
    });
}
