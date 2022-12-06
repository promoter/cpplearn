#include "copyDirFile.h"
#include <QDir>
#include <QFileInfo>
#include <QFile>

#include "fileHelper.h"

CopyDirFile::CopyDirFile(const QString &srcDirPath, const QString &fileFilter, const QString &destDirPath)
{
    copyFile(srcDirPath, fileFilter, destDirPath);
}

CopyDirFile::~CopyDirFile()
{
}

void CopyDirFile::copyFile(const QString &srcDirPath, const QString &fileFilter, const QString &destDirPath)
{
    QDir srcDir(srcDirPath);
    if (!srcDir.exists())
        return;

    QDir destDir(destDirPath);
    FileHelper::CreateDir(destDirPath);

    QRegExp regExp(fileFilter, Qt::CaseInsensitive, QRegExp::Wildcard);   

    QFileInfoList srcFileList = srcDir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::DirsFirst);
    foreach (const QFileInfo &fileInfo, srcFileList)
    {
        if (fileInfo.isDir())
            copyFile(fileInfo.absoluteFilePath(), fileFilter, QString("%1/%2").arg(destDirPath).arg(fileInfo.fileName()));

        if (regExp.exactMatch(fileInfo.fileName())) 
        {
            QFile::copy(fileInfo.absoluteFilePath(), QString("%1/%2").arg(destDirPath).arg(fileInfo.fileName()));
        }

    }

}