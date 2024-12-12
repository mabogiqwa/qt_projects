#include "changeitemdialog.h"
#include "item.h"

ChangeItemDialog::ChangeItemDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Change Dialog");

    // Create QLabel and QLineEdit objects
    QLabel *barcodeLabel = new QLabel("Barcode:");
    barcodeLineEdit = new QLineEdit;

    barcodeLineEdit->setFixedWidth(200);

    // Create a layout for the dialog
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(barcodeLabel);
    layout->addWidget(barcodeLineEdit);

    QLabel *descriptionLabel = new QLabel("Description:");
    descriptionLineEdit = new QLineEdit;

    descriptionLineEdit->setFixedWidth(200);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addWidget(descriptionLabel);
    layout2->addWidget(descriptionLineEdit);

    QLabel *stockLabel = new QLabel("Stock:");
    stockLineEdit = new QSpinBox;

    stockLineEdit->setFixedWidth(200);

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addWidget(stockLabel);
    layout3->addWidget(stockLineEdit);

    QLabel *priceLabel = new QLabel("Price:");
    priceLineEdit = new QDoubleSpinBox;

    priceLineEdit->setFixedWidth(200);

    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4->addWidget(priceLabel);
    layout4->addWidget(priceLineEdit);

    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    connect(okButton, &QPushButton::clicked, this, [=](){
        ChangeItemDialog::on_okButton_clicked();
    });
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    QHBoxLayout *layout5 = new QHBoxLayout;
    layout5->addWidget(okButton);
    layout5->addWidget(cancelButton);

    QVBoxLayout *layout6 = new QVBoxLayout;
    layout6->addLayout(layout);
    layout6->addLayout(layout2);
    layout6->addLayout(layout3);
    layout6->addLayout(layout4);
    layout6->addLayout(layout5);

    setLayout(layout6);

}

void ChangeItemDialog::on_okButton_clicked()
{
    QString barcode = barcodeLineEdit->text();
    QString description = descriptionLineEdit->text();
    int numOfStock = stockLineEdit->value();
    double price = priceLineEdit->value();
    int lengthOfBarcode = barcode.length();

    // Check barcode validity
    bool onlyDigits = true;
    for (const QChar &ch : barcode)
    {
        if (!ch.isDigit()) {
            onlyDigits = false;
            QMessageBox::warning(nullptr, "Warning", "Barcode entry must only contain digits!");
            return; // Exit the function if the barcode is invalid
        }
    }

    // Perform input validations
    if (barcode.isEmpty())
    {
        QMessageBox::warning(nullptr, "Warning", "Barcode is empty!");
    }
    else if ((lengthOfBarcode < 13 || lengthOfBarcode > 13))
    {
        QMessageBox::warning(nullptr, "Warning", "Barcode must be strictly 13 digits!");
    }
    else if (description.isEmpty())
    {
        QMessageBox::warning(nullptr, "Warning", "Description is empty!");
    }
    else if (numOfStock <= 0 || numOfStock > 2000)
    {
        QMessageBox::warning(nullptr, "Warning", "Invalid input for stock (Value between 0 and 2000)!");
    }
    else if (price <= 0 || price > 10000)
    {
        QMessageBox::warning(nullptr, "Warning", "Invalid input for price (Value between R0 and R10,000)!");
    } else {
        accept();
    }     
}

ChangeItemDialog::~ChangeItemDialog()
{
}

QString ChangeItemDialog::getBarcodeValue() const
{
    QString barcode = barcodeLineEdit->text();

    return barcode;
}

QString ChangeItemDialog::getDescription() const
{
    QString description = descriptionLineEdit->text();

    return description;
}

int ChangeItemDialog::getStock() const
{
    int stockAmount = stockLineEdit->value();

    return stockAmount;
}

double ChangeItemDialog::getPrice() const
{
    double price = priceLineEdit->value();

    return price;
}

void ChangeItemDialog::setBarcodeLineEdit(QString val)
{
    barcodeLineEdit->setText(val);
}

void ChangeItemDialog::setDescriptionLineEdit(QString val)
{
    descriptionLineEdit->setText(val);
}

void ChangeItemDialog::setStockLineEdit(int val)
{
    stockLineEdit->setValue(val);
}

void ChangeItemDialog::setPriceLineEdit(double val)
{
    priceLineEdit->setValue(val);
}

void ChangeItemDialog::disableBarcodeField()
{
    barcodeLineEdit->setReadOnly(true);
}

