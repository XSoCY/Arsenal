#ifndef MONITORUI_H
#define MONITORUI_H

#include "commonTypes.h"
#include "monitorsendworker.h"
#include "monitorrecvworker.h"
#include <QWidget>
#include <QTreeWidgetItem>
#include <QThread>
#include <QDebug>

#include "SubTestItems/CaptureTimeTest.h"
#include "SubTestItems/AGCAccuracyTest.h"
#include "SubTestItems/ScanFetureTest.h"
#include "SubTestItems/BandwidthTest.h"
#include "SubTestItems/RCTimeDelayTest.h"
#include "SubTestItems/DemodulTimeDelay.h"
#include "SubTestItems/TimeMeetAccuracyTest.h"

namespace Ui {
class MonitorUi;
}

class WaitObj;
class MonitorUi : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorUi(QWidget *parent = nullptr);
    ~MonitorUi();

signals:
    void sendMessage(const PackMessage &message);
    void onMessageRecved(const UnpackMessage &message);

private slots:
    void onItemChanged(QTreeWidgetItem *item, int column);
    void onErrMsg(const QString &errMsg);

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initThreadWorker();
    void initUI();
    void initConnection();
    void stateExclusion(int type);      //测试项勾选状态互斥
    void updateParentItem(QTreeWidgetItem *item);

private:
    Ui::MonitorUi *ui;
    WaitObj             *m_waitObj;
    MonitorSendWorker   *m_sender;
    MonitorRecvWorker   *m_recver;
    QThread             m_sendThread;
    QThread             m_recvThread;

    quint32 m_sendTimeRC;                   //遥控发令时延测试用到的发令时间
    quint32 m_sendTimeMeet;                 //时间符合精度测试用到的发令时间
    quint8 m_rcDelayRetCnt;                 //遥控发令时延测试结果个数
    quint8 m_demodulRetCnt;                 //遥测解调时延测试结果个数
    QVector<double> m_agcRegisterVal;       //AGC精度测试用到的寄存器值存储容器
    QVector<double> m_agcResultVal;         //AGC精度测试的结果值个数
    QVector<double> m_bandwidthRegVal;      //环路带宽测试用到的寄存器值存储容器
    QVector<double> m_bandwidthResultVal;   //环路带宽测试用到的结果值存储容器

    QList<QTreeWidgetItem*> m_testItems;
    QMap<int, QWidget*> m_resultWidgets;
};

#endif // MONITORUI_H
