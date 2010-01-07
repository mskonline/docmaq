//---------------AUTHOR:PRANEETH--------------------------------------------
//------------PROGRAM:AUTHENTICATION-MANAGER '&' DATABASE MANAGER-----------
#include <QtGui>
#include <QtSql>
#include <QDebug>
#include "authendialog.h"
#include "../mainwindow/mainwindow.h"


AuthenDialog::AuthenDialog(mainwindow *parent)
// :QDialog(parent)
{

    setupUi(this);
    QCoreApplication::setAttribute ( Qt::AA_ImmediateWidgetCreation);
    QWidget::setAttribute(Qt::WA_DeleteOnClose);
    mw=parent;
    settings= new QSettings( QSettings::SystemScope,"Qogency","DocmaQ");
//---------------first page
    connect(iamCombo,SIGNAL(currentIndexChanged(const QString &)),passwordLe,SLOT(setFocus()));
    connect(passwordLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableLoginButton(const QString &)));
    connect(passwordLe,SIGNAL(returnPressed()),loginButton,SIGNAL(clicked()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(loginButton,SIGNAL(clicked()),this,SLOT(loginPageAuthentication()));

//-------------database page
    connect(adminPasswordLe,SIGNAL(returnPressed()),this,SLOT(databasePageAuthentication()));
    connect(dNameLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSaveRollbackButtons()));
    connect(setPortLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSaveRollbackButtons()));
    connect(hostNameLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSaveRollbackButtons()));
    connect(userNameLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSaveRollbackButtons()));
    connect(dPasswordLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSaveRollbackButtons()));

    connect(saveButton,SIGNAL(clicked()),this,SLOT(saveSettings()));
    connect(rollbackButton,SIGNAL(clicked()),this,SLOT(getSettings()));
//----------------general settings page
    connect(adminPasswordLe2,SIGNAL(returnPressed()),this,SLOT(generalPageAuthentication()));
    connect(logPathLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSave2DefaultButton()));
    connect(logDurationLe,SIGNAL(textChanged(const QString &)),this,SLOT(enableSave2DefaultButton()));
    connect(localCheckBox,SIGNAL(pressed()),this,SLOT(enableSave2DefaultButton()));
    connect(centralCheckBox,SIGNAL(pressed()),this,SLOT(enableSave2DefaultButton()));

// -----------to quit the application
    connect(this,SIGNAL(rejected()),qApp,SLOT(quit()));//to quit when user closes authendialog
    groupBox->hide();
    groupBox2->hide();

    passwordLe->setFocus();

    getSettings();  //settings from registry
    if(settings->value("generalsettings/logmode")=="central")
        logPathLe->setEnabled(true);
    save2Button->setEnabled(false);
}



void AuthenDialog:: enableLoginButton(const QString &password)
{
    loginButton->setEnabled(!password.isEmpty());

}

void AuthenDialog:: enableSaveRollbackButtons()
{
    saveButton->setEnabled(true);
    rollbackButton->setEnabled(true);

}

void AuthenDialog::loginPageAuthentication()
{
    bool flag=authenticate(passwordLe->text(),QString().setNum(iamCombo->currentIndex()));

    if (flag)
    {
        done(QDialog::Accepted);

        if (saveButton->isEnabled())
        {
            int result = QMessageBox::question(this, tr("Authentication Manager"),
                                               tr("Database Details changed . Do You want to Save them   ?"),
                                               tr("&Save"), tr("&Go with previous settings"), QString(), 0, 1);

            if (result ==0)
                saveSettings();
            else
                getSettings();
        }
        setDatabase();

        mw->load_logmanager();

        if( ok )
        mw->xconnect();
        else
        mw->error("Connection Error : Unable to Connect to Database\nRelogin & Check Database details in Authentication Manager");

        mw->showMaximized();
}
    else
    {
        messageBox("Authentication Manager","   Incorrect Password!!!  ");
        passwordLe->clear();
    }

}

void AuthenDialog::setDatabase()
{
    //------------------DATABASE CONNECTION----------------------------

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName(dNameLe->text());
    db.setPort(setPortLe->text().toInt());
    db.setHostName(hostNameLe->text());
    db.setUserName(userNameLe->text());
    db.setPassword(dPasswordLe->text());
    ok = db.open();
}

void AuthenDialog::databasePageAuthentication()
{

    if (authenticate(adminPasswordLe->text()))
    {
        groupBox->show();
        groupBox2->show();
    }
    else
    {
        messageBox("Authentication Manager","   Incorrect Password !!!");
        adminPasswordLe->clear();
    }

}
void AuthenDialog::generalPageAuthentication()
{
    if (authenticate(adminPasswordLe2->text()))
    {
        groupBox2->show();
        groupBox->show();
    }
    else
    {
        messageBox("Authentication Manager","   Incorrect Password !!!");
        adminPasswordLe2->clear();
    }
}

void AuthenDialog::on_save2Button_pressed()
{
    settings->beginGroup("generalsettings");
    settings->setValue("logduration",logDurationLe->text());
    settings->setValue("logpath",logPathLe->text());
    if (localCheckBox->isChecked())
        settings->setValue("logmode","local");
    else
        settings->setValue("logmode","central");
    settings->endGroup();
    save2Button->setEnabled(false);
    messageBox("Done..!!","Settings Saved");
}

void AuthenDialog::on_defaultButton_pressed()
{
    settings->beginGroup("generalsettings");
    logDurationLe->setText(settings->value("logduration",180).toString());
    logPathLe->setText(settings->value("logpath").toString());
    if (settings->status()!= QSettings::NoError)
    {
        messageBox("Settings Manager","     Error Occured During Fetching The Settings\n \
                   You can fetch Settings Manually by visiting \
                   HKEY_LOCAL_MACHINE\\Software\\Quogency\\DocmaQ \
                   start->run->regedit    ");
    }
    settings->endGroup();
    defaultButton->setEnabled(false);
}

void AuthenDialog::enableSave2DefaultButton()
{
    save2Button->setEnabled(true);
    defaultButton->setEnabled(true);

}

bool AuthenDialog::authenticate(const QVariant& passwd,QString userno)
{
    QString temp("password");
    temp+=userno;

    QCryptographicHash hashed(QCryptographicHash::Sha1);
    hashed.addData ( passwd.toByteArray());

    if (hashed.result()==settings->value("logins/"+temp).toByteArray())
        return true;

    return false;
}

void AuthenDialog::saveSettings()
{
    settings->beginGroup("database");

    settings->setValue("databasename",dNameLe->text());
    settings->setValue("port",setPortLe->text());
    settings->setValue("hostname",hostNameLe->text());
    settings->setValue("username",userNameLe->text());
    settings->setValue("password",dPasswordLe->text());

    settings->endGroup();

    settings->sync();//  commit changes

    if (settings->status()== QSettings::NoError)
    {
        messageBox("Done !!","Settings Saved !!");

        stackedWidget->setCurrentIndex(0);
        optionsList->setCurrentRow(0);

        saveButton->setEnabled(false);

        rollbackButton->setEnabled(false);
    }

    else
    {
        int result = QMessageBox::question(this, tr("Settings Manager"),
                                           tr("Sorry ,Settings Cannot Be Saved....."),
                                           tr("&Retry"), tr("&No Problem go with previous settings"), QString(), 0, 1);
        if (result == 0)
            saveSettings();
        else
            getSettings();
    }

}

void AuthenDialog::getSettings()
{

    static bool flag =true;

    settings->beginGroup("database");
    dNameLe->setText(settings->value("databasename").toString());
    setPortLe->setText(settings->value("port").toString());
    hostNameLe->setText(settings->value("hostname").toString());
    userNameLe->setText(settings->value("username").toString());
    dPasswordLe->setText(settings->value("password").toString());
    settings->endGroup();

    settings->beginGroup("generalsettings");
    logDurationLe->setText(settings->value("logduration").toString());
    logPathLe->setText(settings->value("logpath").toString());
    if (settings->value("logmode","local")=="local")
        localCheckBox->setChecked(true);
    else
        centralCheckBox->setChecked(true);

    settings->endGroup();

    if (flag)
        saveButton->setEnabled(false);//disabling save on startup

    flag=false;

    rollbackButton->setEnabled(false);

    if (settings->status()!= QSettings::NoError)
    {
        messageBox("Settings Manager","     Error Occured During Fetching The Settings\n \
                   You can fetch Settings Manually by visiting \
                   HKEY_LOCAL_MACHINE\\Software\\Quogency\\DocmaQ \
                   start->run->regedit    ");
    }

}

void AuthenDialog::on_localCheckBox_pressed()
{
    logPathLe->setEnabled(false);
}

void AuthenDialog::on_centralCheckBox_pressed()
{
    logPathLe->setEnabled(true);
}

inline void AuthenDialog::messageBox(char *title,char *message)
{
    QMessageBox::information(this,tr(title),tr(message),
                             QMessageBox::Ok|QMessageBox::Default,
                             QMessageBox::NoButton,QMessageBox::NoButton);

}

