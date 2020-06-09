#include "ScanFetureTest.h"
#include "ui_ScanFetureTest.h"
#include "../monitorui.h"
#include <QMessageBox>

ScanFetureTest::ScanFetureTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanFetureTest)
  , m_isTesting(false)
  , m_monitorUi(monitorUi)
  , m_sendWorker(sendWorker)
  , m_recvWorker(recvWorker)
{
    ui->setupUi(this);
}

ScanFetureTest::~ScanFetureTest()
{
    delete ui;
}

void ScanFetureTest::on_pBtnStart_clicked()
{
    if(m_isTesting){
        QString str("上一次测试还未结束！");
        onErrorMsg(str);
        return;
    }
    qDebug() << Q_FUNC_INFO << m_isTesting;
    m_isTesting = true;
    emit startScanFetureTest(m_packMessage);
}

void ScanFetureTest::on_pBtnStop_clicked()
{
    if(!m_isTesting){
        return;
    }
    m_isTesting = false;
}

void ScanFetureTest::onScanTestResult(double result)
{
    ui->lineEditDopplerRealFreq->setText(QString::number(result));
}

void ScanFetureTest::onErrorMsg(const QString &errMsg)
{
    QMessageBox::warning(this, QStringLiteral("警告"), errMsg, QMessageBox::Cancel);
}

void ScanFetureTest::onTestStatus(bool isTesting)
{
    m_isTesting = isTesting;
}
