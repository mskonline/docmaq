#include "selectiveprint.h"
#include "../mainwindow/mainwindow.h"
#include "../log/log.h"
#include <QMessageBox>

selectiveprint::selectiveprint(mainwindow *mw)
{
    this->mw = mw;
    spsdt = new sdetails();
    frow = 0;
    hl << "Roll Numbers";

    mw->ui.seltab->setColumnWidth(0,270);
    mw->ui.seltab->setFocusPolicy(Qt::StrongFocus);
    mw->ui.seltab->setEditTriggers (QAbstractItemView::NoEditTriggers);
}

void selectiveprint::next()
{
    br = mw->ui.cbselbranch->currentIndex();
    cr = mw->ui.cbselcourse->currentText();
    yr = mw->ui.cbselyear->currentText();
    sec = mw->ui.cbselsection->currentText();

    if(br == -1 | cr.isNull() | yr.isNull() | sec.isNull())
    return;


    intbr = bid(br);
    QVariant v(intbr);
    sqt = tr("SELECT STUDENT_ROLLNO FROM student_admission where STUDENT_ID in (SELECT STUDENT_ID FROM student_academic where course=") + "'"+ cr + "'" + " and BRANCH_ID=" + v.toString() +
                                  " and CURRENT_SEC=" + sec + " and CURRENT_YEAR=" + yr + ");";
    QSqlQuery query(QSqlDatabase::database());
    query.exec(sqt);
    mw->ui.stwselprint->setCurrentIndex(1);
    while (query.next())
    {
         roll = query.value(0).toString();
         mw->ui.seltab->insertRow(frow);
         mw->ui.seltab->setItem(frow,0,new QTableWidgetItem(roll));
         ++frow;
    }
}

void selectiveprint::back()
{
    mw->ui.stwselprint->setCurrentIndex(0);
    if(frow == 0)
    return;

    frow = 0;
    mw->ui.seltab->clear();
    mw->ui.seltab->setHorizontalHeaderLabels( hl );
    mw->ui.seltab->setRowCount(0);
}

void selectiveprint::printsel()
{
    if(frow == 0)
    return;

    if(QMessageBox::question(this,"Selective Print","Do Want to Continue to Printing ?", QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel) == QMessageBox::Cancel)
    return;

    if (mw->ui.optab->currentIndex() == 0)
    {
        mw->pdfpath =  QFileDialog::getExistingDirectory(this, tr("Select Directory for Saving PDF files"),
                                                 QDesktopServices::displayName (QDesktopServices::DesktopLocation),
                                                 QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks) + "/";
        if(mw->pdfpath.isEmpty())
            mw->pdfpath = "./PDF/";
    }

    QTableWidgetItem *item;
    QList<QTableWidgetItem *> bulkselectlist = mw->ui.seltab->selectedItems();
    mw->logmanager->write("Selective Print Started");
    foreach(item,bulkselectlist)
    {
         spsdt->stroll = item->text();
         if(mw->queryit(spsdt))
            mw->printf(spsdt);

    }
    spsdt->stroll = "";
    mw->logmanager->write("Selective Print Ended" );
    mw->pdfpath = "./PDF/";
}

void selectiveprint::printall()
{
    if(frow == 0)
    return;


    if(QMessageBox::question(this,roll,"Do Want to Continue to Printing ?", QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel) == QMessageBox::Cancel)
    return;

    if (mw->ui.optab->currentIndex() == 0)
    {
        mw->pdfpath =  QFileDialog::getExistingDirectory(this, tr("Select Directory for Saving PDF files"),
                                                 QDesktopServices::displayName (QDesktopServices::DesktopLocation),
                                                 QFileDialog::ShowDirsOnly
                                                  | QFileDialog::DontResolveSymlinks) + "/";
        if(mw->pdfpath.isEmpty())
            mw->pdfpath = "./PDF/";
    }

    mw->logmanager->write("Selective Print Started" );

    for(int i = 0;i < mw->ui.seltab->rowCount();++i)
    {
        if(mw->ui.seltab->item(i,0) != 0)
        spsdt->stroll = mw->ui.seltab->item(i,0)->text();
        if(mw->queryit(spsdt))
             mw->printf(spsdt);
    }
    mw->logmanager->write("Selective Print Ended" );
    mw->pdfpath = "./PDF/";
}

int selectiveprint::bid(int branch)
{
    int i;
    switch (branch)
    {
        case 1: i=13;
                break;
        case 2: i=6;
                break;
        case 3 : i=2;
                break;
        case 4 : i=3;
                break;
        case 5 :i=9;
                break;
        case 6 : i=1;
                break;
        case 7 : i=14;
                break;
        case 8 : i=4;
                break;
        case 9 : i=5;
                break;
        case 10 :i=22;
                break;
        case 11: i=12;
                break;
        case 12: i=21;
                break;
        case 13: i=16;
                break;
        case 14: i=20;
                break;
        case 15: i=15;
                break;
        case 16: i=19;
                break;
        case 17: i=10;
                break;
        case 18: i=17;
            break;
        default : i=0;
     }
 return i;
}

