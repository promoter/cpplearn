#include "word_operator.h"
#include <Windows.h>

WordOperator::WordOperator(QObject *parent)
	: QObject(parent)
	, m_word(nullptr)
	, m_documents(nullptr)
	, m_document(nullptr)
{
	OleInitialize(nullptr);
}

WordOperator::~WordOperator()
{
	close();
	OleUninitialize();
}

bool WordOperator::init(void)
{
	m_word = new QAxObject("Word.Application");
	if (!m_word)
		return false;

	m_word->setProperty("Visible", false);

	m_documents = m_word->querySubObject("Documents");
	if (!m_documents)
		return false;

	return true;
}

bool WordOperator::open(const QString& strFile,bool bVisible /*= false*/)
{
	if (!m_word || !m_documents)
		return false;

	m_documents->dynamicCall("Add(QString)",strFile);

	m_document = m_word->querySubObject("ActiveDocument");
	if (!m_document)
		return false;

	return true;
}

bool WordOperator::openFile(const QString& strFile,bool bVisible /*= false*/)
{
	if (!m_word || !m_documents)
		return false;

	m_documents->dynamicCall("open(QString)",strFile);

	m_document = m_word->querySubObject("ActiveDocument");
	if (!m_document)
		return false;

	return true;
}

bool WordOperator::save(const QString& strFile)
{
	if (!m_document)
		return false;
	m_document->dynamicCall("SaveAs2(const QString&)", strFile);

	return true;
}

void WordOperator::close(void)
{
	if (m_document)
	{
		m_document->dynamicCall("Close(bool)", false);
		//delete m_document;
		m_document = 0;
	}
	if (m_word)
	{
		m_word->setProperty("DispalyAlerts", true);
		QAxObject* axobjNormalTemplate = m_word->querySubObject("NormalTemplate");
		if(axobjNormalTemplate != nullptr)
		{
		axobjNormalTemplate->setProperty("Saved", true);
		}
		m_word->dynamicCall("Quit()");
		delete m_word;
		m_word= nullptr;
	}
}


bool WordOperator::getTags(QStringList& tags)
{
	QAxObject* content = m_document->querySubObject("Content");
	if (!content)
		return false;

	QString strContent = content->property("Text").toString();

	QRegExp exp("(#{3})([A-Za-z0-9.\u4e00-\u9fa5_]+)(#{3})");

	int count = 0;
	int pos = 0;
	while ((pos = exp.indexIn(strContent, pos)) != -1) 
	{
		count++;
		pos += exp.matchedLength();
		tags.append(exp.cap(2));
	}

	QAxObject *shapes = m_document->querySubObject("Shapes");
	if (shapes)
	{
		int shapeCount = shapes->property("Count").toUInt();
		for (int i = 1; i <= shapeCount; ++i)
		{
			QAxObject *shape = shapes->querySubObject("Item(int)", i);
			if (shape)
			{
				QAxObject *textFrame = shape->querySubObject("TextFrame");
				if (textFrame)
				{
					QAxObject *textRange = textFrame->querySubObject("TextRange");
					if (textRange)
					{
						QString textRangeText = textRange->property("Text").toString().trimmed();
						// qDebug() << textRangeText;
						if (textRangeText.length() > 6)
						{
							if (textRangeText.left(3) == "###" && textRangeText.right(3) == "###")
								tags.append(textRangeText.mid(3, textRangeText.length() - 6));
						}
					}	
				}
			}
		}
	}

	return true;
}

QAxObject* WordOperator::getRangeFromTag(const QString& tag)
{
	if(!m_document)
		return nullptr;

	QAxObject * range = m_document->querySubObject("Content");
	if (!range)
		return nullptr;
	QAxObject * find = range->querySubObject("Find");

	QString str = QString("###%1###").arg(tag);

	QVariant var = find->dynamicCall("Execute(QString)", str);
	if (!var.toBool())
	{
		// 查找 Shapes
		QAxObject *shapes = m_document->querySubObject("Shapes");
		if (shapes)
		{
			int shapeCount = shapes->property("Count").toUInt();
			for (int i = 1; i <= shapeCount; ++i)
			{
				QAxObject *shape = shapes->querySubObject("Item(int)", i);
				if (shape)
				{
					QAxObject *textFrame = shape->querySubObject("TextFrame");
					if (textFrame)
					{
						QAxObject *textRange = textFrame->querySubObject("TextRange");
						if (textRange)
						{
							QString textRangeText = textRange->property("Text").toString().trimmed();
							if (textRangeText == str)
							{
								return textRange;
							}
						}	
					}
				}
			}
		}


		return nullptr;
	}

	return range;
}

bool WordOperator::replaceText(QAxObject* range,const QString& text)
{
	return range->setProperty("Text", text);
}

bool WordOperator::replacePicutre(QAxObject* range,const QString& strFile)
{
	if(!range->setProperty("Text", ""))
		return false;
	QVariant var = range->dynamicCall("End()");
	QAxObject* shapes = range->querySubObject("InlineShapes");
	if (!shapes)
		return false;

	var = shapes->dynamicCall("AddPicture(QString)", strFile);
	if(!var.toBool())
		return false;

	return true;
}

void WordOperator::copySubDocToMainDoc( const QString &strSubDocPath )
{
    m_documents->dynamicCall("Add(QString)", strSubDocPath);
    QAxObject *pDocument = m_word->querySubObject("ActiveDocument");
    QAxObject *pRange = pDocument->querySubObject("Range()");
    pRange->dynamicCall("Copy()");

    QAxObject *paragraphsA = m_document->querySubObject("Paragraphs");
    int nParaCount = paragraphsA->property("Count").toInt();
    QAxObject *paragraphA = paragraphsA->querySubObject("Item(int)", nParaCount);
    QAxObject *documentRangeA = paragraphA->querySubObject("Range()");
    documentRangeA->dynamicCall("Paste()");
    m_document->dynamicCall("Save()");
}
