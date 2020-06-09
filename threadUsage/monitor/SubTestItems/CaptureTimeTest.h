#ifndef CAPTURETIMETEST_H
#define CAPTURETIMETEST_H

#define CAEEIER_DOUBLE      1   //载波双捕
#define DISTANCE_CAPTURE    2   //距离捕获
#define SYSTEM_CAPTURE      3   //系统捕获
#define ALL_ITEMS           4   //全部

#define CAPTURE_CTRL_CMDID  7   // 捕获控制命令ID
#define MACPU_UNIT_ID       2   // 公共单元ID
#define MODULATOR_UNIT_ID   5   // 调制器单元ID
#define RANGE_UNIT_ID       6   // 测距单元ID

#include <QWidget>
#include <QMap>
#include <QThread>

#include "commonTypes.h"

namespace Ui {
class CaptureTimeTest;
}

class MonitorUi;
class MonitorSendWorker;
class MonitorRecvWorker;
class CaptureTimeTest : public QWidget
{
    Q_OBJECT

public:
    explicit CaptureTimeTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent = 0);
    ~CaptureTimeTest();

    void setItemVisible(int subItem, bool isView);

signals:
    void sendCmd(int cmdID, const QMap<QString, QVariant> &dataMap);

private slots:
    void on_pBtnStart_clicked();
    void on_pBtnStop_clicked();

private:
    void initUI();

private:
    Ui::CaptureTimeTest *ui;
    bool m_isTesting;
    MonitorUi *m_monitorUi;
    MonitorSendWorker *m_sendWorker;
    MonitorRecvWorker *m_recvWorker;
    QThread m_sendThread;
    PackMessage m_packMessage;
};

#endif // CAPTURETIMETEST_H
