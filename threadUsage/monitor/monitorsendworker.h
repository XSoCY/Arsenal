#ifndef MONITORSENDWORKER_H
#define MONITORSENDWORKER_H

#include <QObject>
#include "commonTypes.h"

class MonitorUi;
class WaitObj;
class MonitorSendWorker : public QObject
{
    Q_OBJECT
public:
    explicit MonitorSendWorker(MonitorUi *monitorUi,
                               quint32& sendTimeRC, quint32& sendTimeMeet,
                               quint8& rcDelayRetCnt, quint8& demodulRetCnt,
                               QVector<double>& agcRegisterVal, QVector<double>& agcResultVal,
                               QVector<double>& bandwidthRegVal, QVector<double>& bandwidthResultVal,
                               WaitObj *waitObj, QObject *parent = nullptr);
    ~MonitorSendWorker();

signals:
    void errMsg(const QString &errMsg);
    void sendMessage(const PackMessage &message);

public slots:
    bool onStartAGCTest(PackMessage &packeMsg);

private:
    MonitorUi           *m_monitorUi;
    quint32&            m_sendTimeRC;           //遥控发令时延测试用到的发令时间
    quint32&            m_sendTimeMeet;         //时间符合精度测试用到的发令时间
    quint8&             m_rcDelayRetCnt;        //遥控发令时延测试结果个数
    quint8&             m_demodulRetCnt;        //遥测解调时延测试结果个数
    QVector<double>&    m_agcRegisterVal;       //AGC精度测试用到的寄存器值存储容器
    QVector<double>&    m_agcResultVal;         //AGC精度测试的结果值个数
    QVector<double>&    m_bandwidthRegVal;      //环路带宽测试用到的寄存器值存储容器
    QVector<double>&    m_bandwidthResultVal;   //环路带宽测试用到的结果值存储容器
    WaitObj             *m_waitObj;
};

#endif // MONITORSENDWORKER_H
