#ifndef load_font_h_
#define load_font_h_

#include <QFontDatabase>
#include <QFile>
#include <QStringList>
#include <QDebug>
 
 /*************************************Test ******************************************
QString strFont = loadFontFamilyFromFiles(QString("%1/SmileySans-Oblique.ttf").arg(QCoreApplication::applicationDirPath()));
    QFont font(strFont);
    qApp->setFont(font);
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setText("字体测试，1234abcd~!@#$%^&*()_+{}(),.;'");
    textEdit->show();
 *******************************************************************************************/

inline QString loadFontFamilyFromFiles(const QString &strFontFilePath)
{
    QString font = "";
 
    QFile fontFile(strFontFilePath);
    if(!fontFile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Open font file error";
        return font;
    }
 
    int loadedFontID = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
    QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(loadedFontID);
    if(!loadedFontFamilies.empty())
    {
        font = loadedFontFamilies.at(0);
    }
    fontFile.close();
    return font;
}

#endif
