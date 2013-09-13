#include "AppConfigOutputMaker.h"
#include "SettingCenter.h"

AppConfigOutputMaker::AppConfigOutputMaker(void)
{
	keyContainer_.push_back("$GpsCardPath");
	configContainer_["$GpsCardPath"] = "\\StorageCard\\";
	keyContainer_.push_back("$MediaCardPath");
	configContainer_["$MediaCardPath"] = "\\StorageCard\\";
	keyContainer_.push_back("$HardDiskPath");
	configContainer_["$HardDiskPath"] = "\\USB\\";
	keyContainer_.push_back("$VersionInfo");
	configContainer_["$VersionInfo"] = "2013-01-05-S208-A537";
	keyContainer_.push_back("$ProductNo");
	configContainer_["$ProductNo"] = SettingCenter::getInstance().getCurrentModelName().toStdString();
	keyContainer_.push_back("$AnimatorLevel");
	configContainer_["$AnimatorLevel"] = "1";
	keyContainer_.push_back("$VolumeValueMin");
	configContainer_["$VolumeValueMin"] = "50";
	keyContainer_.push_back("$VolumeValueMax");
	configContainer_["$VolumeValueMax"] = "100";
	keyContainer_.push_back("$DvrCardPath");
	configContainer_["$DvrCardPath"] = "\\CardC\\";
	keyContainer_.push_back("$DvrCardVolumeName");
	configContainer_["$DvrCardVolumeName"] = "SD Card C";
	keyContainer_.push_back("$ReverseVideoCardPath");
	configContainer_["$ReverseVideoCardPath"] = "\\CardC\\";
	keyContainer_.push_back("$ReverseVideoSwitch");
	configContainer_["$ReverseVideoSwitch"] = "1";
	keyContainer_.push_back("$SkinStyle");
	configContainer_["$SkinStyle"] = "1";
	keyContainer_.push_back("$AlternativeLogoPath");
	configContainer_["$AlternativeLogoPath"] = "\\FlashApp\\logo\\";

	configFileName_ = "AppConfigInfo.dat";
}


AppConfigOutputMaker::~AppConfigOutputMaker(void)
{
}
