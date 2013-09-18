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

void ConfigOutputMaker::addConfigValue(const wstring& key, const wstring& value) 
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
/*
	wofstream configFile;
	configFile.open(wideConfigFileName);
	if (!configFile.is_open()) {
		return false;
	}
	for (auto configKey : keyContainer_) {
		configFile << configKey << "," << configContainer_[configKey] << endl;
	}
	*/
	FILE* outputFile = _wfopen(wideConfigFileName, L"w, ccs=UNICODE");
	if (outputFile == NULL) {
		return false;
	}
	
	for (auto configKey : keyContainer_) {
		//configFile << configKey << "," << configContainer_[configKey] << endl;
		fwrite(configKey.c_str(), sizeof(wchar_t), configKey.length(), outputFile);
		fwrite(L",", sizeof(wchar_t), 1, outputFile);
		fwrite(configContainer_[configKey].c_str(), sizeof(wchar_t), configContainer_[configKey].length(), outputFile);
		fwrite(L"\n", sizeof(wchar_t), 1, outputFile);
	}
	fclose(outputFile);
	return true;
}