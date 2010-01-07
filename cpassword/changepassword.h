#ifndef CHANGEPASSWD_H_INCLUDED
#define CHANGEPASSWD_H_INCLUDED

#include <QWidget>

QT_BEGIN_NAMESPACE

class QPushButton;
class QComboBox;
class QLabel;
class QLineEdit;
class QGroupBox;
class QSettings;

QT_END_NAMESPACE

class ChangePassword :public QWidget
{
    Q_OBJECT

private:
    QWidget *formWidget;
    QSettings *settings;
    QLabel *label,*label_2,*label_3,*label_4;
    QComboBox *userCombo;
    QGroupBox *groupBox2;
    QLineEdit *passwordLe,*le1,*le2;
    QPushButton *saveButton,*cancelButton;
    QWidget* loadUiFile();
    bool authenticate(const QVariant& passwd,QString userno);

private slots:

    void on_saveButton_pressed();
    void on_cancelButton_pressed();
    void on_passwordLe_returnPressed();
    void on_le1_textChanged();

signals:
        void destroycp();
public:

    ChangePassword();
    ~ChangePassword();


};

#endif // CHANGEPASSWD_H_INCLUDED
