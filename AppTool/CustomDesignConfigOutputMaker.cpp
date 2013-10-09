#include "CustomDesignConfigOutputMaker.h"
#include "SettingCenter.h"
#include <fstream>

using namespace std;

CustomDesignConfigOutputMaker::CustomDesignConfigOutputMaker(void)
{
	keyContainer_.push_back(L"$Product-Model");
	configContainer_[L"$Product-Model"] = SettingCenter::getInstance().getCurrentMapModelName();
	keyContainer_.push_back(L"$Sales-Area");
	configContainer_[L"$Sales-Area"] = L"Home";
	keyContainer_.push_back(L"$Sales-Channel");
	configContainer_[L"$Sales-Channel"] = L"4S-Store-Way";
	keyContainer_.push_back(L"$Edition-Level");
	configContainer_[L"$Edition-Level"] = L"Deluxe-Edition";
	keyContainer_.push_back(L"$Operating-System");
	configContainer_[L"$Operating-System"] = L"Windows-CE";
	keyContainer_.push_back(L"$Hardware-Configuration");
	configContainer_[L"$Hardware-Configuration"] = L"A10-Flash256M-RAM512M-Nav90M-Resolution1024x600";

	configFileName_ = "CustomInfo.conf";
}


CustomDesignConfigOutputMaker::~CustomDesignConfigOutputMaker(void)
{

}

bool CustomDesignConfigOutputMaker::writeConfigToFile()
{
	wchar_t wideConfigFileName[260];
	SettingCenter& settingCenter = SettingCenter::getInstance();
	string configFileName = settingCenter.getTargetDir().toStdString() + 
		"/" + settingCenter.getCurrentModelName().toStdString() + 
		"/F33APP/Config/" + configFileName_;
	MultiByteToWideChar(CP_UTF8, 0, configFileName.c_str(), -1, wideConfigFileName, 260);

	wofstream configFile;
	configFile.open(wideConfigFileName);
	if (!configFile.is_open()) {
		return false;
	}
	for (auto configKey : keyContainer_) {
		configFile << configKey << "," << configContainer_[configKey] << endl;
	}
	
	return true;
}