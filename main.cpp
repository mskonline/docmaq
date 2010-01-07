#include <QApplication>
#include <Qt>
#include "../mainwindow/mainwindow.h"
#include "thread/mythread.h"


int main(int argc,char **argv)
{
    QApplication app(argc,argv);
    app.addLibraryPath("./plugins");

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("./stpic.png"));
    splash->show();

    Qt::Alignment bottomleft = Qt::AlignLeft | Qt::AlignBottom;
    splash->showMessage(QObject::tr("Initializing..."),bottomleft, Qt::white);
    mythread::msleep(2);
    splash->showMessage(QObject::tr("Loading Modules..."),bottomleft, Qt::white);
    mythread::msleep(2);
    mainwindow mw;

    splash->finish(&mw);
    delete splash;

    return app.exec();
}	
