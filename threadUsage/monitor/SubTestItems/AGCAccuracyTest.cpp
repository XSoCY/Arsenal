#include "AGCAccuracyTest.h"
#include <QMessageBox>
#include "../monitorui.h"
#include "ui_AGCAccuracyTest.h"

AGCAccuracyTest::AGCAccuracyTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AGCAccuracyTest)
    , m_isTesting(false)
    , m_monitorUi(monitorUi)
    , m_sendWorker(sendWorker)
    , m_recvWorker(recvWorker)
{
    ui->setupUi(this);
    initUi();
    initConnect();
}

AGCAccuracyTest::~AGCAccuracyTest()
{
    delete ui;
}

void AGCAccuracyTest::on_pBtnStart_clicked()
{
    if(m_isTesting){
        QString str("上一次测试还未结束！");
        onErrorMsg(str);
        return;
    }
    m_isTesting = true;
    //
    m_packMessage.steps = 3;
    emit startAGCTest(m_packMessage);
}

void AGCAccuracyTest::on_pBtnStop_clicked()
{
    if(!m_isTesting){
        return;
    }
    m_isTesting = false;
}

void AGCAccuracyTest::onTestResult(const UnpackMessage &message)
{
    QString strDesc = QString("AGC控制范围和控制精度测试:%1dbm").arg(message.agcRegisterVal.first());
    QString strResult = QString("%1dbm").arg(message.agcResultVal.first());
    QTableWidgetItem *descItem = new QTableWidgetItem(strDesc);
    QTableWidgetItem *resultItem = new QTableWidgetItem(strResult);
    int rowCnt = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCnt);
    ui->tableWidget->setItem(rowCnt, 0, descItem);
    ui->tableWidget->setItem(rowCnt, 1, resultItem);
}

void AGCAccuracyTest::onErrorMsg(const QString &errMsg)
{
    QMessageBox::warning(this, QStringLiteral("警告"), errMsg, QMessageBox::Cancel);
}

void AGCAccuracyTest::onTestStatus(bool isTesting)
{
    m_isTesting = isTesting;
}

void AGCAccuracyTest::initUi()
{
    QTableWidget* tablewidget = ui->tableWidget;
    QStringList strHeadList;
    strHeadList << QStringLiteral("字段名称") << QStringLiteral("值");
    tablewidget->setColumnCount(2);  // 设置表格的列数
    tablewidget->setColumnWidth(0, 247);
    tablewidget->setColumnWidth(1, 100);
    tablewidget->setHorizontalHeaderLabels(strHeadList);

    tablewidget->verticalHeader()->setVisible(false);
    tablewidget->horizontalHeader()->setSectionsMovable(false);
    tablewidget->horizontalHeader()->setSectionsClickable(false);
    tablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablewidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    tablewidget->setAlternatingRowColors(true);
    tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //禁止编辑表格
}

bool AGCAccuracyTest::initConnect()
{
    if(connect(this, &AGCAccuracyTest::startAGCTest, m_sendWorker, &MonitorSendWorker::onStartAGCTest)
            && connect(m_recvWorker, &MonitorRecvWorker::onMessageRecved, this, &AGCAccuracyTest::onTestResult)
            && connect(m_sendWorker, &MonitorSendWorker::errMsg, this, &AGCAccuracyTest::onErrorMsg)
            && connect(m_recvWorker, &MonitorRecvWorker::errMsg, this, &AGCAccuracyTest::onErrorMsg))
    {
        qDebug() << Q_FUNC_INFO << "Connect success.";
        return true;
    }
    else
    {
        qDebug() << Q_FUNC_INFO << "Connect failed!";
        return false;
    }
}
