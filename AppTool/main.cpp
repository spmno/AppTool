#include "apptool.h"
#include <QtWidgets/QApplication>
#include <QtCore/qfile.h>
#include <qtextcodec.h>
#include "SettingCenter.h"
int main(int argc, char *argv[])
{
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8")); 
	QApplication a(argc, argv);
	
	QFile styleSheet(":/AppTool/res/qss/main_dialog.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return -1;
    }
    //a.setStyleSheet(styleSheet.readAll());
	SettingCenter& settingCenter = SettingCenter::getInstance();
	settingCenter.loadSetting();
	AppTool w;
	w.show();
	return a.exec();
}
