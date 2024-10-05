#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QDialog>
#include <QTextEdit>
#include <QMap>
#include "itemlist.h"
#include "changeitemdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

    // QWidget interface
private:
    QSize sizeHint() const;
    QAction *exitAction;
    QAction *openAction;
    QAction *addAction;
    QAction *saveAction;
    QAction *changeAction;
    QAction *removeAction;
    QTextEdit *textEdit;
    ItemList theList;
    ChangeItemDialog dialog;
private slots:
    void on_openButton_clicked();
    void on_changeButton_clicked();
    void on_removeButton_clicked();
    void on_saveButton_clicked();
    void on_addButton_clicked();
    //void on_addButton_clicked();
};

#endif // MAINWINDOW_H
