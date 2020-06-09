#ifndef TIMEMEETACCURACYTEST_H
#define TIMEMEETACCURACYTEST_H

#include <QWidget>
#include <QMap>
#include <QThread>

#include "commonTypes.h"

namespace Ui {
class TimeMeetAccuracyTest;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class TimeMeetAccuracyTest : public QWidget
{
    Q_OBJECT

public:
    explicit TimeMeetAccuracyTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~TimeMeetAccuracyTest();

signals:
    void sigSendCmd(int cmdID, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void sigSetUnitParam(int unitCode, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void startTimeMeetTest(const PackMessage&);
    void stopTimeMeetTest(const PackMessage&);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();
    void onTestResult(quint32 theoreticalSendTime, quint32 realSendTime, int accuracy);
    void onErrorMsg(const QString &errMsg);
    void onTestStatus(bool isTesting);

private:
    void initUi();

private:
    Ui::TimeMeetAccuracyTest *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // TIMEMEETACCURACYTEST_H
