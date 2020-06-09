#ifndef BANDWIDTHTEST_H
#define BANDWIDTHTEST_H

#include <QWidget>
#include <QMap>
#include <QThread>

#include "commonTypes.h"

namespace Ui {
class BandwidthTest;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class BandwidthTest : public QWidget
{
    Q_OBJECT

public:
    explicit BandwidthTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~BandwidthTest();
signals:
    void sigSendCmd(int cmdID, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void sigSetUnitParam(int unitCode, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void startBandwidthTest(const PackMessage&);
    void stopBandwidthTest(const PackMessage&);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();
    void onBandwidthTestResult(int param, double result);
    void onErrorMsg(const QString &errMsg);
    void onTestStatus(bool isTesting);

private:
    void initUi();

private:
    Ui::BandwidthTest *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // BANDWIDTHTEST_H
