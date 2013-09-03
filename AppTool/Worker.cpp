#include "Worker.h"
#include <windows.h>
#include <shellapi.h>
#include <qdir.h>
#include <qmessagebox.h>
#include <qprogressdialog.h>
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
	QString targetModelDir = targetDir + "/" + settingCenter.getCurrentModelName() + "/F33APP";
	QString sourceDir = settingCenter.getSourceDir();
	vector<string>& filter = settingCenter.getFilter();
	
	//copy files
	if (!copyFilesWithFilter(sourceDir, targetModelDir, filter)) {
		QMessageBox::information(NULL, QStringLiteral("错误"), QStringLiteral("复制错误"));
		return false;
	}

	//del old zip
	QDir toDir(targetModelDir);
	QString zipName = "F33App.zip";
	if (toDir.exists(zipName)) {
		toDir.remove(zipName);
	}
	
	//edit appinfo
	QString appInfoPath = targetModelDir + "/Config/AppConfigInfo.dat";
	QString editCommand = "notepad";
	exeCommandUtillExit(editCommand, appInfoPath);

	//create md5
	QString md5PathFormat("%1\\%2");
	QString md5Path = md5PathFormat.arg(settingCenter.getCurrentModelName()).arg("F33APP");
	QString md5Command = "MD5Console";
	QString md5ParameterFormat("%1 %2");
	QString md5UpdateMethod = settingCenter.getUpdateMethod();
	QString md5Parameter = md5ParameterFormat.arg(md5Path).arg(md5UpdateMethod);
	exeCommandUtillExit(md5Command, md5Parameter);

	//pagage zip
	QString oldPath = QDir::currentPath();
	QString modelPath = oldPath + "/" + settingCenter.getCurrentModelName();
	QDir::setCurrent(modelPath);
	QString zipCommand = oldPath + "/zip.exe";
	QString zipParameterFormat("%1 %2 %3 %4");
	QString zipParameter = zipParameterFormat.arg("-1").arg("-r").arg("F33APP.zip").arg("F33APP");
	exeCommandUtillExit(zipCommand, zipParameter);
	QDir::setCurrent(oldPath);

	//open dir
	wchar_t wideOpenDirPath[260];
	string modelStdPath = modelPath.toStdString();
	MultiByteToWideChar(CP_UTF8, 0, modelStdPath.c_str(), -1, wideOpenDirPath, 260);
	QString openCommand = "explorer";
	exeCommand(modelPath, "", false);

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
	QProgressDialog progressDialog;
	progressDialog.setLabelText(QStringLiteral("复制文件"));
	progressDialog.setRange(0, fileInfoList.size());
	progressDialog.setModal(false);
	progressDialog.show();
	int currentPosition = -1;
	for (auto fileInfo : fileInfoList) {
		progressDialog.setValue(++currentPosition);
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
	progressDialog.close();
	return true;
}

void Worker::exeCommandUtillExit(const QString& command, const QString& parameter)
{
	exeCommand(command, parameter, true);
}

void Worker::exeCommand(const QString& command, const QString& parameter, bool waitFlag)
{
	SHELLEXECUTEINFO shExecInfo = {0};

	shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);

	shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;

	shExecInfo.hwnd = NULL;

	shExecInfo.lpVerb = L"open";

	wchar_t wideCommand[64];
	string commandString = command.toStdString();
	MultiByteToWideChar(CP_UTF8, 0, commandString.c_str(), -1, wideCommand, 64);
	shExecInfo.lpFile = wideCommand;

	wchar_t wideParameter[260];
	string parameterString = parameter.toStdString();
	MultiByteToWideChar(CP_UTF8, 0, parameterString.c_str(), -1, wideParameter, 260);
	shExecInfo.lpParameters = wideParameter;

	shExecInfo.lpDirectory = NULL;

	shExecInfo.nShow = SW_SHOWNORMAL;

	shExecInfo.hInstApp = NULL;

	bool shellResult = ShellExecuteEx(&shExecInfo);

	if (!shellResult) {
		QString errorFormat("error code = %1");
		QString error = errorFormat.arg(GetLastError());
		QMessageBox::information(NULL, "ERROR", error);
	}

	if (waitFlag) {
		WaitForSingleObject(shExecInfo.hProcess,INFINITE);
	}
}