#include "productcard.h"
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

ProductCard::ProductCard(const QString &productName, const QString &productPrice, const QString &productImage, QWidget *parent)
    : QFrame(parent), manager(new QNetworkAccessManager(this)) {
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setStyleSheet("background-color: white; border-radius: 12px; padding: 12px;");

    QVBoxLayout *layout = new QVBoxLayout(this);

    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setFixedSize(145, 145);
    layout->addWidget(imageLabel);

    nameLabel = new QLabel(productName, this);
    nameLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: grey;");
    nameLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(nameLabel);

    priceLabel = new QLabel(productPrice, this);
    priceLabel->setStyleSheet("font-size: 12px; color: green;");
    priceLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(priceLabel);

    addButton = new QPushButton("Add to Cart", this);
    addButton->setStyleSheet("background-color: red; color: white; padding: 4px;");
    layout->addWidget(addButton);

    setLayout(layout);

    connect(addButton, &QPushButton::clicked, this, [=]() {
        emit addToCart(productName, productPrice);
    });

    connect(manager, &QNetworkAccessManager::finished, this, &ProductCard::onImageDownloaded);

    QUrl imageUrl(productImage);
    qDebug() << "Requesting required image from URL:" << imageUrl.toString();
    QNetworkRequest request(imageUrl);
    manager->get(request);
}

void ProductCard::onImageDownloaded(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray imageData = reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(imageData);
        imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
    } else {
        qWarning() << "Image downloading error: " << reply->errorString();
        imageLabel->setText("Image not found");
    }
    reply->deleteLater();
}
