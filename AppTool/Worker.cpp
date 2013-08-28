#include "Worker.h"
#include <qdir.h>
#include <qmessagebox.h>

Worker::Worker(void)
{
}


Worker::~Worker(void)
{
}

bool Worker::copyFilesWithFilter(const QString& fromDir, const QString& toDir, const vector<string>& filter)
{
	QDir sourceDir(fromDir);
	QDir targetDir(toDir);
	
	if (!targetDir.exists()) {
		if (!targetDir.mkdir(targetDir.absolutePath())) {
			QMessageBox::information(NULL, "ERROR", "创建目标目录失败");
		}
	}

	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	for (auto fileInfo : fileInfoList) {
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..") {
			continue;
		}

		if (fileInfo.isDir()) {
			if (!copyFilesWithFilter(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()), filter)) {
				return false;
			}
		} else {
			bool findFlag = false;
			for (int i = 0; i < filter.size(); ++i) {
				if (targetDir.filePath(fileInfo.fileName()).indexOf(filter[i].c_str()) != -1) {
					findFlag = true;
				}
			}

			if (findFlag) {
				continue;
			}

			if (targetDir.exists(fileInfo.fileName())) {
				targetDir.remove(fileInfo.fileName());
			}

			if (!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName()))) {
				QMessageBox::information(NULL, fileInfo.fileName(), "复制文件失败");
				return false;
			}
		}
	}
	return true;
}