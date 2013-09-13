#include "ConfigOutputMaker.h"
#include <fstream>
#include <Windows.h>
#include "SettingCenter.h"

ConfigOutputMaker::ConfigOutputMaker(void)
{

}


ConfigOutputMaker::~ConfigOutputMaker(void)
{

}

void ConfigOutputMaker::addConfigValue(const string& key, const string& value) 
{
	configContainer_[key] = value;
}

bool ConfigOutputMaker::writeConfigToFile()
{
	wchar_t wideConfigFileName[260];
	SettingCenter settingCenter = SettingCenter::getInstance();
	string configFileName = settingCenter.getTargetDir().toStdString() + 
		"/" + settingCenter.getCurrentModelName().toStdString() + 
		"/F33APP/Config/" + configFileName_;
	MultiByteToWideChar(CP_UTF8, 0, configFileName.c_str(), -1, wideConfigFileName, 260);
	ofstream configFile;
	configFile.open(wideConfigFileName);
	if (!configFile.is_open()) {
		return false;
	}
	for (auto configItem : configContainer_) {
		configFile << configItem.first << "," << configItem.second << endl;
	}
	return true;
}