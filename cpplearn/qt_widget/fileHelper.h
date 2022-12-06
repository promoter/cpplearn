#ifndef fileHelper_h_
#define fileHelper_h_
#include <QString>

class FileHelper
{
public:
    static QString CreateDir(const QString &localDirPath);

    // 文件是否被别的 程序 打开占用
    static bool IsFileOpenByOther(const QString &localFilePath);

    
};

#endif // __FILEHELPER_H__