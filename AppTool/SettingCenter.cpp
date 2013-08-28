#include "SettingCenter.h"
#include <fstream>
#include <QtCore/QString>
#include <QtCore/qdir.h>
#include <QMessageBox>
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
	QString jsonFileName = currentDir + "/setting.json";
	ifstream jsonFileStream;
	jsonFileStream.open(jsonFileName.toStdString().c_str());
	if (!jsonFileStream.is_open()) {
		QMessageBox::information(NULL, "ERROR", "配置文件错误");
		exit(-1);
	}
	Json::Reader reader;
	Json::Value jsonObject;
	if (!reader.parse(jsonFileStream, jsonObject, false)) {
		QMessageBox::information(NULL, "ERROR", "解析文件错误");
		exit(-1);
	}

	Json::Value models = jsonObject["Model"];
	Json::Value filters = jsonObject["Filter"];

	// save model and filter to globa setting
	for (int i = 0; i < models.size(); ++i) {
		modelContainer.push_back(models[i].asString());
	}

	for (int i = 0; i < filters.size(); ++i) {
		filterContainer.push_back(filters[i].asString());
	}
}

SettingCenter& SettingCenter::getInstance()
{
	static SettingCenter instance;
	return instance;
}