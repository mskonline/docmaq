#include <QtSql>
#include <QtGui>
#include "ui_mainwindow.h"

#define PRINT_ALL 0
#define PRINT_FIELDS 1

class bulkprint;
class selectiveprint;
class logs;
class psettings;
class ChangePassword;

class sdetails
{
public:
    QString stname,ftname,stroll,year,branch,course,
    gender,sem,fyear,tyear,fmt,co,sds,p_pose;
    sdetails()
    {
        stname = ftname = year = branch = course = "";
        gender = sem =  p_pose = "";
        co = sds = fyear = tyear = "";
    }
    void reset()
    {
        sdetails();
    }
};

class mainwindow : public QMainWindow
{
    Q_OBJECT
    public :
        mainwindow();
        ~mainwindow();
        Ui::mainwindow ui;
        QPrinter *printer,*printer2;
        QPainter *painter;
        QString lstroll,pdfpath,tempx;
        QAction *actionbclearall,*actionbclearsel,
        *actionselprintall,*actionselprintsel;
        QGraphicsTextItem *s_no,*s_no2;
        float valw,valh;
        int sno;
        QList<int> clist;
        bulkprint *btable;
        selectiveprint *selprint;
        psettings *psets;
        logs *logmanager;
        sdetails *mwsdt;

        void xconnect();
        void setupmenu();
        void setacscene();
        void setdmscene();
        bool queryit(sdetails *);
        void error(QString str);
        void load_logmanager();

    private :
    QGraphicsScene *scene,*scene2;
    QGraphicsTextItem  *sname,*fname,*sdetail,*periodfrom,
    *periodto,*roll,*date,*gen,*purposetext,
    *purpose;
    QGraphicsTextItem *sname2,*fname2,*sdetail2,*periodfrom2,
    *periodto2,*roll2,*date2,*gen2,*purposetext2,
    *purpose2;
    QGraphicsPixmapItem *pix,*pix2;

    QString temp2,q,id,fmt,dt;
    QString qp1,qp2,qp3;
    QList <int> lt;


    int bid,now,bulktype,pt_type,pt_mth,var_yr,var_sem,evt,isreset;
    ChangePassword *cp;


    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *);
    void setprinter();
    void sdttabfill();


    public slots :
    void view_fill(sdetails *);
    void printf(sdetails *);
    void pmode(int);


    private slots :
    void destroycp();
    void changepasswd();
    void abortprint();
    void qfill();
    void bprintall();
    void bprintsel();
    void qprint();
    void setpositions();
    void positionsdialog();
    void reset();
    void breset();
    void about_p();

    void snamechanged(const QString &temp)
    {
        if(evt)
        {
            sname->setPlainText(temp);
            mwsdt->stname = temp;

        }
    }
    void fnamechanged(const QString &temp)
    {
        if(evt)
        {
            fname->setPlainText(temp);
            mwsdt->ftname = temp;
        }
    }
    void yearchanged(const QString &temp)
    {
        if(evt)
        {
            mwsdt->year = !temp.isEmpty() ? ", " + temp + " year" : temp;

            mwsdt->sds = mwsdt->course + mwsdt->branch + mwsdt->year + mwsdt->sem;
            sdetail->setPlainText(mwsdt->sds);
        }
    }
    void semchanged(const QString &temp)
    {
        if(evt)
        {
            mwsdt->sem = !temp.isEmpty() ? ", " + temp + " semester" : temp ;

            mwsdt->sds = mwsdt->course + mwsdt->branch + mwsdt->year + mwsdt->sem;
            sdetail->setPlainText(mwsdt->sds);
        }
    }
    void fromchanged(const QString &temp)
    {
        if(evt)
        {
            periodfrom->setPlainText(temp);
            mwsdt->fyear = temp;
        }
    }
    void tochanged(const QString &temp)
    {
        if(evt)
        {
            periodto->setPlainText(temp);
            mwsdt->tyear = temp;
         }
    }
    void coursechanged(const QString &temp)
    {
        if(evt)
        {
            mwsdt->course = temp;
            mwsdt->sds = mwsdt->course + mwsdt->branch + mwsdt->year + mwsdt->sem;
            sdetail->setPlainText(mwsdt->sds);
        }
    }
    void branchchanged(const QString &temp)
    {
        if(evt)
        {
            mwsdt->branch = !temp.isEmpty() ? " - " + temp : temp;

            mwsdt->sds = mwsdt->course + mwsdt->branch + mwsdt->year + mwsdt->sem;
            sdetail->setPlainText(mwsdt->sds);
        }
    }

    void rollchanged(const QString &temp)
    {
        roll->setPlainText(temp.toUpper());
        mwsdt->stroll = temp;

        if(isreset == 0)
            reset();

    }

    void ppchanged(const QString &temp)
    {

        if(!temp.isEmpty())
        {
            purposetext->setPlainText("This Certificate is issued for the Purpose of : ");
            purpose->setPlainText(temp);
            mwsdt->p_pose = temp;
        }
        else
        {
            purposetext->setPlainText("");
            purpose->setPlainText("");
            mwsdt->p_pose="";
        }

    }

    void cidtoggle(bool flag)
    {
        if(flag)
        {
            QString st;
            s_no->setPlainText(st.sprintf("%04d",ui.sbcno->value()));
            s_no->setVisible(true);
        }
        else
            s_no->setVisible(false);
    }

    void cidvalue(int i)
    {
        QString st;
        s_no->setPlainText(st.sprintf("%04d",i));
        sno = i;
    }

    void genchanged(int index)
    {
        mwsdt->co = index ? "D/o" : "S/o";
        gen->setPlainText(mwsdt->co);
    }

    // TODO
    /*
    void ptchanged(const QString &temp)
    {
        printer->setPrinterName(temp);
        printer2->setPrinterName(temp);
    }
    */
};
