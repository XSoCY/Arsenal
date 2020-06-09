#ifndef AGCACCURACYTEST_H
#define AGCACCURACYTEST_H

#include <QWidget>
#include <QMap>
#include <QThread>

#include "commonTypes.h"

namespace Ui {
class AGCAccuracyTest;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class AGCAccuracyTest : public QWidget
{
    Q_OBJECT

public:
    explicit AGCAccuracyTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~AGCAccuracyTest();

signals:
    bool startAGCTest(PackMessage&);
    void stopAGCTest(PackMessage&);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();
    void onTestResult(const UnpackMessage &message);
    void onErrorMsg(const QString &errMsg);
    void onTestStatus(bool isTesting);

private:
    void initUi();
    bool initConnect();

private:
    Ui::AGCAccuracyTest *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // AGCACCURACYTEST_H
