#include "../mainwindow/mainwindow.h"
#include "../log/log.h"
#include "../about/about.h"
#include "../bulkprint/bulkprint.h"
#include "../selectiveprint/selectiveprint.h"
#include "../thread/mythread.h"
#include "../dialogs/psettings.h"
#include "../authentication_manager/authendialog.h"
#include "../cpassword/changepassword.h"

mainwindow::mainwindow()
{
    // Interface Construction
    ui.setupUi(this);
    pt_mth = pt_type = -1;
    evt = isreset = 1;
    pdfpath = "./PDF/";
    lstroll = "";


    dt = QDate::currentDate().toString("dd.MM.yyyy");
    ui.date->setText(dt);

    mwsdt = new sdetails();
    // Scene Construction
    setdmscene();


    // Load Modules
    btable = new bulkprint(this,ui.tab_5);
    btable->show();
    selprint = new selectiveprint(this);
    setupmenu();


    // Start the Authentication Dialog
    AuthenDialog *authendialog = new AuthenDialog(this);
    authendialog->show();

    // Printer Info
    QPrinter print;
    QPrinterInfo pinfo(print);
    ui.pinfo->setText(pinfo.printerName());//.section("",-1,-1));

    // Fetch Printing Positions
    QFile file2("./positions.dat");
    file2.open(QIODevice::ReadOnly);
    QDataStream inp(&file2);
    inp >> lt;

    //set printer
    setprinter();

    //Connections
    connect(ui.bselback,SIGNAL(pressed()),selprint,SLOT(back()));
    connect(ui.bqreset,SIGNAL(pressed()),this,SLOT(breset()));
    connect(ui.bqprint,SIGNAL(pressed()),this,SLOT(qprint()));
    connect(ui.bbulkprintall,SIGNAL(pressed()),this,SLOT(bprintall()));
    connect(ui.bbulkselprint,SIGNAL(pressed()),this,SLOT(bprintsel()));
    connect(ui.bselnext,SIGNAL(released()),selprint,SLOT(next()));
    connect(ui.babortprint,SIGNAL(released()),this,SLOT(abortprint()));
    connect(ui.bpositions,SIGNAL(released()),this,SLOT(positionsdialog()));
    connect(ui.changeButton,SIGNAL(released()),this,SLOT(changepasswd()));

    connect(ui.leqroll,SIGNAL(textChanged(const QString &)),this,SLOT(rollchanged(const QString &)));
    connect(ui.leqsname,SIGNAL(textChanged(const QString &)),this,SLOT(snamechanged(const QString &)));
    connect(ui.leqfname,SIGNAL(textChanged(const QString &)),this,SLOT(fnamechanged(const QString &)));
    connect(ui.cbcourse,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(coursechanged(const QString &)));
    connect(ui.cbbranch,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(branchchanged(const QString &)));
    connect(ui.cbyear,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(yearchanged(const QString &)));
    connect(ui.cbsem,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(semchanged(const QString &)));
    //connect(ui.cbpl,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(ptchanged(const QString &)));
    connect(ui.leqfrom,SIGNAL(textChanged(const QString &)),this,SLOT(fromchanged(const QString &)));
    connect(ui.leqto,SIGNAL(textChanged(const QString &)),this,SLOT(tochanged(const QString &)));
    connect(ui.lepurpose,SIGNAL(textChanged(const QString &)),this,SLOT(ppchanged(const QString &)));
    connect(ui.cbgen,SIGNAL(currentIndexChanged(int)),this,SLOT(genchanged(int)));
    connect(ui.modetab,SIGNAL(currentChanged(int)),this,SLOT(pmode(int)));


    connect(ui.ptcombo,SIGNAL(currentIndexChanged(QString)),ui.ltype,SLOT(setText(const QString &)));
    connect(ui.outbox,SIGNAL(currentIndexChanged(QString)),ui.lout,SLOT(setText(const QString &)));
    connect(ui.gbcno,SIGNAL(toggled(bool)),this,SLOT(cidtoggle(bool)));
    connect(ui.sbcno,SIGNAL(valueChanged (int)),this,SLOT(cidvalue(int)));
    connect(ui.actionQuit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui.actionAbout,SIGNAL(triggered()),this,SLOT(about_p()));
    connect(actionselprintall,SIGNAL(triggered()),selprint,SLOT(printall()));
    connect(actionselprintsel,SIGNAL(triggered()),selprint,SLOT(printsel()));
    connect(ui.actionPrint,SIGNAL(triggered()),this,SLOT(qprint()));
    connect(ui.actionReset,SIGNAL(triggered()),this,SLOT(reset()));

    ui.leqroll->setFocus();
    ui.lepurpose->setText("Bus Pass");
    qp1 = "select STUDENT_ID from student_admission where STUDENT_ROLLNO=";
    qp2 = "select student_name,father_name,gender from student_info where student_id=" ;
    qp3 = "select course,branch_id,current_sem,current_year from student_academic where student_id=" ;

}

void mainwindow::load_logmanager()
{
    QStringList rslist;

    logmanager = new logs(ui.logd);
    logmanager->save();//take backup or just flush
    clist = logmanager->getCount(0);//0 = Bonafide,1 = conduct, 2 = TC

    // Get Last Roll No & Certificate ID
    rslist= logmanager->getLastSnoRollNo();
    ui.lstroll->setText(rslist.at(0));

    sno = rslist.at(1).toInt();
    s_no->setPlainText(tempx.sprintf("%04d",sno));
    ui.sbcno->setValue(sno);

    ui.ltotalptd->setText(tempx.setNum(clist.at(0)));
    ui.ltotalp->setText(tempx.setNum(clist.at(1)));

    //logmanagerButton connection
    connect(ui.logmanagerButton,SIGNAL(pressed()),logmanager,SLOT(createlogmanager()));
    ui.statusLabel->setText("Single Print Mode");
}


void mainwindow::setdmscene()
{

    QRectF dmbounds(0,0,619,438);
    scene=new QGraphicsScene(dmbounds,this);
    QFont sfont("Bitstream Vera Serif",10);
    sfont.setBold(true);
    QFont sfont2("Bitstream Vera Serif",11);
    sfont2.setBold(true);

    QPixmap pic("./pic/bpicrz.png");
    pix = new QGraphicsPixmapItem(pic);
    pix->setOffset(QPointF(0,0));
    scene->addItem(pix);

    s_no = new QGraphicsTextItem("");
    s_no->setZValue(pix->zValue()+1);
    s_no->setPos(QPointF(168,131));
    s_no->setFont(sfont2);
    QColor cred("red");
    s_no->setDefaultTextColor(cred);

    sname = new QGraphicsTextItem("");
    sname->setZValue(pix->zValue()+1);
    sname->setPos(QPointF(230,191));
    sname->setFont(sfont);

    fname = new QGraphicsTextItem("");
    fname->setZValue(pix->zValue()+1);
    fname->setPos(QPointF(115,216));
    fname->setFont(sfont);

    sdetail = new QGraphicsTextItem("");
    sdetail->setPos(QPointF(273,271));
    sdetail->setZValue(pix->zValue()+1);
    sdetail->setFont(sfont);

    periodfrom = new QGraphicsTextItem("");
    periodfrom->setZValue(pix->zValue()+1);
    periodfrom->setPos(QPointF(192,300));
    periodfrom->setFont(sfont);

    periodto = new QGraphicsTextItem("");
    periodto->setZValue(pix->zValue()+1);
    periodto->setPos(QPointF(294,300));
    periodto->setFont(sfont);

    date = new QGraphicsTextItem(dt);
    date->setZValue(pix->zValue()+1);
    date->setPos(QPointF(515,132));
    date->setFont(sfont);

    roll = new QGraphicsTextItem("");
    roll->setZValue(pix->zValue()+1);
    roll->setPos(QPointF(206,244));
    roll->setFont(sfont);

    gen = new QGraphicsTextItem("");
    gen->setZValue(pix->zValue()+1);
    gen->setPos(QPointF(505,191));
    gen->setFont(sfont);

    purpose = new QGraphicsTextItem("");
    purpose->setZValue(pix->zValue()+1);
    purpose->setPos(QPointF(365,339));
    purpose->setFont(sfont);

    purposetext = new QGraphicsTextItem("");
    purposetext->setZValue(pix->zValue()+1);
    purposetext->setPos(QPointF(30,339));
    purposetext->setFont(sfont);

    scene->addItem(s_no);
    scene->addItem(fname);
    scene->addItem(sname);
    scene->addItem(sdetail);
    scene->addItem(periodfrom);
    scene->addItem(periodto);
    scene->addItem(roll);
    scene->addItem(date);
    scene->addItem(gen);
    scene->addItem(purpose);
    scene->addItem(purposetext);
    ui.gview->setScene(scene);
}

void mainwindow::setacscene()
{
    QRectF acbounds(0,0,2480,1754);
    scene2=new QGraphicsScene(acbounds,this);
    QPixmap pic2("./pic/bpic.png");
    pix2 = new QGraphicsPixmapItem(pic2);
    scene2->addItem(pix2);

    s_no2 = new QGraphicsTextItem("");
    s_no2->setZValue(pix2->zValue()+1);
    //s_no2->setPos(QPointF(908,784));

    sname2 = new QGraphicsTextItem("");
    sname2->setZValue(pix2->zValue()+1);
    sname2->setPos(QPointF(908,784));

    fname2 = new QGraphicsTextItem("");
    fname2->setZValue(pix2->zValue()+1);
    fname2->setPos(QPointF(440,896));

    sdetail2 = new QGraphicsTextItem("");
    sdetail2->setZValue(pix2->zValue()+1);
    sdetail2->setPos(QPointF(1128,1108));

    periodfrom2 = new QGraphicsTextItem("");
    periodfrom2->setZValue(pix2->zValue()+1);
    periodfrom2->setPos(QPointF(784,1228));

    periodto2 = new QGraphicsTextItem("");
    periodto2->setZValue(pix2->zValue()+1);
    periodto2->setPos(QPointF(1176,1228));

    date2 = new QGraphicsTextItem(dt);
    date2->setZValue(pix2->zValue()+1);
    date2->setPos(QPoint(2112,540));

    roll2 = new QGraphicsTextItem("");
    roll2->setZValue(pix2->zValue()+1);
    roll2->setPos(QPointF(808,1000));

    gen2 = new QGraphicsTextItem("");
    gen2->setZValue(pix2->zValue()+1);
    gen2->setPos(QPointF(140,904));

    purpose2 = new QGraphicsTextItem("");
    purpose2->setZValue(pix2->zValue()+1);
    purpose2->setPos(QPointF(1024,1372));

    purposetext2 = new QGraphicsTextItem("");
    purposetext2->setZValue(pix2->zValue()+1);
    purposetext2->setPos(QPointF(128,1372));

    scene2->addItem(fname2);
    scene2->addItem(sname2);
    scene2->addItem(sdetail2);
    scene2->addItem(periodfrom2);
    scene2->addItem(periodto2);
    scene2->addItem(roll2);
    scene2->addItem(date2);
    scene2->addItem(gen2);
    scene2->addItem(purpose2);
    scene2->addItem(purposetext2);
}

void mainwindow::setupmenu()
{
    actionbclearall = new QAction(this);
    actionbclearsel = new QAction(this);
    actionbclearall->setText("All");
    actionbclearsel->setText("Selected");
    QMenu *bclearmenu = new QMenu(this);

    bclearmenu->addAction(actionbclearall);
    bclearmenu->addAction(actionbclearsel);
    ui.bclearall->setMenu(bclearmenu);
    connect(actionbclearall,SIGNAL(triggered()),btable,SLOT(cleartable()));
    connect(actionbclearsel,SIGNAL(triggered()),btable,SLOT(clearselected()));


    actionselprintall = new QAction(this);
    actionselprintsel = new QAction(this);
    actionselprintall->setText("All");
    actionselprintsel->setText("Selected");
    QMenu *selprintmenu = new QMenu(this);

    selprintmenu->addAction(actionselprintall);
    selprintmenu->addAction(actionselprintsel);
    ui.bselprint->setMenu(selprintmenu);
}

void mainwindow::xconnect()
{
    // Called in AuthenDialog
    connect(ui.lebp_pose,SIGNAL(returnPressed()),btable,SLOT(fill()));
    connect(ui.lebulkroll,SIGNAL(returnPressed()),btable,SLOT(fill()));
    connect(ui.leqroll,SIGNAL(returnPressed()),this,SLOT(qfill()));
}

void mainwindow::qfill()
{
    /* Called when User Presses "Enter Key" after entering Roll Number.
     * Database Connection is mandatory.
     */
    if(ui.leqroll->text().isEmpty())
        return;

    if(ui.leqroll->text().toUpper() == lstroll)
    {
        qprint();
        return;
    }

    mwsdt->stroll = ui.leqroll->text().toUpper();
    ui.cstroll->setText(mwsdt->stroll);


    /* queryit() fetches details & also reports  for database inconsistency.
     * returns true or false
     */
    if(queryit(mwsdt))
    {
        view_fill(mwsdt);
        sdttabfill();
    }

    lstroll = mwsdt->stroll;
}

void mainwindow::view_fill(sdetails *sdt)
{
    /* called by qfill() & from bulkprint Module
     * to fill details in the QGraphicsView
     */

    sname->setPlainText(sdt->stname);
    fname->setPlainText(sdt->ftname);
    roll->setPlainText(sdt->stroll.toUpper());
    periodfrom->setPlainText(sdt->fyear);
    periodto->setPlainText(sdt->tyear);
    sdetail->setPlainText(sdt->sds);

    if(sdt->gender == "Male")
    {
        gen->setPlainText("S/o");
        ui.cbgen->setCurrentIndex(0);
    }
    else
    {
        gen->setPlainText("D/o");
        ui.cbgen->setCurrentIndex(1);
    }

    if(!sdt->p_pose.isEmpty())
    {
        purposetext->setPlainText("This Certificate is issued for the Purpose of : ");
        purpose->setPlainText(sdt->p_pose);
    }
}

void mainwindow::sdttabfill()
{
    /* called only inside this object
     * flag "evt" disables changes for year,sem,course for ComboBox valueChange()
     * since it results in double assignment
     */

    evt = 0;
    ui.leqsname->setText(mwsdt->stname);
    ui.leqfname->setText(mwsdt->ftname);
    ui.cbcourse->setCurrentIndex(ui.cbcourse->findText(mwsdt->course));
    ui.cbbranch->setCurrentIndex(ui.cbbranch->findText(temp2));
    ui.cbyear->setCurrentIndex(var_yr);
    ui.cbsem->setCurrentIndex(var_sem);
    ui.leqfrom->setText(mwsdt->fyear);
    ui.leqto->setText(mwsdt->tyear);
    evt = 1;

    isreset = 0;
}

bool mainwindow::queryit(sdetails *sdt)
{
    /* The Details are fetched from the database
     * The Code can change if database configuration changes.
     */
    if(sdt->stroll.isEmpty())
        return false;

    // Build the query object from currently opened database.
    QSqlQuery query(QSqlDatabase::database());

    // first query,fetches students unique ID
    q = qp1 + "'" + sdt->stroll + "'" ;
    query.exec(q);
    query.next();
    id = query.value(0).toString();

    if( id.isEmpty() )
    {
        error("No Data Exists for :" + sdt->stroll);
        return false;
    }

    // second query,fetches student name,fathers name, gender
    q = qp2 + id;
    query.exec(q);
    query.next();
    sdt->stname = query.value(0).toString().toUpper();
    sdt->ftname = query.value(1).toString().toUpper();
    sdt->gender = query.value(2).toString();

    if ( sdt->stname.isEmpty() && sdt->ftname.isEmpty() && sdt->gender.isEmpty() )
    {
        error("Few Empty Fields in Database for : " + sdt->stroll);
        return false;
    }

    // third query,fetches course details
    q = qp3 + id;
    query.exec(q);
    query.next();
    sdt->course = query.value(0).toString();
    bid = query.value(1).toInt();
    sdt->sem = query.value(2).toString();
    sdt->year = query.value(3).toString();


    /* TODO
        Academic Year
    */
    sdt->fyear = "2009";
    sdt->tyear = "2010";

    if ( sdt->course.isEmpty() &&  bid == 0 && sdt->year.isEmpty() && sdt->sem.isEmpty() && sdt->fyear.isEmpty() )
    {
        error("Few Empty Fields in Database for : " + sdt->stroll);
        return false;
    }

    var_yr = sdt->year.toInt();

    // Year
    switch ( var_yr )
    {
    case 1: sdt->year = ", I year";
        break;
    case 2: sdt->year = ", II year";
        break;
    case 3: sdt->year = ", III year";
        break;
    case 4: sdt->year = ", IV year";
    }

    var_sem = sdt->sem.toInt();

   // B'tech 1st year don't have semester system
    if (sdt->course == "B.Tech" and var_yr == 1)
   {
       sdt->sem = "";
       var_sem = 0;
    }
   else
   {
        switch ( var_sem )
        {
            case 1 : sdt->sem = ", I semester";
            break;
            case 2 : sdt->sem = ", II semester";
        }
   }

   // Branch
   switch ( bid )
    {
    case 1 : sdt->branch ="EEE";
        break;
    case 2 : sdt->branch ="CSE";
        break;
    case 3 : sdt->branch ="ECE";
        break;
    case 4 : sdt->branch ="IT";
        break;
    case 5 : sdt->branch ="Mech";
        break;
    case 6 : sdt->branch ="Bio-Tech";
        break;
    case 9 : sdt->branch ="ECM";
        break;
    case 10 : sdt->branch ="S & H";
        break;
    case 12 : sdt->branch ="";//MBA
        break;
    case 13 : sdt->branch ="AM";
        break;
    case 14 : sdt->branch ="EET";
        break;
    case 15 : sdt->branch ="ECE";
        break;
    case 16 : sdt->branch ="BSCE";
        break;
    case 17 : sdt->branch ="VLSI";
        break;
    case 19 : sdt->branch ="SE";
        break;
    case 20 : sdt->branch ="CAD-CAM";
        break;
    case 21 : sdt->branch ="Bio-Tech";
        break;
    case 22 : sdt->branch ="";//MCA
        break;
    default : sdt->branch = "";
}

    temp2 = sdt->branch;
    sdt->branch = !sdt->branch.isEmpty() ? " - " + sdt->branch : "";

    // constructing course details.
    sdt->sds = sdt->course + sdt->branch + sdt->year + sdt->sem;

    if(sdt->gender == "Male")
    {
        sdt->stname = "Mr. " + sdt->stname;
        sdt->co = "S/o";
    }
    else
    {
        sdt->stname = "Ms. " + sdt->stname;
        sdt->co = "D/o";
    }
    return true;
}

void mainwindow::bprintall()
{
    btable->display(BULK_PRINT_ALL);
}

void mainwindow::bprintsel()
{
    btable->display(BULK_SELECTED);
}



void mainwindow::breset()
{
        // Complete Interface Reset
        ui.leqsname->clear();
        ui.leqfname->clear();
        ui.cbcourse->setCurrentIndex(0);
        ui.cbbranch->setCurrentIndex(0);
        ui.cbyear->setCurrentIndex(0);
        ui.cbsem->setCurrentIndex(0);
        ui.leqfrom->clear();
        ui.leqto->clear();
        ui.cbgen->setCurrentIndex(-1);
        ui.lepurpose->clear();
        ui.leqroll->clear();
        ui.cstroll->clear();

        sname->setPlainText("");
        fname->setPlainText("");
        sdetail->setPlainText("");
        periodfrom->setPlainText("");
        periodto->setPlainText("");
        roll->setPlainText("");
        gen->setPlainText("");
        lstroll = "";
        // graphicitems purposetext & purpose will be
        // reset

        isreset = 1; // Gui elements reset.
        // Automatically mwsdt will be reset.

}

void mainwindow::reset()
{
    // Interface Reset except Roll & purpose
    if(!isreset)
    {
        ui.leqsname->clear();
        ui.leqfname->clear();
        ui.cbcourse->setCurrentIndex(0);
        ui.cbbranch->setCurrentIndex(0);
        ui.cbyear->setCurrentIndex(0);
        ui.cbsem->setCurrentIndex(0);
        ui.leqfrom->clear();
        ui.leqto->clear();
        ui.cbgen->setCurrentIndex(-1);
        ui.cstroll->clear();

        sname->setPlainText("");
        fname->setPlainText("");
        sdetail->setPlainText("");
        roll->setPlainText("");
        gen->setPlainText("");
        lstroll = "";
        // graphicitems purposetext & purpose will be
        // reset

        isreset = 1; // Gui elements reset.
        // Automatically mwsdt will be reset.
    }
}

// Called by qfill()
void mainwindow::qprint()
{

    if( mwsdt->stroll.isEmpty() or mwsdt->stname.isEmpty() or mwsdt->ftname.isEmpty() or ui.cbgen->currentIndex() == -1)
    {
            QMessageBox::warning(this,"Error",
            "Some of the Mandatory Fields left blank. Cannot Proceed further.");
            return;
    }

    if(QMessageBox::question(this,mwsdt->stroll,"Do you Want to Print Roll No. " + mwsdt->stroll + "'s Certificate ?", QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok) == QMessageBox::Ok)
    {
            // Print Details
            printf(mwsdt);

            // Set Last Printed Roll
            ui.lstroll->setText(mwsdt->stroll);

            // Reset Interface & mwsdt after Printing in Single Print Mode.
            lstroll = "";
            reset();
            ui.leqroll->selectAll();
    }
}

void mainwindow::printf(sdetails *sdt)
{
    int tsno = 0 ;
    fmt = "Printer";
    pt_type = ui.ptcombo->currentIndex();//fields,complete


    if(ui.outbox->currentIndex() == 0)//pdf,printer
    {
        fmt = "PDF  ";
        printer2->setOutputFileName(pdfpath + sdt->stroll + ".pdf");
        painter = new QPainter(printer2);
        valw = (printer2->width()/printer2->widthMM());
        valh = (printer2->height()/printer2->heightMM());
    }
    else
    {
        printer->setDocName(sdt->stroll);
        painter = new QPainter(printer);
        valw = (printer->width()/printer->widthMM());
        valh = (printer->height()/printer->heightMM());
    }
    QFont pfont("MonoType",32);
    QPointF pt;
    QFont paintfont("Bitstream Vera Serif",11);
    QFont snofont("Bitstream Vera Serif",18);

    switch (pt_type)
    {
    case PRINT_ALL :
        //Setting up the actual scene
        setacscene();

        if(ui.gbcno->isChecked())
        {
            // QFont ;
            // s_no2->setFont();
            // QString ctemp;
            // s_no2->setPlainText(ctemp.sprintf("%04",sno);
        }
        sname2->setFont(pfont);
        sname2->setPlainText(sdt->stname);

        fname2->setFont(pfont);
        fname2->setPlainText(sdt->ftname);

        sdetail2->setFont(pfont);
        sdetail2->setPlainText(sdt->sds);

        periodfrom2->setFont(pfont);
        periodfrom2->setPlainText(sdt->fyear);

        periodto2->setFont(pfont);
        periodto2->setPlainText(sdt->tyear);

        roll2->setFont(pfont);
        roll2->setPlainText(sdt->stroll);

        date2->setFont(pfont);
        date2->setPlainText(dt);

        gen2->setFont(pfont);
        gen2->setPlainText(sdt->co);

        purposetext2->setFont(pfont);
        purpose2->setFont(pfont);

        if(!sdt->p_pose.isEmpty())
        {
            purposetext2->setPlainText(" This Certificate is issued for the Purpose of : ");
            purpose2->setPlainText(sdt->p_pose);
        }
        else
        {
            purposetext2->setPlainText("");
            purpose2->setPlainText("");
        }

        scene2->render(painter); //,QRectF(0,0,printer->width(),printer->height()));
        painter->end();
        delete scene2;
        break;
    case PRINT_FIELDS:

        painter->setFont(snofont);
        if(ui.gbcno->isChecked())
        {

            pt.setX(lt.at(0) * valw);
            pt.setY(lt.at(1) * valh);
            painter->drawText (pt,tempx.sprintf("%04d",sno));

            tsno = sno;
            ++sno;

            // Reset Certificate ID to 0001 on reaching
            // the Max value set by User
            if(sno == ui.sbreset->value())
                ui.sbcno->setValue(1);

            ui.sbcno->setValue(sno);
        }

        painter->setFont(paintfont);
        pt.setX(lt.at(2) * valw);
        pt.setY(lt.at(3) * valh);
        painter->drawText ( pt, dt );

        pt.setX(lt.at(4) * valw);
        pt.setY(lt.at(5) * valh);
        painter->drawText ( pt,sdt->stname);

        pt.setX(lt.at(6) * valw);
        pt.setY(lt.at(7) * valh);
        painter->drawText (pt,sdt->co);

        pt.setX(lt.at(8) * valw);
        pt.setY(lt.at(9) * valh);
        painter->drawText (pt,sdt->ftname);

        pt.setX(lt.at(10)* valw);
        pt.setY(lt.at(11)* valh);
        painter->drawText (pt,sdt->stroll);

        pt.setX(lt.at(12) * valw);
        pt.setY(lt.at(13) * valh);
        painter->drawText (pt,sdt->sds);

        pt.setX(lt.at(14) * valw);
        pt.setY(lt.at(15) * valh);
        painter->drawText (pt,sdt->fyear);


        pt.setX(lt.at(16) * valw);
        pt.setY(lt.at(17) * valh);
        painter->drawText ( pt, sdt->tyear);

        if(!sdt->p_pose.isEmpty())
        {
            pt.setX(lt.at(18) * valw);
            pt.setY(lt.at(19) * valh);
            painter->drawText (pt,"This Certificate is issued for the Purpose of : ");

            pt.setX(lt.at(20) * valw);
            pt.setY(lt.at(21) * valh) ;
            painter->drawText (pt,sdt->p_pose);
        }

        painter->end();

        break;
    }

    logmanager->write(tempx.setNum(tsno)+" :: " + sdt->stroll + " |  "+"Certificate Type : Bonafide  |  "+"Format : " + fmt +"  |  Time : "+QTime::currentTime().toString());
    clist.replace(0,clist.at(0) + 1);
    clist.replace(1,clist.at(1) + 1);
    ui.ltotalptd->setText(tempx.setNum(clist.at(0)));
    ui.ltotalp->setText(tempx.setNum(clist.at(1)));

    logmanager->setLastSnoRollNo(sno,sdt->stroll);
    delete painter;
}

void mainwindow::setprinter()
{
    printer = new QPrinter(QPrinter::HighResolution);
    printer->setPaperSize(QPrinter::A5);
    printer->setOrientation(QPrinter::Landscape);
    printer->setFullPage(true);

    printer2 = new QPrinter(QPrinter::HighResolution);
    printer2->setPaperSize(QPrinter::A5);
    printer2->setOrientation(QPrinter::Landscape);
    printer2->setFullPage(true);
    printer2->setOutputFormat(QPrinter::PdfFormat);
}

void mainwindow::positionsdialog()
{
    psets = new psettings(&lt);
    psets->show();

    connect(psets,SIGNAL(setpositions()),this,SLOT(setpositions()));
}

void mainwindow::setpositions()
{
    QFile file("./positions.dat");
    file.open(QIODevice::ReadOnly);

    lt.clear();
    QDataStream inp(&file);
    inp >> lt;

    file.close();
    delete psets;
}

void mainwindow::pmode(int i)
{
    switch(i)
    {
        case 0 : //Single Print Mode
                breset();
                ui.statusLabel->setText("Single Print Mode");
                ui.gview->setDisabled(false);
                ui.optab->widget(0)->setDisabled(false);
                isreset=1;
                break;
        case 1: // Bulk print Mode
                reset();
                ui.leqroll->setText("");
                ui.statusLabel->setText("Bulk Print Mode");
                ui.optab->widget(0)->setDisabled(true);
                isreset = 0;
                break;
        case 2: // Selective Print Mode
                ui.leqroll->clear();
                ui.statusLabel->setText("Selective Print Mode");
                ui.gview->setDisabled(true);
                ui.optab->widget(0)->setDisabled(true);
      }

}

void mainwindow::abortprint()
{
    if(QMessageBox::question(this,"Abort Printing","Do Want Cancel Printing ?", QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel) == QMessageBox::Ok)
    {
        if(printer != NULL)
            printer->abort();
        logmanager->write("Printing aborted");
    }
}


void mainwindow::about_p()
{
    about *abt =  new about();
    abt->show();
}

void mainwindow::error(QString str)
{
    ui.optab->setCurrentIndex(3);
    ui.errord->append(QTime::currentTime().toString() + " :  " + str);
}

void mainwindow::closeEvent(QCloseEvent *e)
{
        logmanager->write("\n****************************End of Session**************************\n");
        logmanager->setCount(clist.at(0),clist.at(1),0);
        logmanager->save();
        e->accept();
    }

void mainwindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Home:
        ui.optab->setCurrentIndex(0);
        ui.modetab->setCurrentIndex(0);
        break;
    case Qt::Key_Delete:
        reset();
        break;
    case Qt::Key_F1:
        about_p();
    }
}

void mainwindow::changepasswd()
{

    cp = new ChangePassword();
    connect(cp,SIGNAL(destroycp()),this,SLOT(destroycp()));

    cp->show();
}

void mainwindow::destroycp()
{
    delete cp;
}
mainwindow::~mainwindow()
{
    delete scene;
}
