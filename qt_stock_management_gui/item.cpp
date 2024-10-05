#include "item.h"

Item::Item(QString b, QString d, int s, double p): barcode(b), description(d), stock(s), price(p)
{
    barcode.truncate(13);
    description.truncate(20);
}

bool Item::isValidBarcode(QString b) {
    bool ok;
    int bInt = b.toInt(&ok);
    return ok && (bInt > 0);
}

QString Item::getBarcode() const {
    return barcode;
}

QString Item::getDescription() const {
    return description;
}

double Item::getPrice() const {
    return price;
}

int Item::getStock() const {
    return stock;
}

void Item::setStock(int s) {
    stock = s;
}

void Item::setBarcode(QString b)
{
    barcode = b;
}

void Item::setDescription(QString d)
{
    description = d;
}

void Item::setPrice(double p)
{
    price = p;
}

QString Item::toString() const {
    return QString("%1\t%2\t%3\t%4").arg(barcode, 13).arg(description, 20).arg(stock, 5).arg(price, 8, 'f', 2);
}
