#include "monitorrecvworker.h"
#include "monitorui.h"
#include "SubTestItems/waitobj.h"

MonitorRecvWorker::MonitorRecvWorker(MonitorUi *monitorUi,
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

void MonitorRecvWorker::onMessageRecved(const UnpackMessage &message)
{
    qDebug() << Q_FUNC_INFO << "线程ID【" << QThread::currentThreadId() << "】";
    m_waitObj->wakeOne(message.operateId);
}
