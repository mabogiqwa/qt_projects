#include "itemlist.h"

ItemList::ItemList(QWidget *parent)
    : QWidget{parent}
{

}

void ItemList::addItem(Item *someItem)
{
    QString barcode = someItem->getBarcode();

    itemData.insert(barcode, someItem);
}

void ItemList::removeItem(QString itemKey)
{
    if (itemData.contains(itemKey))
    {
        Item* itemToBeDeleted = itemData[itemKey];

        delete itemToBeDeleted;

        itemData.remove(itemKey);
    }
}

void ItemList::addItemsFromFile(const QString filename)
{
    QFile file(filename); //Opens a file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList parts = line.split("\t");

        if (parts.size() == 4)
        {
            QString barcode = parts[0];
            barcodeList.append(barcode); //adds barcode to barcode list
            QString description = parts[1];
            int stockAmount = parts[2].toInt();
            double price = parts[3].toDouble();

            Item *someItem = new Item(barcode, description, stockAmount, price);

            itemData.insert(barcode, someItem);
        }
    }

    file.close();
}

const QMap<QString, Item*>& ItemList::getItemData() const {
    return itemData;
}

void ItemList::saveItemsIntoFile(const QString filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        for (auto it = itemData.begin(); it != itemData.end(); ++it)
        {
            Item *someItem = it.value();

            QString itemString = someItem->getBarcode() + "\t" +
                                 someItem->getDescription() + "\t" +
                                 QString::number(someItem->getStock()) + "\t" +
                                 QString::number(someItem->getPrice());

            out << itemString << Qt::endl;
        }
    }
}

QStringList ItemList::getStringList() const
{
    return barcodeList;
}

Item *ItemList::searchForItem(QString barcode)
{
    if (itemData.contains(barcode))
    {
        return itemData[barcode];
    } else {
        return nullptr;
    }
}
bool ItemList::searchForBarcode(QString barcode)
{
    bool barcodeExists;
    if (itemData.contains(barcode))
    {
        barcodeExists = true;

        return barcodeExists;
    } else {
        barcodeExists = false;

        return barcodeExists;
    }
}
