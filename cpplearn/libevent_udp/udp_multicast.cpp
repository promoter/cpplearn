#include "udp_multicast.h"

#ifdef WIN32
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#endif

#include "event2/event.h"
#include "event2/event_compat.h"

#include <QDebug>

const char* localIp = "172.20.4.122";
const char* sendData = "122235232352351发生的鬼魂附体太热特而特温柔特务太温柔teertwertewrtwr@#$%^&*(122235232352351发生的鬼魂附体太热特而特温柔特务太温柔teertwertewrtwr@#$%^&*(122235232352351发生的鬼魂附体太热特而特温柔特务太温柔teertwertewrtwr@#$%^&*(122235232352351发生的鬼魂附体太热特而特温柔特务太温柔teertwertewrtwr@#$%^&*(122235232352351发生的鬼魂附体太热特而特温柔特务太温柔teertwertewrtwr@#$%^&*(";

void eventCallBack(int fd, short ev, void *arg)
{
    UdpMulticast *udp = (UdpMulticast*)arg;
    if (ev & EV_READ)
    {
        struct sockaddr_in addrClient;
        socklen_t len = sizeof(sockaddr_in);
        memset(udp->_recvBuff, 0, sizeof(udp->_recvBuff));
        int iRecv = recvfrom(fd, udp->_recvBuff, sizeof(udp->_recvBuff), 0,  (struct sockaddr*)&addrClient, &len);
        //qDebug() << "iRecv " << iRecv;
    }
    else if (ev & EV_WRITE)
    {
        //模拟发送
        struct sockaddr_in sendAddr;
        sendAddr.sin_family = AF_INET;
        sendAddr.sin_addr.s_addr = inet_addr(localIp);
        sendAddr.sin_port = htons(UDP_MULTICAST_PORT);
        //memset(udp->_sendBuff, 0, sizeof(udp->_sendBuff));
        //memcpy(udp->_sendBuff, sendData, strlen(sendData));
        //int sendLen = strlen(udp->_sendBuff);
        int iSend = sendto(fd,  udp->_sendBuff, strlen(udp->_sendBuff), 0, (struct sockaddr*)&sendAddr, sizeof(sendAddr));
        //qDebug() << "isend " << iSend;
    }
}

#define CHECK_ERROR_NOT_0(str, i) \
    if ((i) != 0) { qDebug() << (#str) << " error:" << (i);  return;    }

UdpMulticast::UdpMulticast()
    : QThread()
    , _evBase(NULL)
    , _ev(NULL)
    , _bRun(false)
{

    WORD wVsersion = MAKEWORD(2, 2);
    WSADATA wsa_data;
    WSAStartup(wVsersion, &wsa_data);

    _serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    Q_ASSERT(_serverSocket != -1);

    int optval = 1;
    int er = setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)(&optval), sizeof(optval));
    CHECK_ERROR_NOT_0("set SO_REUSEADDR", er);

    er = evutil_make_socket_nonblocking(_serverSocket);
    CHECK_ERROR_NOT_0("evutil_make_socket_nonblocking", er);

#if 0 //  加上buffsize = 1024 * 1024 * 12;这个吞吐量会有轻微下降， 800Mbps降到700Mbps;
    unsigned int buffsize = 1024 * 1024 * 12;
    er = setsockopt(_serverSocket, SOL_SOCKET, SO_RCVBUF, (const char*)(&buffsize), sizeof(buffsize));
    CHECK_ERROR_NOT_0("set SO_RCVBUF", er);

    er = setsockopt(_serverSocket, SOL_SOCKET, SO_SNDBUF, (const char*)(&buffsize), sizeof(buffsize));
    CHECK_ERROR_NOT_0("set SO_SNDBUF", er);
#endif

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(UDP_MULTICAST_PORT);
    er = bind(_serverSocket, (const struct sockaddr*)&addr, sizeof(addr));
    CHECK_ERROR_NOT_0("bind", er);

    ip_mreq multiCast;
	multiCast.imr_interface.S_un.S_addr = inet_addr(localIp);
	multiCast.imr_multiaddr.S_un.S_addr = inet_addr(UDP_MULTICAST_ADDR);
	er = setsockopt(_serverSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&multiCast, sizeof(multiCast));
    CHECK_ERROR_NOT_0("IP_ADD_MEMBERSHIP", er);

    struct in_addr sendAddr;
    sendAddr.s_addr = inet_addr(localIp);
	er = setsockopt(_serverSocket, IPPROTO_IP, IP_MULTICAST_IF, (char*)&sendAddr, sizeof(sendAddr));
    CHECK_ERROR_NOT_0("IP_MULTICAST_IF", er);

    qDebug() << "use libEvent:" << event_get_version();
    _evBase = event_base_new();
    Q_ASSERT(_evBase);

    memset(_sendBuff, 33, 1300);
}

UdpMulticast::~UdpMulticast()
{
    _bRun = false;
    if (!this->wait(1000))
        this->terminate();

    WSACleanup();
}

void UdpMulticast::StartEventThread(void *arg)
{
    UdpMulticast *pThis = (UdpMulticast *)arg;
    Q_ASSERT(pThis);

    pThis->_ev = event_new(pThis->_evBase, pThis->_serverSocket, EV_READ | EV_WRITE | EV_PERSIST, 
                        eventCallBack, pThis);
    Q_ASSERT(pThis->_ev);      
    event_add(pThis->_ev, NULL);
    event_base_dispatch(pThis->_evBase);             
}


void UdpMulticast::Start()
{
    if (_bRun)
        return;
    _bRun = true;
    this->start();
}

void UdpMulticast::run()
{
    qDebug() << "-------------UdpMulticast::run--------start-----------";
    while (_bRun)
    {
        /* code */

        //模拟处理消息

        QThread::msleep(1);
    }
    
    qDebug() << "-------------UdpMulticast::run-------finisehd------------";
}

