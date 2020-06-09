#ifndef RCTIMEDELAYTEST_H
#define RCTIMEDELAYTEST_H

#include <QWidget>
#include <QThread>
#include <QMap>

#include "commonTypes.h"

namespace Ui {
class RCTimeDelayTest;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class RCTimeDelayTest : public QWidget
{
    Q_OBJECT

public:
    explicit RCTimeDelayTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~RCTimeDelayTest();

signals:
    void sigSendCmd(int cmdID, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void sigSetUnitParam(int unitCode, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void startRCTimeDelayTest(const PackMessage&);
    void stopRCTimeDelayTest(const PackMessage&);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();
    void onTestResult(int param, int result);
    void onErrorMsg(const QString &errMsg);
    void onTestStatus(bool isTesting);

private:
    void initUi();

private:
    Ui::RCTimeDelayTest *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // RCTIMEDELAYTEST_H
