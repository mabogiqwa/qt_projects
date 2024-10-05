#ifndef CHANGEITEMDIALOG_H
#define CHANGEITEMDIALOG_H

#include <QDialog>
#include <QtWidgets>

class ChangeItemDialog : public QDialog
{
    Q_OBJECT

public:
    ChangeItemDialog(QWidget *parent = nullptr);
    ~ChangeItemDialog();
    QString getBarcodeValue() const;
    QString getDescription() const;
    int getStock() const;
    double getPrice() const;
    void setBarcodeLineEdit(QString val);
    void setDescriptionLineEdit(QString val);
    void setStockLineEdit(int val);
    void setPriceLineEdit(double val);
    void disableBarcodeField();
    //Item getItem() const;
private slots:
    void on_okButton_clicked();
private:
    QLineEdit *barcodeLineEdit;
    QLineEdit *descriptionLineEdit;
    QSpinBox *stockLineEdit;
    QDoubleSpinBox *priceLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};
#endif // CHANGEITEMDIALOG_H
