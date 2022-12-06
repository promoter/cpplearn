#include "fileHelper.h"
#include <QDir>
#include <QFileInfo>

QString FileHelper::CreateDir(const QString &localDirPath)
{
    if (localDirPath.isEmpty())
        return "";

    QDir dir(localDirPath);
    if (dir.exists(localDirPath))
        return localDirPath;

    QString parentDir = CreateDir(localDirPath.mid(0, localDirPath.lastIndexOf('/')));
    QString dirName = localDirPath.mid(localDirPath.lastIndexOf('/') + 1);
    QDir parentPath(parentDir);
    if (!dirName.isEmpty())
        parentPath.mkpath(dirName);
    return QString("%1/%2").arg(parentDir).arg(dirName);
}

bool FileHelper::IsFileOpenByOther(const QString &localFilePath)
{
    QFileInfo fileInfo(localFilePath);
    if (!fileInfo.exists())
        return false;
    //bool isReadable = fileInfo.isReadable();
    //bool isWritable = fileInfo.isWritable();
    QFile file(localFilePath);
    file.open(QIODevice::ReadWrite);
    bool isOpen = file.isOpen();
    if (isOpen)
        file.close();
    return !isOpen;
}
