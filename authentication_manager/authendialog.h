#ifndef AUTHENWIDGET_H_INCLUDED
#define AUTHENWIDGET_H_INCLUDED

#include "ui_authendialog.h"

class QSettings;
class QDialog;
class mainwindow;



class AuthenDialog:public QDialog,public Ui::AuthenDialog
{
    Q_OBJECT

private slots:

    void enableLoginButton(const QString &);
    void enableSaveRollbackButtons();
    void loginPageAuthentication();
    void generalPageAuthentication();
    void databasePageAuthentication();
    void saveSettings();
    void getSettings();
    void setDatabase();
    void on_save2Button_pressed();
    void enableSave2DefaultButton();
    void on_defaultButton_pressed();
    void on_localCheckBox_pressed();
    void on_centralCheckBox_pressed();

private:

    mainwindow *mw;

public:

    AuthenDialog(mainwindow *parent=0);
    QSettings *settings;
    bool authenticate(const QVariant&,QString userno="1");//admin=1;user=0;
    void messageBox(char *,char *);
    bool ok;


};

#endif // AUTHENWIDGET_H_INCLUDED
