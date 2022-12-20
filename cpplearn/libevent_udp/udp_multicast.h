#ifndef __UDP_MULTICAST_H__
#define __UDP_MULTICAST_H__

#include <QThread>

#define UDP_MULTICAST_ADDR "224.0.0.50"
#define UDP_MULTICAST_PORT 15100

struct event_base;
struct event;

class UdpMulticast : public QThread
{
    friend void eventCallBack(int fd, short ev, void *arg);
public:
    UdpMulticast();
    virtual ~UdpMulticast();

    void Start();

    static void StartEventThread(void *arg);

protected:
    void run();


private:
    struct event_base *_evBase;
    struct event *_ev;

    int _serverSocket;
    char _recvBuff[20480];

    //测试
    char _sendBuff[1300]; //能稳定到 800Mbps; 单机收发。 加一个 qDebug日志，性能下降到300Mbps;

    volatile bool _bRun;
};


#endif // __UDP_MULTICAST_H__