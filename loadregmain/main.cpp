//---------------AUTHOR:PRANEETH---------------------------------------------
//------------PROGRAM:SETS REGISTRY FOR THE FIRST TIME(PASSWORDS)-----------------------
#include <QSettings>
#include <QCryptographicHash>
#include <QtGui/QApplication>
#include "registering.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    registering r;
    r.show();

    QSettings settings(QSettings::SystemScope,"Qogency","DocmaQ");

    //------------setting initial passwords
    QCryptographicHash hashed(QCryptographicHash::Sha1);
    hashed.addData ("snist", 5 );
    settings.beginGroup("logins");
    settings.setValue("password0",hashed.result());

    hashed.reset();

    hashed.addData ("admin", 5 );
    settings.setValue("password1",hashed.result());
    settings.endGroup();
    //------------setting database details
    settings.beginGroup("database");
    settings.setValue("databasename","sreenidhi");
    settings.setValue("port",3306);
    settings.setValue("hostname","localhost");
    settings.setValue("username","root");
    settings.setValue("password","");
    settings.endGroup();
    //------------setting initial general settings

    settings.beginGroup("generalsettings");

    settings.setValue("logduration",180);
    settings.setValue("logpath","//10.4.9.57/srinivas/logs/");
    settings.setValue("reminder" ,30);
    settings.setValue("logmode","local");
    //settings.setValue("firsttime","true");
    settings.endGroup();

    //------------setting initial certificatecount-----------------
    settings.beginGroup("certificatecount");
    settings.setValue("bonafide/totalbonafidecount",0000);
    settings.setValue("tc/totaltccount",0000);
    settings.setValue("bonafideconduct/totalbonafideconductcount",0000);

    settings.setValue("bonafide/serialno",0001);
    settings.setValue("bonafideconduct/serialno",0001);
    settings.setValue("tc/serialno",0001);
    settings.endGroup();
    return a.exec();
}
