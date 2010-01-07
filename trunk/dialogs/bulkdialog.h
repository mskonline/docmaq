#include <QtGui>
#include "ui_bulkdialog.h"


class bulkdialog : public QWidget, public Ui::bulkdialog
{

	Q_OBJECT
	
    public :
	bulkdialog();
	
	signals :
	void contin();

	public slots :
	void continueact(){ emit contin();}
};
