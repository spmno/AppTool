#include "AppConfigOutputMaker.h"
#include "SettingCenter.h"

AppConfigOutputMaker::AppConfigOutputMaker(void)
{
	configContainer_["$GpsCardPath"] = "\\StorageCard\\";
	configContainer_["$MediaCardPath"] = "\\StorageCard\\";
	configContainer_["$HardDiskPath"] = "\\USB\\";
	configContainer_["$VersionInfo"] = "2013-01-05-S208-A537";
	configContainer_["$ProductNo"] = SettingCenter::getInstance().getCurrentModelName().toStdString();
	configContainer_["$AnimatorLevel"] = "1";
	configContainer_["$VolumeValueMin"] = "50";
	configContainer_["$VolumeValueMax"] = "100";
	configContainer_["$DvrCardPath"] = "\\CardC\\";
	configContainer_["$DvrCardVolumeName"] = "SD Card C";
	configContainer_["$ReverseVideoCardPath"] = "\\CardC\\";
	configContainer_["$ReverseVideoSwitch"] = "1";
	configContainer_["$SkinStyle"] = "1";
	configContainer_["$AlternativeLogoPath"] = "\\FlashApp\\logo\\";

	configFileName_ = "AppConfigInfo.dat";
}


AppConfigOutputMaker::~AppConfigOutputMaker(void)
{
}
