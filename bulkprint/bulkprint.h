#ifndef BULKPRINT_H
#define BULKPRINT_H
#include <QTableWidget>
#include <QStringList>

#define BULK_PRINT_ALL 0
#define BULK_SELECTED 1

class bulkdialog;
class mainwindow;
class sdetails;

class bulkprint : public QTableWidget
{
    Q_OBJECT

public :
    mainwindow *mw;
    bulkdialog *bdl;
    sdetails *bpsdt;
    int frow,btype;
    QList <sdetails *> blist;
    QStringList hl;
    bulkprint(mainwindow *mw,QWidget *parent = 0);

public slots :
    void display(int type);
    void fill();
    void cleartable();
    void clearselected();
    void print();
};

#endif // BULKPRINT_H
