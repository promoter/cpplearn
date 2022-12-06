#include "KillOffice.h"

#include <QDebug>
#include <QApplication>

#include"tlhelp32.h"

//这个是软件内部创建Office进程时的父
#define SVCHOST_EXE "svchost.exe"

//这个是外部创建Office进程时的父
#define EXPLORER_EXE "explorer.exe"

#define WORD_EXE            "WINWORD.EXE"
#define EXCEL_EXE           "EXCEL.EXE"
#define POWERPOINT_EXE      "POWERPNT.EXE"

#define ProcessBasicInformation 0

typedef struct
{
    DWORD ExitStatus;
    DWORD PebBaseAddress;
    DWORD AffinityMask;
    DWORD BasePriority;
    ULONG UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
}   PROCESS_BASIC_INFORMATION;

typedef LONG (WINAPI *PROCNTQSIP)(HANDLE,UINT,PVOID,ULONG,PULONG);


KillOffice::KillOffice()
{    
    QList<int> lstSvchostPid = getListPidByName(SVCHOST_EXE);
    QList<int> lstExplorer = getListPidByName(EXPLORER_EXE);  //这个可以不用

    appendDisplay(QString("svchost:"), lstSvchostPid);
    appendDisplay(QString("explorer:"), lstExplorer);

    QList<int> lstWordPid = getListPidByName(WORD_EXE);
    appendDisplay(QString("word:"), lstWordPid);
    killProcess(lstWordPid, lstExplorer);

#if 0
    QList<int> lstExcelPid = getListPidByName(EXCEL_EXE);
    appendDisplay(QString("excel:"), lstExcelPid);
    killProcess(lstExcelPid, lstSvchostPid);

    QList<int> lstPowerPointPid = getListPidByName(POWERPOINT_EXE);
    appendDisplay(QString("ppt:"), lstPowerPointPid);
    killProcess(lstPowerPointPid, lstSvchostPid);
#endif
}

KillOffice::~KillOffice()
{

}

//根据进程名获取pid
QList<int> KillOffice::getListPidByName(const char *strName)
{
    QList<int> lstPid;
    HANDLE hProcess;
    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);
    BOOL bRet;
    //进行进程快照
    hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //TH32CS_SNAPPROCESS快照所有进程
    //开始进程查找
    bRet = Process32First(hProcess, &processEntry);
    //循环比较，得出ProcessID
    while(bRet)
    {
        QString temp = QString::fromLocal8Bit(processEntry.szExeFile);
        if(strcmp(strName, temp.toLocal8Bit()) == 0)
        {
            lstPid.append(processEntry.th32ProcessID);
        }
        bRet = Process32Next(hProcess, &processEntry);
    }
    return lstPid;
}

//根据进程的Pid获取父Pid
DWORD KillOffice::getParentPidByPid(DWORD dwProcessId)
{
    LONG                        status = -1;
    DWORD                       dwParentPid = (DWORD)-1;
    HANDLE                      hProcess = NULL;
    PROCESS_BASIC_INFORMATION   processBasicInformation;

    PROCNTQSIP NtQueryInformationProcess = (PROCNTQSIP) GetProcAddress(
                GetModuleHandle("ntdll"), "NtQueryInformationProcess");

    if (NULL == NtQueryInformationProcess)
    {
        return (DWORD)-1;
    }
    // Get process handle
    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
    if (!hProcess)
    {
        return (DWORD)-1;
    }

    // Retrieve information
    status = NtQueryInformationProcess(hProcess,
                                       ProcessBasicInformation,
                                       (PVOID)&processBasicInformation,
                                       sizeof(PROCESS_BASIC_INFORMATION),
                                       NULL
                                       );

    //注意：这里要用32位的编译器，64位的编译器得到的不是0而是 -1073741820
    if (!status)
    {
        dwParentPid = processBasicInformation.InheritedFromUniqueProcessId;
    }

    CloseHandle(hProcess);

    return dwParentPid;
}

//杀死进程
void KillOffice::killProcess(const QList<int> &lstSubPid, const QList<int> &lstParentPid)
{
    int nParentPid = -1;
    //遍历子进程
    for (int i = 0; i < lstSubPid.count(); ++i)
    {
        //获取子进程的父进程
        nParentPid = getParentPidByPid(lstSubPid.at(i));
        //如果这个进程是由某个父进程创建的，则杀死
        if (lstParentPid.contains(nParentPid))
        {
            HANDLE hProcess = NULL;
            //打开目标进程
            hProcess = OpenProcess(PROCESS_TERMINATE,FALSE, lstSubPid.at(i));
            if (hProcess == NULL)
            {
                qDebug()<<"Open Process fAiled ,error:"<<GetLastError();
            }
            //结束目标进程
            DWORD ret = TerminateProcess(hProcess,0);
            if(ret == 0)
            {
                qDebug()<<"kill task faild,error:"<<GetLastError();
            }
            else
            {
                qDebug()<<"kill task success ------------------------------------------------";
            }
        }
    }
}

void KillOffice::appendDisplay(const QString &display, const QList<int> &lstPid)
{
    qDebug() << "-----------display-----------:" <<  display;
    for (int i = 0; i < lstPid.size(); ++i)
    {      
        qDebug() << QString("%1 ").arg(lstPid.at(i));
    }
}
