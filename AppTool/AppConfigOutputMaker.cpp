#include "AppConfigOutputMaker.h"
#include "SettingCenter.h"

AppConfigOutputMaker::AppConfigOutputMaker(void)
{
	keyContainer_.push_back(L"$GpsCardPath");
	configContainer_[L"$GpsCardPath"] = L"\\StorageCard\\";
	keyContainer_.push_back(L"$MediaCardPath");
	configContainer_[L"$MediaCardPath"] = L"\\StorageCard\\";
	keyContainer_.push_back(L"$HardDiskPath");
	configContainer_[L"$HardDiskPath"] = L"\\USB\\";
	keyContainer_.push_back(L"$VersionInfo");
	configContainer_[L"$VersionInfo"] = L"2013-01-05-S208-A537";
	keyContainer_.push_back(L"$ProductNo");
	configContainer_[L"$ProductNo"] = SettingCenter::getInstance().getCurrentModelNameW();
	keyContainer_.push_back(L"$AnimatorLevel");
	configContainer_[L"$AnimatorLevel"] = L"1";
	keyContainer_.push_back(L"$VolumeValueMin");
	configContainer_[L"$VolumeValueMin"] = L"50";
	keyContainer_.push_back(L"$VolumeValueMax");
	configContainer_[L"$VolumeValueMax"] = L"100";
	keyContainer_.push_back(L"$DvrCardPath");
	configContainer_[L"$DvrCardPath"] = L"\\CardC\\";
	keyContainer_.push_back(L"$DvrCardVolumeName");
	configContainer_[L"$DvrCardVolumeName"] = L"SD Card C";
	keyContainer_.push_back(L"$ReverseVideoCardPath");
	configContainer_[L"$ReverseVideoCardPath"] = L"\\CardC\\";
	keyContainer_.push_back(L"$ReverseVideoSwitch");
	configContainer_[L"$ReverseVideoSwitch"] = L"0";
	keyContainer_.push_back(L"$SkinStyle");
	configContainer_[L"$SkinStyle"] = L"1";
	keyContainer_.push_back(L"$AlternativeLogoPath");
	configContainer_[L"$AlternativeLogoPath"] = L"\\FlashApp\\logo\\";

	configFileName_ = "AppConfigInfo.dat";
}


AppConfigOutputMaker::~AppConfigOutputMaker(void)
{
}
