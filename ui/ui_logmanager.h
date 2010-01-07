/********************************************************************************
** Form generated from reading ui file 'logmanager.ui'
**
** Created: Sat Oct 31 07:22:39 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGMANAGER_H
#define UI_LOGMANAGER_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Logmanager
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *searchLabel;
    QSpacerItem *verticalSpacer_5;
    QComboBox *searchCombo;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *searchButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *searchLabel_5;
    QDateEdit *dateEdit;
    QSpacerItem *verticalSpacer_2;
    QPushButton *goButton;
    QSpacerItem *verticalSpacer_3;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *searchLabel_4;
    QLabel *logDateLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *foundLabel;
    QLabel *resultLabel;
    QTextEdit *textEdit;
    QWidget *tab2;
    QVBoxLayout *verticalLayout_3;
    QLabel *filesFoundLabel;
    QTableWidget *tableWidget;
    QCheckBox *checkBox;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QWidget *Logmanager)
    {
        if (Logmanager->objectName().isEmpty())
            Logmanager->setObjectName(QString::fromUtf8("Logmanager"));
        Logmanager->resize(628, 627);
        Logmanager->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(Logmanager);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        searchLabel = new QLabel(Logmanager);
        searchLabel->setObjectName(QString::fromUtf8("searchLabel"));
        searchLabel->setMaximumSize(QSize(121, 16777215));
        QFont font;
        font.setFamily(QString::fromUtf8("Verdana"));
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(true);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferAntialias);
        searchLabel->setFont(font);
        searchLabel->setFrameShape(QFrame::Box);
        searchLabel->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(searchLabel);

        verticalSpacer_5 = new QSpacerItem(17, 17, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer_5);

        searchCombo = new QComboBox(Logmanager);
        searchCombo->setObjectName(QString::fromUtf8("searchCombo"));
        searchCombo->setEditable(true);

        horizontalLayout->addWidget(searchCombo);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(30);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        searchButton = new QPushButton(Logmanager);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setEnabled(false);
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setStyleStrategy(QFont::PreferDefault);
        searchButton->setFont(font1);
        searchButton->setCursor(QCursor(Qt::PointingHandCursor));
        searchButton->setFocusPolicy(Qt::StrongFocus);
        searchButton->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 255)"));
        searchButton->setAutoDefault(true);
        searchButton->setDefault(true);

        horizontalLayout_4->addWidget(searchButton);


        gridLayout->addLayout(horizontalLayout_4, 0, 2, 1, 2);

        verticalSpacer = new QSpacerItem(142, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        searchLabel_5 = new QLabel(Logmanager);
        searchLabel_5->setObjectName(QString::fromUtf8("searchLabel_5"));
        QFont font2;
        font2.setPointSize(11);
        font2.setStyleStrategy(QFont::PreferAntialias);
        searchLabel_5->setFont(font2);

        horizontalLayout_2->addWidget(searchLabel_5);

        dateEdit = new QDateEdit(Logmanager);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        QFont font3;
        font3.setStyleStrategy(QFont::PreferAntialias);
        dateEdit->setFont(font3);
        dateEdit->setCursor(QCursor(Qt::PointingHandCursor));
        dateEdit->setDate(QDate(2009, 7, 2));

        horizontalLayout_2->addWidget(dateEdit);

        verticalSpacer_2 = new QSpacerItem(25, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(verticalSpacer_2);

        goButton = new QPushButton(Logmanager);
        goButton->setObjectName(QString::fromUtf8("goButton"));
        QFont font4;
        font4.setPointSize(9);
        font4.setBold(true);
        font4.setWeight(75);
        font4.setStyleStrategy(QFont::PreferAntialias);
        goButton->setFont(font4);
        goButton->setCursor(QCursor(Qt::PointingHandCursor));
        goButton->setStyleSheet(QString::fromUtf8("color:rgb(0, 170, 0)"));

        horizontalLayout_2->addWidget(goButton);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(280, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(verticalSpacer_3, 2, 1, 1, 1);

        tabWidget = new QTabWidget(Logmanager);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(false);
        font5.setWeight(50);
        font5.setStyleStrategy(QFont::PreferDefault);
        tabWidget->setFont(font5);
        tabWidget->setCursor(QCursor(Qt::PointingHandCursor));
        tabWidget->setTabPosition(QTabWidget::North);
        tab1 = new QWidget();
        tab1->setObjectName(QString::fromUtf8("tab1"));
        gridLayout_3 = new QGridLayout(tab1);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        searchLabel_4 = new QLabel(tab1);
        searchLabel_4->setObjectName(QString::fromUtf8("searchLabel_4"));
        QFont font6;
        font6.setPointSize(10);
        font6.setStyleStrategy(QFont::PreferAntialias);
        searchLabel_4->setFont(font6);
        searchLabel_4->setFrameShape(QFrame::NoFrame);
        searchLabel_4->setFrameShadow(QFrame::Plain);

        horizontalLayout_6->addWidget(searchLabel_4);

        logDateLabel = new QLabel(tab1);
        logDateLabel->setObjectName(QString::fromUtf8("logDateLabel"));
        QFont font7;
        font7.setPointSize(10);
        logDateLabel->setFont(font7);
        logDateLabel->setStyleSheet(QString::fromUtf8("color:rgb(170, 0, 127)"));
        logDateLabel->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_6->addWidget(logDateLabel);

        verticalSpacer_4 = new QSpacerItem(280, 14, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(verticalSpacer_4);

        foundLabel = new QLabel(tab1);
        foundLabel->setObjectName(QString::fromUtf8("foundLabel"));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Verdana"));
        font8.setPointSize(11);
        font8.setBold(true);
        font8.setItalic(true);
        font8.setWeight(75);
        font8.setStyleStrategy(QFont::PreferAntialias);
        foundLabel->setFont(font8);
        foundLabel->setStyleSheet(QString::fromUtf8("color:rgb(255, 0, 0)"));

        horizontalLayout_6->addWidget(foundLabel);

        resultLabel = new QLabel(tab1);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        QFont font9;
        font9.setPointSize(9);
        font9.setBold(true);
        font9.setWeight(75);
        font9.setStyleStrategy(QFont::PreferDefault);
        resultLabel->setFont(font9);
        resultLabel->setStyleSheet(QString::fromUtf8("color:rgb(0, 85, 255)"));
        resultLabel->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_6->addWidget(resultLabel);


        gridLayout_3->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        textEdit = new QTextEdit(tab1);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        gridLayout_3->addWidget(textEdit, 1, 0, 1, 1);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QString::fromUtf8("tab2"));
        verticalLayout_3 = new QVBoxLayout(tab2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        filesFoundLabel = new QLabel(tab2);
        filesFoundLabel->setObjectName(QString::fromUtf8("filesFoundLabel"));
        QFont font10;
        font10.setPointSize(11);
        font10.setStyleStrategy(QFont::PreferDefault);
        filesFoundLabel->setFont(font10);
        filesFoundLabel->setStyleSheet(QString::fromUtf8("COLOR:rgb(241, 154, 83)"));
        filesFoundLabel->setFrameShape(QFrame::StyledPanel);

        verticalLayout_3->addWidget(filesFoundLabel);

        tableWidget = new QTableWidget(tab2);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QFont font11;
        font11.setFamily(QString::fromUtf8("System"));
        font11.setPointSize(10);
        font11.setBold(false);
        font11.setItalic(false);
        font11.setWeight(9);
        tableWidget->setFont(font11);
        tableWidget->setStyleSheet(QString::fromUtf8("font: 75 10pt \"System\";"));
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setTextElideMode(Qt::ElideLeft);
        tableWidget->setGridStyle(Qt::SolidLine);
        tableWidget->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(21);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidget->verticalHeader()->setStretchLastSection(false);

        verticalLayout_3->addWidget(tableWidget);

        tabWidget->addTab(tab2, QString());

        gridLayout->addWidget(tabWidget, 4, 0, 1, 4);

        checkBox = new QCheckBox(Logmanager);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        QFont font12;
        font12.setPointSize(10);
        font12.setBold(true);
        font12.setWeight(75);
        checkBox->setFont(font12);
        checkBox->setStyleSheet(QString::fromUtf8("color:rgb(0, 170, 0)"));

        gridLayout->addWidget(checkBox, 2, 3, 1, 1);

        verticalSpacer_6 = new QSpacerItem(142, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_6, 3, 3, 1, 1);

#ifndef QT_NO_SHORTCUT
        searchLabel->setBuddy(searchCombo);
        searchLabel_5->setBuddy(dateEdit);
        filesFoundLabel->setBuddy(dateEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(searchCombo, searchButton);
        QWidget::setTabOrder(searchButton, dateEdit);
        QWidget::setTabOrder(dateEdit, goButton);
        QWidget::setTabOrder(goButton, checkBox);
        QWidget::setTabOrder(checkBox, tabWidget);
        QWidget::setTabOrder(tabWidget, textEdit);
        QWidget::setTabOrder(textEdit, tableWidget);

        retranslateUi(Logmanager);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Logmanager);
    } // setupUi

    void retranslateUi(QWidget *Logmanager)
    {
        Logmanager->setWindowTitle(QApplication::translate("Logmanager", "Log Manager", 0, QApplication::UnicodeUTF8));
        searchLabel->setText(QApplication::translate("Logmanager", "Search &for :", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("Logmanager", "&Search", 0, QApplication::UnicodeUTF8));
        searchLabel_5->setText(QApplication::translate("Logmanager", "Log &Date :", 0, QApplication::UnicodeUTF8));
        dateEdit->setDisplayFormat(QApplication::translate("Logmanager", "d/M/yyyy", 0, QApplication::UnicodeUTF8));
        goButton->setText(QApplication::translate("Logmanager", "&Go", 0, QApplication::UnicodeUTF8));
        searchLabel_4->setText(QApplication::translate("Logmanager", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#00aa00;\">Log Date :</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        logDateLabel->setText(QString());
        foundLabel->setText(QString());
        resultLabel->setText(QApplication::translate("Logmanager", "Results Found : ", 0, QApplication::UnicodeUTF8));
        textEdit->setDocumentTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("Logmanager", "Log", 0, QApplication::UnicodeUTF8));
        filesFoundLabel->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Logmanager", "Log Date", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Logmanager", "Log Size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tableWidget->setToolTip(QApplication::translate("Logmanager", "Shows logs where search is found", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("Logmanager", "Multiple Log Search", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("Logmanager", "Search the entire &Log Database", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Logmanager);
    } // retranslateUi

};

namespace Ui {
    class Logmanager: public Ui_Logmanager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGMANAGER_H
