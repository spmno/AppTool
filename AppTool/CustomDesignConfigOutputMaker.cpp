#include "CustomDesignConfigOutputMaker.h"
#include "SettingCenter.h"

CustomDesignConfigOutputMaker::CustomDesignConfigOutputMaker(void)
{
	configContainer_["$Product-Model"] = SettingCenter::getInstance().getCurrentModelName().toStdString();
	configContainer_["$Sales-Area"] = "Home";
	configContainer_["$Sales-Channel"] = "4S-Store-Way";
	configContainer_["$Edition-Level"] = "Deluxe-Edition";
	configContainer_["$Operating-System"] = "Windows-CE";
	configContainer_["$Hardware-Configuration"] = "A10-Flash256M-RAM512M-Nav90M-Resolution1024x600";

	configFileName_ = "CustomDesign.conf";
}


CustomDesignConfigOutputMaker::~CustomDesignConfigOutputMaker(void)
{

}
