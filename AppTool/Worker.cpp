#include "Worker.h"
#include <windows.h>
#include <shellapi.h>
#include <qdir.h>
#include <qmessagebox.h>
#include "SettingCenter.h"

Worker::Worker(void)
{
}


Worker::~Worker(void)
{
}

bool Worker::startAppImp()
{
	//prepare -- make dir name, get filter
	SettingCenter settingCenter = SettingCenter::getInstance();
	QString targetDir = settingCenter.getTargetDir();
	QString sourceDir = settingCenter.getSourceDir();
	vector<string>& filter = settingCenter.getFilter();
	//copy files
	if (!copyFilesWithFilter(sourceDir, targetDir, filter)) {
		QMessageBox::information(NULL, QStringLiteral("错误"), QStringLiteral("复制错误"));
		return false;
	}

	//del old zip
	QDir toDir(targetDir);
	QString zipName = "F33App.zip";
	if (toDir.exists(zipName)) {
		toDir.remove(zipName);
	}

	//edit appinfo
	QString appInfoPath = targetDir + "\\Config\\AppConfigInfo.dat";
	QString editCommand = "notepad";
	exeCommand(editCommand, appInfoPath);

	//create md5
	QString md5PathFormat("%1\\%2");
	QString md5Path = md5PathFormat.arg(settingCenter.getCurrentModelName()).arg("F33APP");
	QString md5Command = "MD5Console";
	QString md5ParameterFormat("%1 %2");
	QString md5UpdateMethod = settingCenter.getUpdateMethod();
	QString md5Parameter = md5ParameterFormat.arg(md5Path).arg(md5UpdateMethod);
	exeCommand(md5Command, md5Parameter);

	//pagage zip
	QString zipCommand = "zip";
	QString zipParameterFormat("%1 %2 %3 %4");
	QString zipParameter = zipParameterFormat.arg("-1").arg("-r").arg("F33APP.zip").arg("F33APP");
	exeCommand(zipCommand, zipParameter);

	return true;
}

bool Worker::copyFilesWithFilter(const QString& fromDir, const QString& toDir, const vector<string>& filter)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	
	if (!targetDir.exists()) {
		if (!targetDir.mkdir(targetDir.absolutePath())) {
			QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("创建目标目录失败"));
			return false;
		}
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	for (auto fileInfo : fileInfoList) {
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..") {
			continue;
		}

		if (fileInfo.isDir()) {
			if (!copyFilesWithFilter(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()), filter)) {
				return false;
			}
		} else {
			bool findFlag = false;
			for (int i = 0; i < filter.size(); ++i) {
				if (targetDir.filePath(fileInfo.fileName()).indexOf(filter[i].c_str()) != -1) {
					findFlag = true;
				}
			}
			if (findFlag) {
				continue;
			}
			if (targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}
			if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))) {
				QMessageBox::information(NULL, (fileInfo.fileName()), QStringLiteral("复制文件失败"));
				return false;
			}
		}
	}
	return true;
}

void Worker::exeCommand(const QString& command, const QString& parameter)
{
	SHELLEXECUTEINFOA shExecInfo = {0};

	shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);

	shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

	shExecInfo.hwnd = NULL;

	shExecInfo.lpVerb = NULL;

	shExecInfo.lpFile = command.toStdString().c_str();

	shExecInfo.lpParameters = parameter.toStdString().c_str();

	shExecInfo.lpDirectory = NULL;

	shExecInfo.nShow = SW_HIDE;

	shExecInfo.hInstApp = NULL;

	ShellExecuteExA(&shExecInfo);

	WaitForSingleObject(shExecInfo.hProcess,INFINITE);
}