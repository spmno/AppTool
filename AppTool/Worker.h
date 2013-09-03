#pragma once
#include <qstring.h>
#include <string>
#include <vector>
using namespace std;

class Worker
{
public:
	Worker(void);
	~Worker(void);
	bool startAppImp();
private:
	bool copyFilesWithFilter(const QString& sourceDir, const QString& targetDir, const vector<string>& filter);
	void exeCommandUtillExit(const QString& command, const QString& parameter);
	void exeCommand(const QString& command, const QString& parameter, bool waitFlag);
};

