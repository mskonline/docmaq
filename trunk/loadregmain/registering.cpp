#include "registering.h"
#include <QTimer>


registering::registering(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    setWindowFlags (Qt::FramelessWindowHint);
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    QTimer::singleShot(3000, qApp, SLOT(quit()));

}


