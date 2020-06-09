#ifndef SCANFETURETEST_H
#define SCANFETURETEST_H

#include <QWidget>
#include <QMap>
#include <QThread>

#include "commonTypes.h"

namespace Ui {
class ScanFetureTest;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class ScanFetureTest : public QWidget
{
    Q_OBJECT

public:
    explicit ScanFetureTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~ScanFetureTest();

signals:
    void sigSendCmd(int cmdID, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void sigSetUnitParam(int unitCode, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void startScanFetureTest(const PackMessage&);
    void stopScanFetureTest(const PackMessage&);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();
    void onScanTestResult(double result);
    void onErrorMsg(const QString &errMsg);
    void onTestStatus(bool isTesting);

private:
    Ui::ScanFetureTest *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // SCANFETURETEST_H
