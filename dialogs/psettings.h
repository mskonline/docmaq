#ifndef PSETTINGS_H
#define PSETTINGS_H

#include "ui_psettings.h"
#include <QtGui>

class psettings : public QWidget, private Ui::psettings
{
    Q_OBJECT

public :
    QList <int> *lt;
    psettings(QList <int> *);
    void setvalues();

signals :

    void setpositions();

 public slots :
    void writepos();
};

#endif // PSETTINGS_H
