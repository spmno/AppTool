#include "apptool.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "SettingCenter.h"
AppTool::AppTool(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//this->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
	SettingCenter& settingCenter = SettingCenter::getInstance();
	vector<string>& models = settingCenter.getModels();
	for (vector<string>::iterator iter = models.begin(); iter != models.end(); ++iter) {
		ui.modelComboBox->addItem((*iter).c_str());
	}
	
}

AppTool::~AppTool()
{

}

void AppTool::selectSourceDictionary()
{
	QString initialFolder = QDir::currentPath();
    QFileDialog fileDlg( this, tr("Please select folder"), initialFolder );
    fileDlg.setFileMode(QFileDialog::DirectoryOnly);
	QString sourceDir = fileDlg.getExistingDirectory();
	ui.sourceLineEdit->setText(sourceDir);
}

void AppTool::selectTargetDictionary()
{
	QString initialFolder = QDir::currentPath();
    QFileDialog fileDlg( this, tr("Please select folder"), initialFolder );
    fileDlg.setFileMode(QFileDialog::DirectoryOnly);
	QString targetDir = fileDlg.getExistingDirectory();
	ui.targetLineEdit->setText(targetDir);
}

void AppTool::startApp()
{
	SettingCenter& settingCenter = SettingCenter::getInstance();
	settingCenter.setModelIndex(ui.modelComboBox->currentIndex());
	if (ui.allRadioButton->isChecked()) {
		settingCenter.setUpdateMethod(SettingCenter::ALL);
	} else if (ui.settingRadioButton->isChecked()) {
		settingCenter.setUpdateMethod(SettingCenter::SETTING);
	} else if (ui.compareRadioButton->isChecked()) {
		settingCenter.setUpdateMethod(SettingCenter::COMPARE);
	}

}


void AppTool::exitApp()
{
	exit(0);
}