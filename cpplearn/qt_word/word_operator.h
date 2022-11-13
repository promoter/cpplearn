#ifndef WORDOPERATOR_H
#define WORDOPERATOR_H

#include <QObject>
#include <QAxObject>
#include <QAxWidget>
#include <QDebug>


class WordOperator : public QObject
{
	Q_OBJECT

public:
	WordOperator(QObject *parent = nullptr);
	~WordOperator();

	bool init(void);
	bool open(const QString& strFile,bool bVisible = false);
	//直接打开文件，用于复制子文档到主文档
	bool openFile(const QString& strFile,bool bVisible = false);
	bool save(const QString& strFile);
	void close(void);
	bool getTags(QStringList& tags);//获取占位符字符串列表

	QAxObject* getRangeFromTag(const QString& tag);


	bool replaceText(QAxObject* range,const QString& text);
	bool replacePicutre(QAxObject* range,const QString& strFile);

    //复制子文档到主文档
    void copySubDocToMainDoc(const QString &strSubDocPath);

private:

	QAxObject * m_word;
	QAxObject * m_documents;
	QAxObject * m_document;
};

#endif // WORDOPERATOR_H
