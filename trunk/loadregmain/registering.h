#ifndef REGISTERING_H
#define REGISTERING_H

#include <QtGui/QWidget>
#include "ui_registering.h"

class registering : public QWidget,public Ui::registering
{
    Q_OBJECT

public:
    registering(QWidget *parent = 0);

};

#endif // REGISTERING_H
