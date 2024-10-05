#include "widget.h"
#include "./ui_widget.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_nameButton_clicked()
{
    QString name;
    string name_1;
    bool ok;
    name = QInputDialog::getText(this, tr("Input Name"),
                                    tr("Name:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
    name_1 = name.toStdString();

    QString surname;
    bool ok1;
    surname = QInputDialog::getText(this, tr("Input Surname"),
                                    tr("Surname:"), QLineEdit::Normal, QDir::home().dirName(), &ok1);
    surname_1 = surname.toStdString();

    QString qs;
    QString qs1;
    int surnameLength = surname_1.length();
    if(surnameLength < 4)
    {
        string username = generateUserName(name_1, surname_1);
        if(username.length() < 5)
        {
            username =  appendUserName(name_1, surname_1);
        }
        qs = QString::fromLocal8Bit(username.c_str());
    } else {
        string username = createUserName(name_1, surname_1);
        qs = QString::fromLocal8Bit(username.c_str());
    }
    string password = generatePassword(name_1, surname_1);
    qs1 = QString::fromLocal8Bit(password.c_str());

    int ret = QMessageBox::information(this,"Choose option","Press Ok to display the generated username and password. Press Cancel to not display.", QMessageBox::Ok | QMessageBox::Cancel);

    if(ret == QMessageBox::Ok)
    {
        ui->userNameOutput->setText(qs);
        ui->passwordLabel->setText(qs1);
    }
    if(ret == QMessageBox::Cancel)
    {
        ui->userNameOutput->setText("(Not generated)");
        ui->passwordLabel->setText("(Not generated)");
    }

}

string Widget::generateUserName(string name, string surname)
{
    string usernameChars = "", username;
    int num, num2, num3;

    int numOfSurnameChars = surname.length();

    if((numOfSurnameChars < 4) && (!name.empty() && !surname.empty())) { //This if is executed when there
        num = name[0];        //are not enough character in the surname
        if(isupper(num))      //less than 4.
            name[0] = tolower(num);
        if(numOfSurnameChars == 1) {
            usernameChars += surname[0];
            for(int i = 0; i < 4; i++) {
                num3 = name[i];
                if(isalpha(num3))
                    usernameChars += name[i];
            }
        } else if(numOfSurnameChars == 2) {
            usernameChars += surname[0];
            usernameChars += surname[1];
            for(int j = 0; j < 3; j++) {
                num3 = name[j];
                if(isalpha(num3))
                    usernameChars += name[j];
            }
        } else if(numOfSurnameChars == 3) {
            for(int i = 0; i < 3; i++)
                usernameChars += surname[i];
            usernameChars += name[0];
            usernameChars += name[1];
        }
    } else {
        return "(Not generated)";
    }
    username = usernameChars;

    num2 = username[0];
    if(islower(num2))
        username[0] = toupper(num2);

    return username;
}

string Widget::createUserName(string name, string surname)
{
    string surnameChars = "", username;
    string nameChars = "";
    int num, num2;

    for(int i = 0; i < 4; i++) {
        if(i == 0) {
            num = surname[i]; //this 'if' block is the created the first character
            if(islower(num))  //in the surname, to convert to an uppercase.
                surname[i] = toupper(num);
        };
        surnameChars += surname[i]; //adds the characters in the
    };                             //cstring to the string variable

    for(int j = 0; j < 1; j++)
        nameChars += name[j];
    num = nameChars[0];
    if(isupper(num))
        nameChars[0] = tolower(num); //converts the first character of
            //of the name to a lowercase.

    username = surnameChars + nameChars;

    return username;
}

string Widget::appendUserName(string name, string surname)
{
    string username = generateUserName(name,surname);
    int userNameLength = username.length();
    if(userNameLength < 5) {   //if there are less than 5 characters in the username
        if(userNameLength == 0)
            username = "00000";
        else if(userNameLength == 1)
            username += "0000";
        else if(userNameLength == 2)
            username += "000";
        else if(userNameLength == 3)
            username += "00";
        else if(userNameLength == 4)
            username += "0";
    };
    return username;
}
string Widget::appendNames(string name, string surname)
{
    string appendedFullName = "";
    for(int i = 0; i < name.length(); i++)
        appendedFullName += name[i];
    for(int j = 0; j < surname.length(); j++)
        appendedFullName += surname[j];

    return appendedFullName;
}

string Widget::generatePassword(string name, string surname)
{
    string password = "";
    int lengthOfName, random_number;

    if(name.empty() && surname.empty())
         return "(Not generated)";

    string appendedFName = appendNames(name,surname);
    srand(time(0));

    lengthOfName = name.length() + surname.length();
    lengthOfName--;
    for(int i = 1; i <= 5; i++)
    {
        random_number = 1 + rand() % lengthOfName;
        password += appendedFName[random_number];
    }

    return password;
}
string Widget::getName() const
{
    return name_1;
}

string Widget::getSurname() const
{
    return surname_1;
}
