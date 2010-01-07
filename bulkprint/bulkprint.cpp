#include "bulkprint.h"
#include "../dialogs/bulkdialog.h"
#include "../mainwindow/mainwindow.h"
#include "../log/log.h"


bulkprint::bulkprint(mainwindow *mw,QWidget *parent)
    : QTableWidget(parent)
{
    this->mw = mw;
    frow = 0;
    hl << "Roll Numbers" << "Purpose";
    if (columnCount() < 1)
        setColumnCount(2);
    bpsdt = new sdetails();
    setHorizontalHeaderLabels(hl);
    setColumnWidth(0,210);
    setColumnWidth(1,70);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setFocusPolicy(Qt::StrongFocus);
    setEditTriggers (QAbstractItemView::NoEditTriggers);
    setGeometry(QRect(10, 20, 281, 271));

}

void bulkprint::fill()
{
    bpsdt->stroll = mw->ui.lebulkroll->text().toUpper();
    bpsdt->p_pose = mw->ui.lebp_pose->text();

    if(mw->queryit(bpsdt))
    {
        mw->view_fill(bpsdt);
        insertRow(frow);
        setItem(frow,0,new QTableWidgetItem(bpsdt->stroll));
        setItem(frow,1,new QTableWidgetItem(bpsdt->p_pose));
        ++frow;
        mw->ui.lebulkroll->clear();
    }
}

void bulkprint::cleartable()
{
    if(frow == 0)
        return;

    frow = 0;
    clear();
    setHorizontalHeaderLabels( hl );
    setRowCount(0);
}

void bulkprint::clearselected()
{
    int i;
    QList<QTableWidgetItem *> bsl = selectedItems();
    for(i = 0 ; i < bsl.length();)
    {
        i = row(bsl.at(i));
        removeRow(i);
        i = i + 2;
    }
    frow = rowCount();
}

void bulkprint::display(int type)
{
    int i ;
    btype = type;
    if(frow == 0)
        return;

    bdl = new bulkdialog();
    connect(bdl,SIGNAL(contin()),this,SLOT(print()));

    switch(btype)
    {
    case BULK_PRINT_ALL :
        for(i = 0; i < rowCount(); ++i)
        {
            if(item(i,0) != 0)
                bdl->tedisplay->append(item(i,0)->text());
        }
        break;
    case BULK_SELECTED :
        QList<QTableWidgetItem *> bsl = selectedItems();

        for(i = 0 ; i < bsl.length();)
		{
                    bdl->tedisplay->append(bsl.at(i)->text());
                    i = i + 2;
		}
    }

    bdl->show();
}

void bulkprint::print()
{

    if (mw->ui.optab->currentIndex() == 0)
    {
        mw->pdfpath =  QFileDialog::getExistingDirectory(this, tr("Select Directory for Saving PDF files"),
                                                         QDesktopServices::displayName (QDesktopServices::DesktopLocation),
                                                         QFileDialog::ShowDirsOnly
                                                         | QFileDialog::DontResolveSymlinks) + "/";

        if(mw->pdfpath.isEmpty())
            mw->pdfpath = "./PDF/";
    }
    mw->logmanager->write("Bulk Print Started" );

    switch(btype)
    {
    case BULK_PRINT_ALL :

        for(int i = 0;i < rowCount();++i)
        {
            if(item(i,0) != 0)
            {
                bpsdt->stroll = item(i,0)->text();
                bpsdt->p_pose = item(i,1)->text();
            }
            if(mw->queryit(bpsdt))
                mw->printf(bpsdt);

        }
        cleartable();
        break;
    case BULK_SELECTED :
        QList<QTableWidgetItem *> bsl = selectedItems();
        for(int i = 0; i < bsl.length();)
        {
            bpsdt->stroll = bsl.at(i)->text();
            bpsdt->p_pose = bsl.at(i+1)->text();
            if(mw->queryit(bpsdt))
                mw->printf(bpsdt);
            i = i + 2;
        }
        clearselected();

    }
    mw->logmanager->write("Bulk Print Ended" );
    mw->pdfpath = "./PDF/";
    bdl->close();
    delete bdl;
}
