#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    //Precondition: The arguments must be of type string and the surname must have
    //less than 4 characters otherwise the function will return "no username".
    //Postcondition: The method will return the username.
    string generateUserName(string name, string surname);
    //precondition: the arguments must be strings and
    //there must be more than 4 characters in the name and surname
    //postcondition: returns a string, the username.
    string createUserName(string name, string surname);
    //creates a username
    //precondition: not enough characters in the username(less than 5 characters)
    //and arguments have to be strings.
    //postcondition: adds 0s to an existing username to create username of
    //sufficient length.
    string appendUserName(string name, string surname);
    //concatenates the name and surname of the user.
    string appendNames(string name, string surname);
    //Precondition: the arguments must be strings
    //Postcondition: the function returns a password in the form of
    //a string
    string generatePassword(string name, string surname);
    string getName() const;
    string getSurname() const;
    ~Widget();

private slots:
    void on_nameButton_clicked();

private:
    string name_1;
    string surname_1;
    Ui::Widget *ui;
};
#endif // WIDGET_H
