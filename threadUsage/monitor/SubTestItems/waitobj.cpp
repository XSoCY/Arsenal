#include "waitobj.h"
#include <QDebug>
#include <QThread>

WaitObj::WaitObj(QObject *parent)
    : QObject(parent)
    , m_id(0)
    , m_timer(nullptr)
{
}

int WaitObj::waitOne(quint32 id, int waitTime)
{
    qDebug() << Q_FUNC_INFO << "线程ID【" << QThread::currentThreadId() << "】";
    m_id = id;
    if(m_timer == nullptr)
    {
        m_timer = new QTimer;
        connect(m_timer, &QTimer::timeout, this, &WaitObj::onTimeOut);
        m_timer->setSingleShot(true);
    }
    m_timer->start(waitTime);

    return m_loop.exec();
}

void WaitObj::wakeOne(quint32 id)
{
    qDebug() << Q_FUNC_INFO << "线程ID【" << QThread::currentThreadId() << "】";
    if(id == m_id)
    {
        m_loop.exit(0);
    }
}

void WaitObj::onTimeOut()
{
    m_loop.exit(1);     //超时退出
}
