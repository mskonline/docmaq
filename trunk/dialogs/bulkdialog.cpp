#include "bulkdialog.h"


bulkdialog::bulkdialog()
{
	setupUi(this);
	connect(bprint,SIGNAL(pressed()),this,SLOT(continueact()));
}

