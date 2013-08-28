#pragma once
#include <vector>
#include <string>
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
	}
	void setModelIndex(int index)
	{
		modelIndex = index;
	}
private:
	SettingCenter(void);
	vector<string> modelContainer;
	vector<string> filterContainer;
	UPDATE_METHOD updateMethod;
	int modelIndex;
};

