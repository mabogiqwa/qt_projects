#include "mainwindow.h"
#include <QIODevice>
#include <QFile>
#include <QToolBar>
#include <QFileDialog>
#include <QTextEdit>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QSpinBox>
#include "changeitemdialog.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    textEdit = new QTextEdit(this);

    textEdit->setReadOnly(true);

    QString titles = "Barcode\t\tDescription\t\tStock\tPrice";

    textEdit->setPlainText(titles);

    setCentralWidget(textEdit);

    exitAction = new QAction("Exit");
    QIcon icon1("C:/Users/realm/OneDrive/Documents/QtProjects/icons/x.png");
    exitAction->setIcon(icon1);
    
    connect(exitAction,&QAction::triggered,[=](){
        QApplication::quit();
    });
    
    openAction = new QAction("Open");
    QIcon icon2("C:/Users/realm/OneDrive/Documents/QtProjects/icons/o.png");
    openAction->setIcon(icon2);

    saveAction = new QAction("Save");
    QIcon icon3("C:/Users/realm/OneDrive/Documents/QtProjects/icons/s.png");
    saveAction->setIcon(icon3);

    connect(openAction,&QAction::triggered,this,[=](){
        MainWindow::on_openButton_clicked();
    });

    addAction = new QAction("Add");
    QIcon icon4("C:/Users/realm/OneDrive/Documents/QtProjects/icons/a.png");
    addAction->setIcon(icon4);

    changeAction = new QAction("Change");
    QIcon icon5("C:/Users/realm/OneDrive/Documents/QtProjects/icons/c.png");
    changeAction->setIcon(icon5);

    removeAction = new QAction("Remove");
    QIcon icon6("C:/Users/realm/OneDrive/Documents/QtProjects/icons/r.png");
    removeAction->setIcon(icon6);

    connect(changeAction,&QAction::triggered,this,[=]() {
        MainWindow::on_changeButton_clicked();
    });
    
    //Add menubar
    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    QMenu *fileMenu2 = menuBar()->addMenu("Edit");
    fileMenu2->addAction(addAction);
    fileMenu2->addAction(changeAction);
    fileMenu2->addAction(removeAction);

    QObject::connect(addAction, &QAction::triggered, this, [=](){
        MainWindow::on_addButton_clicked();
    });

    QObject::connect(removeAction, &QAction::triggered, this, [=](){
        MainWindow::on_removeButton_clicked();
    });

    QObject::connect(saveAction, &QAction::triggered, this, [=](){
            MainWindow::on_saveButton_clicked();
    });

    //QPushButton *openButton = new QPushButton("Open",this);
    QLabel *label1 = new QLabel; //Label used to store open picture
    QPixmap pix("C:/Users/realm/OneDrive/Documents/QtProjects/icons/o.png");
    label1->setPixmap(pix.scaled(30,30,Qt::KeepAspectRatio));
    //The block of code above adds the O picture inside the main window

    QLabel *label2 = new QLabel;
    QPixmap pix2("C:/Users/realm/OneDrive/Documents/QtProjects/icons/s.png");
    label2->setPixmap(pix2.scaled(30,30,Qt::KeepAspectRatio));

    QLabel *label3 = new QLabel;
    QPixmap pix3("C:/Users/realm/OneDrive/Documents/QtProjects/icons/x.png");
    label3->setPixmap(pix3.scaled(30,30,Qt::KeepAspectRatio));

    QLabel *label4 = new QLabel;
    QPixmap pix4("C:/Users/realm/OneDrive/Documents/QtProjects/icons/a.png");
    label4->setPixmap(pix4.scaled(30,30,Qt::KeepAspectRatio));

    QLabel *label5 = new QLabel;
    QPixmap pix5("C:/Users/realm/OneDrive/Documents/QtProjects/icons/c.png");
    label5->setPixmap(pix5.scaled(30,30,Qt::KeepAspectRatio));

    QLabel *label6 = new QLabel;
    QPixmap pix6("C:/Users/realm/OneDrive/Documents/QtProjects/icons/r.png");
    label6->setPixmap(pix6.scaled(30,30,Qt::KeepAspectRatio));

    QToolBar *fileToolBar = addToolBar(tr("File"));
    fileToolBar->addWidget(label1);
    fileToolBar->addSeparator();
    fileToolBar->addWidget(label2);
    fileToolBar->addSeparator();
    fileToolBar->addWidget(label3);
    fileToolBar->addSeparator();
    fileToolBar->addSeparator();
    fileToolBar->addWidget(label4);
    fileToolBar->addSeparator();
    fileToolBar->addWidget(label5);
    fileToolBar->addSeparator();
    fileToolBar->addWidget(label6);
    //addToolBar(fileToolBar);

}


QSize MainWindow::sizeHint() const
{
    return QSize(500,200);
}

//This function opens a file and stores the
//features of the items specified in the chosen
//file into a QMap object
void MainWindow::on_openButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File");

    if (filename.isEmpty())
        return;

    theList.addItemsFromFile(filename);

    //This the part where the items in the file will be printed
    QStringList someList = theList.getStringList();

    int index = 0;
    for (const QString &item : someList)
    {
        QString b = someList.at(index);
        Item *someItem = theList.searchForItem(b);

        QString barcode = someItem->getBarcode();
        QString des = someItem->getDescription();
        int stock = someItem->getStock();
        double price = someItem->getPrice();

        QString stockVal = QString::number(stock);
        QString priceVal = QString::number(price);

        QString itemFeatures = barcode + "\t" + des + "\t" + stockVal + "\tR" + priceVal;

        textEdit->append(itemFeatures);
        index++;
    }

}

void MainWindow::on_changeButton_clicked()
{
    bool ok;
    QString barcode = QInputDialog::getText(this, "Enter barcode", "Please enter the barcode:", QLineEdit::Normal, "", &ok);

    if (ok && !barcode.isEmpty())
    {
        Item *someItem = theList.searchForItem(barcode);

        if (someItem == nullptr)
            QMessageBox::information(nullptr, "Barcode Not Found", "The entered barcode is not in the database.");
        else {
            ChangeItemDialog *changeDialog = new ChangeItemDialog(this);

            QString oldBarcode;
            QString oldDescription;
            int oldStock;
            double oldPrice;

            oldBarcode = someItem->getBarcode();
            oldDescription = someItem->getDescription();
            oldStock = someItem->getStock();
            oldPrice = someItem->getPrice();

            changeDialog->setBarcodeLineEdit(oldBarcode);
            changeDialog->disableBarcodeField();
            changeDialog->setDescriptionLineEdit(oldDescription);
            changeDialog->setStockLineEdit(oldStock);
            changeDialog->setPriceLineEdit(oldPrice);

            if(changeDialog->exec() == QDialog::Accepted)
            {
                QString newDescription = changeDialog->getDescription();
                int newStock = changeDialog->getStock();
                int newPrice = changeDialog->getPrice();

                someItem->setDescription(newDescription);
                someItem->setStock(newStock);
                someItem->setPrice(newPrice);

                QMessageBox::information(nullptr,"Change is made","The change has been made");
            }
        }
    }
}

void MainWindow::on_addButton_clicked()
{
    ChangeItemDialog *addDialog = new ChangeItemDialog;
    if(addDialog->exec() == QDialog::Accepted)
    {
        QString barcode = addDialog->getBarcodeValue();

        bool exists = theList.searchForBarcode(barcode);

        if (exists)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Update Stock", "Do you want to enter a new stock amount?",
                                          QMessageBox::Yes|QMessageBox::No);

            if(reply == QMessageBox::Yes)
            {
                bool ok;
                int newStock = QInputDialog::getInt(this,"Enter New Stock", "New Stock Amount:", 0, 0, 1000000, 1, &ok);

                if(ok)
                {
                    Item *someItem = theList.searchForItem(barcode);
                    someItem->setStock(newStock);

                    QString b = someItem->getBarcode();
                    QString d = someItem->getDescription();
                    int s = someItem->getStock();
                    double p = someItem->getPrice();

                }
            }
        } else {
            QString description = addDialog->getDescription();
            int stockAmount = addDialog->getStock();
            double price = addDialog->getPrice();

            Item *newItem = new Item(barcode, description, stockAmount, price);

            theList.addItem(newItem);
        }
    }
}

void MainWindow::on_removeButton_clicked()
{
    bool ok;
    QString barcode = QInputDialog::getText(this, "Delete Item", "Enter Barcode:",
                                            QLineEdit::Normal, QString(), &ok);

    if(ok && !barcode.isEmpty())
    {
        bool exists = theList.searchForBarcode(barcode);

        if(exists)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Delete Item", "Are you sure you want to delete this item?",
                                          QMessageBox::Yes|QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                theList.removeItem(barcode);
            }
        } else {
           QMessageBox::information(nullptr, "Item Not Found", "The entered barcode is not in the database.");
        }
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Save File");

    if (filename.isEmpty())
        return;

    theList.saveItemsIntoFile(filename);
}

