#include "apptool.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "SettingCenter.h"
#include "Worker.h"
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
	if (!settingCenter.getSourceDir().isEmpty()) {
		ui.sourceLineEdit->setText(settingCenter.getSourceDir());
	}
	ui.targetLineEdit->setText(QDir::currentPath());
	ui.allRadioButton->setChecked(true);
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
	if (!sourceDir.isEmpty()) {
		ui.sourceLineEdit->setText(sourceDir);
		SettingCenter::getInstance().writeLastSourceDirToFile(sourceDir);
	}

}

void AppTool::selectTargetDictionary()
{
	QString initialFolder = QDir::currentPath();
    QFileDialog fileDlg( this, tr("Please select folder"), initialFolder );
    fileDlg.setFileMode(QFileDialog::DirectoryOnly);
	QString targetDir = fileDlg.getExistingDirectory();
	if (!targetDir.isEmpty()) {
		ui.targetLineEdit->setText(targetDir);
	}
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

	if (ui.sourceLineEdit->text().isEmpty()) {
		QMessageBox::information(NULL, QStringLiteral("错误"), QStringLiteral("没有设置源目录"));
		return;
	}
	settingCenter.setSourceDir(ui.sourceLineEdit->text());

	if (ui.targetLineEdit->text().isEmpty()) {
		QMessageBox::information(NULL, QStringLiteral("错误"), QStringLiteral("没有设置目标目录"));
		return;
	}
	settingCenter.setTargetDir(ui.targetLineEdit->text());
	Worker worker;
	worker.startAppImp();
}


void AppTool::exitApp()
{
	exit(0);
}