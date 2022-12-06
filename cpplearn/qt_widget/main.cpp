#include <QApplication>
#include <QTextCodec>
#include <QWidget>
#include <QTextEdit>
#include <QDebug>
#include "fileHelper.h"
#include "load_font.h"
#include "copyDirFile.h"
#include "KillOffice.h"

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    
    {
        if (FileHelper::IsFileOpenByOther("C:/Users/KLJS381/Desktop/b.docx"))
            KillOffice killword;
    }

    return a.exec();
}
