#ifndef DEMODULTIMEDELAY_H
#define DEMODULTIMEDELAY_H

#include <QWidget>
#include <QMap>
#include <QThread>

#include "commonTypes.h"

namespace Ui {
class DemodulTimeDelay;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class DemodulTimeDelay : public QWidget
{
    Q_OBJECT

public:
    explicit DemodulTimeDelay(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~DemodulTimeDelay();

signals:
    void sigSendCmd(int cmdID, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void sigSetUnitParam(int unitCode, const QMap<QString, QVariant> &dataMap, bool isTestMode, int cmdNum);
    void startDemodulTimeDelayTest(const PackMessage&);
    void stopDemodulTimeDelayTest(const PackMessage&);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();
    void onTestResult(int param, int result);
    void onErrorMsg(const QString &errMsg);
    void onTestStatus(bool isTesting);

private:
    void initUi();

private:
    Ui::DemodulTimeDelay *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // DEMODULTIMEDELAY_H
