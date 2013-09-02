#pragma once
#include <vector>
#include <string>
#include <qstring.h>
using namespace std;

class SettingCenter
{

public:
	~SettingCenter(void);
	enum UPDATE_METHOD{
		ALL,
		SETTING,
		COMPARE
	};

	void loadSetting();
	static SettingCenter& getInstance();
	vector<string>& getModels() 
	{
		return modelContainer;
	}
	void setUpdateMethod(UPDATE_METHOD method)
	{
		updateMethod = method;
		switch (method)
		{
		case SettingCenter::ALL:
			updateMethodString = "ALL";
			break;
		case SettingCenter::SETTING:
			updateMethodString = "SETTING";
			break;
		case SettingCenter::COMPARE:
			updateMethodString = "COMPARE";
			break;
		default:
			break;
		}
	}
	QString& getUpdateMethod()
	{
		return updateMethodString;
	}
	void setModelIndex(int index)
	{
		modelIndex = index;
		currentModelName = modelContainer[index].c_str();
	}
	QString& getCurrentModelName() 
	{
		return currentModelName;
	}
	QString& getSourceDir()
	{
		return sourceDir;
	}
	void setSourceDir(QString& dir) 
	{
		sourceDir = dir;
	}
	QString& getTargetDir()
	{
		return targetDir;
	}
	void setTargetDir(QString& dir) 
	{
		targetDir = dir;
	}
	vector<string>& getFilter()
	{
		return filterContainer;
	}
private:
	SettingCenter(void);
	vector<string> modelContainer;
	vector<string> filterContainer;
	UPDATE_METHOD updateMethod;
	QString updateMethodString;
	int modelIndex;
	QString currentModelName;
	QString sourceDir;
	QString targetDir;
};

