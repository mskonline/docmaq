/********************************************************************************
** Form generated from reading ui file 'registering.ui'
**
** Created: Fri Nov 6 04:12:55 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_REGISTERING_H
#define UI_REGISTERING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registering
{
public:
    QProgressBar *progressBar;
    QLabel *label;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QWidget *registering)
    {
        if (registering->objectName().isEmpty())
            registering->setObjectName(QString::fromUtf8("registering"));
        registering->resize(571, 287);
        registering->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        progressBar = new QProgressBar(registering);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 150, 441, 31));
        progressBar->setValue(14);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);
        label = new QLabel(registering);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 221, 21));
        line = new QFrame(registering);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 40, 561, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(registering);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(480, 10, 20, 271));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        retranslateUi(registering);

        QMetaObject::connectSlotsByName(registering);
    } // setupUi

    void retranslateUi(QWidget *registering)
    {
        registering->setWindowTitle(QApplication::translate("registering", "Installing...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("registering", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600; color:#06ebff;\">Setting Up System Registry........</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(registering);
    } // retranslateUi

};

namespace Ui {
    class registering: public Ui_registering {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERING_H
