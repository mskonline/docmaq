//---------------AUTHOR:PRANEETH-----------------------
//------------PROGRAM:ALLOWS TO CHANGE PASSWORD--------
#include <QtUiTools>
#include <QtGui>
#include "changepassword.h"
#include <QDebug>

ChangePassword::ChangePassword()
{
    settings= new QSettings( QSettings::SystemScope,"Qogency","DocmaQ");

    formWidget = loadUiFile();
    saveButton=qFindChild<QPushButton*>(this, "saveButton");
    cancelButton=qFindChild<QPushButton*>(this, "cancelButton");
    userCombo = qFindChild<QComboBox*>(this, "userCombo");
    passwordLe= qFindChild<QLineEdit*>(this, "passwordLe");
    groupBox2 = qFindChild<QGroupBox*>(this, "groupBox2");
    le1= qFindChild<QLineEdit*>(this, "le1");
    le2= qFindChild<QLineEdit*>(this, "le2");
    label = qFindChild<QLabel*>(this, "label");
    label_2 = qFindChild<QLabel*>(this, "label_2");
    label_3 = qFindChild<QLabel*>(this, "label_3");
    label_4 =qFindChild<QLabel*>(this, "label_4");

    QMetaObject::connectSlotsByName(this);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(formWidget);
    setLayout(layout);
    setWindowTitle(tr("Password Manager"));

    setWindowModality(Qt::ApplicationModal);

    passwordLe->setFocus();
    setGeometry(389,345,385,189);
    setMinimumSize(QSize(385,189));
    setMaximumSize(QSize(385, 189));
}

QWidget* ChangePassword::loadUiFile()
{
    QUiLoader loader;

    QFile file("./forms/changepassword.ui");
    file.open(QFile::ReadOnly);

    QWidget *formWidget= loader.load(&file, this);
    file.close();

    return formWidget;
}
void ChangePassword::on_le1_textChanged()
{
    if (!le1->text().isEmpty())
        saveButton->setEnabled(true);
}

void ChangePassword::on_saveButton_pressed()
{
    if (le1->text()==le2->text() && !le1->text().isEmpty())
    {

        QCryptographicHash hashed(QCryptographicHash::Sha1);

        hashed.addData(QVariant(le2->text()).toByteArray());

        settings->setValue("logins/password"+QString().setNum(userCombo->currentIndex()),hashed.result());

        if (settings->status()!= QSettings::NoError)
        {
            QMessageBox::warning(this,tr("Password Manager"),tr("Password could not be Saved !!"));
        }
        else
        {
            QMessageBox::information(this,"Password Manager","Password Saved !!");
            close();
        }
    }

    else
    {
        QMessageBox::information(this,"Password Manager","Retype the same Password");
        le1->clear();
        le2->clear();
        le1->setFocus();
    }

}

void ChangePassword::on_cancelButton_pressed()
{
    close();
}

void ChangePassword::on_passwordLe_returnPressed()
{
    if (authenticate(passwordLe->text(),QString().setNum(userCombo->currentIndex())))
    {
        groupBox2->setEnabled(true);
        le1->setFocus();
    }
    else
    {
        QMessageBox::information(this,"Password Manager","Incorrect Password");
        passwordLe->clear();
        passwordLe->setFocus();
    }
}

bool ChangePassword::authenticate(const QVariant& passwd,QString userno)
{
    QString temp("password");
    temp+=userno;

    QCryptographicHash hashed(QCryptographicHash::Sha1);
    hashed.addData ( passwd.toByteArray());

    if (hashed.result()==settings->value("logins/"+temp).toByteArray())
        return true;

    return false;
}



ChangePassword::~ChangePassword()
{
    qDebug() << "i am destroyed";
    delete formWidget;
    emit destroycp();
}
