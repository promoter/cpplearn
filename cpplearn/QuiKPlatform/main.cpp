#include <QApplication>
#include <QTextCodec>
#include <QWidget>
#include <QTextEdit>
#include <QDebug>

#include "CoreManTarget.h"

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    
    QCoreApplication::setOrganizationName("Keliang");
    QCoreApplication::setApplicationName("QuiKICD_Target");

    CoreManTarget coremanTarget;
    coremanTarget.Init();

    return a.exec();
}
