#ifndef SELECTIVEPRINT_H
#define SELECTIVEPRINT_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QtGui>

class mainwindow;
class sdetails;

class selectiveprint :public QWidget
{
    Q_OBJECT

public :
    QString cr,yr,sec,roll,sqt;
    QStringList hl;
    mainwindow *mw;
    sdetails *spsdt;
    int intbr,frow,br;

    selectiveprint(mainwindow *mw);
    int bid (int branch);
public slots :
    void next();
    void back();
    void printall();
    void printsel();
};

#endif // SELECTIVEPRINT_H
