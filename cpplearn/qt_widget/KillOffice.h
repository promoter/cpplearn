#ifndef __KILLOFFICE_H__
#define __KILLOFFICE_H__
#include <Windows.h>

#include <QList>
#include <QString>

class KillOffice
{
public:
    KillOffice();
    ~KillOffice();
private:
    QList<int> getListPidByName(const char *strName);
    DWORD getParentPidByPid(DWORD dwProcessId);

    void killProcess(const QList<int>& lstSubPid, const QList<int>& lstParentPid);
    void appendDisplay(const QString& display, const QList<int>& lstPid);
private:
    QString m_strExplorerPid;
    QString m_strSvchostPid;
};


#endif // __KILLOFFICE_H__