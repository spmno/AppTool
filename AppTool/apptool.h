#ifndef APPTOOL_H
#define APPTOOL_H

#include <QtWidgets/QDialog>
#include "ui_apptool.h"

class AppTool : public QDialog
{
	Q_OBJECT

public:
	AppTool(QWidget *parent = 0);
	~AppTool();

private:
	Ui::AppToolClass ui;
	
protected slots:
	void selectSourceDictionary();
	void selectTargetDictionary();
	void startApp();
	void exitApp();
};

#endif // APPTOOL_H
