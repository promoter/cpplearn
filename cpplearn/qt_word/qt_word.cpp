#include <QApplication>
#include <QTextCodec>
#include <QWidget>

#include <QDebug>

#include "word_operator.h"

int main(int argc, char *argv[]) 
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));

    QString textRangeText = "###文本1###";
    bool b = (textRangeText.left(3) == "###" && textRangeText.right(3) == "###");

    QWidget *w = new QWidget();
    w->show();

    WordOperator word;
    if (!word.init())
        return 0;
    if (!word.open(QString("%1/word.dot").arg(QCoreApplication::applicationDirPath())) )
        return 0;
    // TODO
    //QAxObject *range = word.getRangeFromTag(QString("文本A"));
    QStringList tags;
    word.getTags(tags);

    qDebug() << tags;

    QAxObject *text1 = word.getRangeFromTag(QString("文本1"));
    word.replaceText(text1, "替换1");

    QAxObject *text2 = word.getRangeFromTag(QString("文本2"));
    word.replaceText(text2, "替换2");
    word.save(QString("%1/save.doc").arg(QCoreApplication::applicationDirPath()));

//TODO: 测试todo功能

    return a.exec();
}
