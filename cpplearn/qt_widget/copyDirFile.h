#ifndef copyDirFile_h_
#define copyDirFile_h_

#include <QString>

 /*************************************Test ******************************************
{
        CopyDirFile copydirFile(QString("F:/vs_workspace/ICD/20221128/QuikICD"), 
                                QString ("*.vcxproj"), 
                                QString ("C:/Users/KLJS381/Desktop/QuikICD"));
}
 *******************************************************************************************/

class CopyDirFile
{
public:
    CopyDirFile(const QString &srcDirPath, const QString &fileFilter, const QString &destDirPath);
    ~CopyDirFile();
private:
    void copyFile(const QString &srcDirPath, const QString &fileFilter, const QString &destDirPath);
    
};


#endif

