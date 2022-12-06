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

    QString textRangeText = "###�ı�1###";
    bool b = (textRangeText.left(3) == "###" && textRangeText.right(3) == "###");

    QWidget *w = new QWidget();
    w->show();

    WordOperator word;
    if (!word.init())
        return 0;
    if (!word.open(QString("%1/word.dot").arg(QCoreApplication::applicationDirPath())) )
        return 0;
    // TODO
    //QAxObject *range = word.getRangeFromTag(QString("�ı�A"));
    QStringList tags;
    word.getTags(tags);

    qDebug() << tags;

    QAxObject *text1 = word.getRangeFromTag(QString("�ı�1"));
    word.replaceText(text1, "�滻1");

    QAxObject *text2 = word.getRangeFromTag(QString("�ı�2"));
    word.replaceText(text2, "�滻2");
    word.save(QString("%1/save.doc").arg(QCoreApplication::applicationDirPath()));

//TODO: ����todo����

    return a.exec();
}
