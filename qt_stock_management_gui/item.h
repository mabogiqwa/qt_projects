#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{
private:
    QString barcode;
    QString description;
    int stock;
    double price;
public:
    Item(QString b, QString d, int s, double p);
    static bool isValidBarcode(QString b);
    QString getBarcode() const;
    QString getDescription() const;
    double getPrice() const;
    int getStock() const;
    void setStock(int s);
    void setBarcode(QString b);
    void setDescription(QString d);
    void setPrice(double p);
    QString toString() const;
};

#endif // ITEM_H
