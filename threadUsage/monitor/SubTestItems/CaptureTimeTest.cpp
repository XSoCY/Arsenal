#include "CaptureTimeTest.h"
#include "ui_CaptureTimeTest.h"
#include "../monitorui.h"

CaptureTimeTest::CaptureTimeTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CaptureTimeTest)
    , m_isTesting(false)
    , m_monitorUi(monitorUi)
    , m_sendWorker(sendWorker)
    , m_recvWorker(recvWorker)
{
    ui->setupUi(this);
    initUI();
}

CaptureTimeTest::~CaptureTimeTest()
{
    delete ui;
}

void CaptureTimeTest::setItemVisible(int subItem, bool isView)
{
    switch (subItem) {
    case CAEEIER_DOUBLE:
        ui->groupBoxCarrier->setVisible(isView);
        break;
    case DISTANCE_CAPTURE:
        ui->groupBoxDistance->setVisible(isView);
        break;
    case SYSTEM_CAPTURE:
        ui->groupBoxSystem->setVisible(isView);
        break;
    case ALL_ITEMS:
        ui->groupBoxCarrier->setVisible(isView);
        ui->groupBoxDistance->setVisible(isView);
//        ui->groupBoxSystem->setVisible(isView);
        break;
    default:
        break;
    }
}

void CaptureTimeTest::on_pBtnStart_clicked()
{
    // 从界面获取参数
}

void CaptureTimeTest::on_pBtnStop_clicked()
{
    // 从界面获取参数
}

void CaptureTimeTest::initUI()
{
    // 隐藏右侧结果展示框
    ui->groupBoxCarrier->hide();
    ui->groupBoxDistance->hide();
    ui->groupBoxSystem->hide();

    ui->timeEditDistanceIntervalTime->setReadOnly(true);
    ui->timeEditDistanceStartTime->setReadOnly(true);
    ui->timeEditDistanceStopTime->setReadOnly(true);
    ui->timeEditCarrierIntervalTime->setReadOnly(true);
    ui->timeEditCarrierStartTime->setReadOnly(true);
    ui->timeEditCarrierStopTime->setReadOnly(true);
    ui->timeEditSystemIntervalTime->setReadOnly(true);
    ui->timeEditSystemStartTime->setReadOnly(true);
    ui->timeEditSystemStopTime->setReadOnly(true);
}
