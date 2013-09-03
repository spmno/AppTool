#include "SettingCenter.h"
#include <Windows.h>
#include <fstream>
#include <QtCore/QString>
#include <QtCore/qdir.h>
#include <QMessageBox>
#include <qtextcodec.h>
#include "3party\jsoncpp-src-0.5.0\include\json\json.h"
using namespace std;

SettingCenter::SettingCenter(void)
{
}


SettingCenter::~SettingCenter(void)
{
}

void SettingCenter::loadSetting()
{
	// read and parse json file

	QString currentDir = QDir::currentPath();
	string jsonFileName = currentDir.toStdString() + "/setting.json";
	wchar_t wideJsonFileName[260];
	ifstream jsonFileStream;
	MultiByteToWideChar(CP_UTF8, 0, jsonFileName.c_str(), -1, wideJsonFileName, 260);
	jsonFileStream.open(wideJsonFileName);

	if (!jsonFileStream.is_open()) {
		QMessageBox::information(NULL, jsonFileName.c_str(), QStringLiteral("配置文件错误"));
		exit(-1);
	}
	Json::Reader reader;
	Json::Value jsonObject;
	if (!reader.parse(jsonFileStream, jsonObject, false)) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("解析文件错误"));
		exit(-1);
	}

	Json::Value models = jsonObject["Model"];
	Json::Value filters = jsonObject["Filter"];
	Json::Value lastSourceDir = jsonObject["SourceDir"];

	// save model and filter to globa setting
	for (int i = 0; i < models.size(); ++i) {
		modelContainer.push_back(models[i].asString());
	}

	for (int i = 0; i < filters.size(); ++i) {
		filterContainer.push_back(filters[i].asString());
	}

	if (!lastSourceDir.isNull()) {
		sourceDir = lastSourceDir.asString().c_str();
	}
}

bool SettingCenter::writeLastSourceDirToFile(QString& dir) 
{
	QString currentDir = QDir::currentPath();
	string jsonFileName = currentDir.toStdString() + "/setting.json";
	wchar_t wideJsonFileName[260];
	ifstream jsonFileStream;
	MultiByteToWideChar(CP_UTF8, 0, jsonFileName.c_str(), -1, wideJsonFileName, 260);
	jsonFileStream.open(wideJsonFileName);
	if (!jsonFileStream.is_open()) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("配置文件错误"));
		return false;
	}
	Json::Reader reader;
	Json::Value jsonObject;
	if (!reader.parse(jsonFileStream, jsonObject, false)) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("解析文件错误"));
		return false;
	}
	jsonFileStream.close();

	jsonObject["SourceDir"] = dir.toStdString();
	ofstream jsonOutStream;
	Json::FastWriter writer;
	jsonOutStream.open(wideJsonFileName);
	if (!jsonOutStream.is_open()) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("输出配置文件错误"));
		return false;
	}
	string jsonFileContent = writer.write(jsonObject);
	jsonOutStream << jsonFileContent;

	return true;
}

SettingCenter& SettingCenter::getInstance()
{
	static SettingCenter instance;
	return instance;
}
