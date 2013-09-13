#include "CustomDesignConfigOutputMaker.h"
#include "SettingCenter.h"

CustomDesignConfigOutputMaker::CustomDesignConfigOutputMaker(void)
{
	keyContainer_.push_back("$Product-Model");
	configContainer_["$Product-Model"] = SettingCenter::getInstance().getCurrentModelName().toStdString();
	keyContainer_.push_back("$Sales-Area");
	configContainer_["$Sales-Area"] = "Home";
	keyContainer_.push_back("$Sales-Channel");
	configContainer_["$Sales-Channel"] = "4S-Store-Way";
	keyContainer_.push_back("$Edition-Level");
	configContainer_["$Edition-Level"] = "Deluxe-Edition";
	keyContainer_.push_back("$Operating-System");
	configContainer_["$Operating-System"] = "Windows-CE";
	keyContainer_.push_back("$Hardware-Configuration");
	configContainer_["$Hardware-Configuration"] = "A10-Flash256M-RAM512M-Nav90M-Resolution1024x600";

	configFileName_ = "CustomInfo.conf";
}


CustomDesignConfigOutputMaker::~CustomDesignConfigOutputMaker(void)
{

}
