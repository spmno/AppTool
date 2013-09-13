#pragma once
#include <map>
#include <string>
using namespace std;

class ConfigOutputMaker
{
public:
	ConfigOutputMaker(void);
	~ConfigOutputMaker(void);
	void addConfigValue(const string& key, const string& value);
	map<string, string>& getConfigContainer()
	{
		return configContainer_;
	}
	bool writeConfigToFile();
protected:
	map<string, string> configContainer_;
	string configFileName_;
};

