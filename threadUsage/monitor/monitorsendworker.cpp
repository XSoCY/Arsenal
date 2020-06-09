#include "monitorsendworker.h"
#include "monitorui.h"
#include "SubTestItems/waitobj.h"

MonitorSendWorker::MonitorSendWorker(MonitorUi *monitorUi,
                                     quint32 &sendTimeRC, quint32 &sendTimeMeet,
                                     quint8 &rcDelayRetCnt, quint8 &demodulRetCnt,
                                     QVector<double> &agcRegisterVal, QVector<double> &agcResultVal,
                                     QVector<double> &bandwidthRegVal, QVector<double> &bandwidthResultVal,
                                     WaitObj *waitObj, QObject *parent)
    : QObject(parent), m_monitorUi(monitorUi)
    , m_sendTimeRC(sendTimeRC), m_sendTimeMeet(sendTimeMeet)
    , m_rcDelayRetCnt(rcDelayRetCnt), m_demodulRetCnt(demodulRetCnt)
    , m_agcRegisterVal(agcRegisterVal), m_agcResultVal(agcResultVal)
    , m_bandwidthRegVal(bandwidthRegVal), m_bandwidthResultVal(bandwidthResultVal)
    , m_waitObj(waitObj)
{
}

MonitorSendWorker::~MonitorSendWorker()
{
}

bool MonitorSendWorker::onStartAGCTest(PackMessage &packeMsg)
{
    qDebug() << Q_FUNC_INFO << "线程ID【" << QThread::currentThreadId() << "】";
    const quint32 step = 100;
    for(quint32 i=0; i < packeMsg.steps; i++)
    {
        packeMsg.operateId = step + i;
        emit sendMessage(packeMsg);
        if(m_waitObj->waitOne(step+i)) {
            QString str = QString("AGCTest步骤%1操作失败！").arg(step+i);
            emit errMsg(str);
            return false;
        }
        qDebug() << Q_FUNC_INFO << "线程ID【" << QThread::currentThreadId() << "】";
    }

    return true;
}
