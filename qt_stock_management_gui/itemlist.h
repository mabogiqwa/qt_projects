#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QWidget>
#include <QMap>
#include <QFile>
#include <QTextStream>
#include "item.h"

class ItemList : public QWidget
{
    Q_OBJECT
public:
    explicit ItemList(QWidget *parent = nullptr);
    void addItem(Item *someItem);
    void removeItem(QString itemKey);
    void addItemsFromFile(const QString filename);
    void saveItemsIntoFile(const QString filename);
    QStringList getStringList() const;
    bool searchForBarcode(QString barcode);
    const QMap<QString, Item*>& getItemData() const;
    Item* searchForItem(QString barcode);
signals:

private:
    QMap<QString, Item*> itemData;
    QStringList barcodeList;

};

#endif // ITEMLIST_H
