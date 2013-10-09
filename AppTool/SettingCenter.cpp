#include "SettingCenter.h"
#include <Windows.h>
#include <fstream>
#include <QtCore/QString>
#include <QtCore/qdir.h>
#include <QMessageBox>
#include <qtextcodec.h>
#include "3party\jsoncpp-src-0.5.0\include\json\json.h"
using namespace std;

SettingCenter SettingCenter::instance;

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
		QMessageBox::information(NULL, jsonFileName.c_str(), QStringLiteral("�����ļ�����"));
		exit(-1);
	}
	Json::Reader reader;
	Json::Value jsonObject;
	if (!reader.parse(jsonFileStream, jsonObject, false)) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("�����ļ�����"));
		exit(-1);
	}

	Json::Value models = jsonObject["Model"];
	//Json::Value filters = jsonObject["Filter"];
	Json::Value lastSourceDir = jsonObject["SourceDir"];

	// save model and filter to globa setting
	for (int i = 0; i < models.size(); ++i) {
		modelContainer.push_back(models[i].asString());
	}

	/* remove the filter to single file
	for (int i = 0; i < filters.size(); ++i) {
		filterContainer.push_back(filters[i].asString());
	}
	*/

	if (!lastSourceDir.isNull()) {
		sourceDir = lastSourceDir.asString().c_str();
		QDir dir(sourceDir);
		if (!dir.exists()) {
			sourceDir = QDir::currentPath();
		}
	} else {
		sourceDir = QDir::currentPath();
	}
}

void SettingCenter::loadFilter()
{
	string jsonFileName = targetDir.toStdString() + "/Filter/" + currentModelName.toStdString() + ".json";
	wchar_t wideJsonFileName[260];
	ifstream jsonFileStream;
	MultiByteToWideChar(CP_UTF8, 0, jsonFileName.c_str(), -1, wideJsonFileName, 260);
	jsonFileStream.open(wideJsonFileName);
	if (!jsonFileStream.is_open()) {
		MessageBox(NULL, wideJsonFileName, L"Filter error", MB_TOPMOST);
		return ;
	}
	Json::Reader reader;
	Json::Value jsonObject;
	if (!reader.parse(jsonFileStream, jsonObject, false)) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("�����ļ�����"));
		return ;
	}
	jsonFileStream.close();
	Json::Value filters = jsonObject["Filter"];
	filterContainer.clear();
	for (int i = 0; i < filters.size(); ++i) {
		filterContainer.push_back(filters[i].asString());
	}

	Json::Value mapModel = jsonObject["MapModel"];
	if (mapModel.isNull()) {
		instance.currentMapModelName = currentModelName;
	} else {
		currentMapModelName = mapModel.asCString();
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
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("�����ļ�����"));
		return false;
	}
	Json::Reader reader;
	Json::Value jsonObject;
	if (!reader.parse(jsonFileStream, jsonObject, false)) {
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("�����ļ�����"));
		return false;
	}
	jsonFileStream.close();

	jsonObject["SourceDir"] = dir.toStdString();
	ofstream jsonOutStream;
	Json::FastWriter writer;
	jsonOutStream.open(wideJsonFileName);
	if (!jsonOutStream.is_open()) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
		QMessageBox::information(NULL, QStringLiteral("ERROR"), QStringLiteral("��������ļ�����"));
		return false;
	}
	string jsonFileContent = writer.write(jsonObject);
	jsonOutStream << jsonFileContent;

	return true;
}

SettingCenter& SettingCenter::getInstance()
{
	
	return instance;
}
