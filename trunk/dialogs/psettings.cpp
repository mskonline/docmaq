#include "psettings.h"

psettings::psettings(QList<int> *ltx)
{
    setupUi(this);

    lt = ltx;
    setvalues();
    connect(bok,SIGNAL(pressed()),this,SLOT(writepos()));
}



void psettings::setvalues()
{
    sbcidw->setValue(lt->at(0));
    sbcidh->setValue(lt->at(1));
    sbdw->setValue(lt->at(2));
    sbdh->setValue(lt->at(3));
    sbsnw->setValue(lt->at(4));
    sbsnh->setValue(lt->at(5));
    sbcw->setValue(lt->at(6));
    sbch->setValue(lt->at(7));
    sbfnw->setValue(lt->at(8));
    sbfnh->setValue(lt->at(9));
    sbrnw->setValue(lt->at(10));
    sbrnh->setValue(lt->at(11));
    sbcdw->setValue(lt->at(12));
    sbcdh->setValue(lt->at(13));
    sbfyw->setValue(lt->at(14));
    sbfyh->setValue(lt->at(15));
    sbtyw->setValue(lt->at(16));
    sbtyh->setValue(lt->at(17));
    sbptw->setValue(lt->at(18));
    sbpth->setValue(lt->at(19));
    sbpw->setValue(lt->at(20));
    sbph->setValue(lt->at(21));


}

void psettings::writepos()
{
    if(QMessageBox::question(this,"Set Positions","Do you want OverWrite the Positions ?", QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok) != QMessageBox::Ok)
    {
        setvalues();
        return;
    }


    QList <int> temp;
    temp <<  sbcidw->value();
    temp <<  sbcidh->value();
    temp <<  sbdw->value();
    temp <<  sbdh->value();
    temp <<  sbsnw->value();
    temp <<  sbsnh->value();
    temp <<  sbcw->value();
    temp <<  sbch->value();
    temp <<  sbfnw->value();
    temp <<  sbfnh->value();
    temp <<  sbrnw->value();
    temp <<  sbrnh->value();
    temp <<  sbcdw->value();
    temp <<  sbcdh->value();
    temp <<  sbfyw->value();
    temp <<  sbfyh->value();
    temp <<  sbtyw->value();
    temp <<  sbtyh->value();
    temp <<  sbptw->value();
    temp <<  sbpth->value();
    temp <<  sbpw->value();
    temp <<  sbph->value();

    QFile file("./positions.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << temp;
    file.close();

    emit setpositions();
}

