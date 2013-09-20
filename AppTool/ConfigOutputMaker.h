#pragma once
#include <vector>
#include <map>
#include <string>
using namespace std;

class ConfigOutputMaker
{
public:
	ConfigOutputMaker(void);
	~ConfigOutputMaker(void);
	void addConfigValue(const wstring& key, const wstring& value);
	map<wstring, wstring>& getConfigContainer()
	{
		return configContainer_;
	}
	virtual bool writeConfigToFile();
protected:
	vector<wstring> keyContainer_;
	map<wstring, wstring> configContainer_;
	string configFileName_;
};

