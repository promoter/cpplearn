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
	//ֱ�Ӵ��ļ������ڸ������ĵ������ĵ�
	bool openFile(const QString& strFile,bool bVisible = false);
	bool save(const QString& strFile);
	void close(void);
	bool getTags(QStringList& tags);//��ȡռλ���ַ����б�

	QAxObject* getRangeFromTag(const QString& tag);


	bool replaceText(QAxObject* range,const QString& text);
	bool replacePicutre(QAxObject* range,const QString& strFile);

    //�������ĵ������ĵ�
    void copySubDocToMainDoc(const QString &strSubDocPath);

private:

	QAxObject * m_word;
	QAxObject * m_documents;
	QAxObject * m_document;
};

#endif // WORDOPERATOR_H
