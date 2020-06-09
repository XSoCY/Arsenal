#include "BandwidthTest.h"
#include "ui_BandwidthTest.h"
#include "../monitorui.h"
#include <QMessageBox>

BandwidthTest::BandwidthTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BandwidthTest)
  , m_isTesting(false)
  , m_monitorUi(monitorUi)
  , m_sendWorker(sendWorker)
  , m_recvWorker(recvWorker)
{
    ui->setupUi(this);
    initUi();
}

BandwidthTest::~BandwidthTest()
{
    delete ui;
}

void BandwidthTest::on_pBtnStart_clicked()
{
    if(m_isTesting){
        QString str("上一次测试还未结束！");
        onErrorMsg(str);
        return;
    }
    m_isTesting = true;
    emit startBandwidthTest(m_packMessage);
}

void BandwidthTest::on_pBtnStop_clicked()
{
    if(!m_isTesting){
        return;
    }
    m_isTesting = false;
}

void BandwidthTest::onBandwidthTestResult(int param, double result)
{
    QString strDesc = QString("载波环路带宽%1Hz").arg(param);
    QString strResult = QString("%1Hz").arg(result);
    QTableWidgetItem *descItem = new QTableWidgetItem(strDesc);
    QTableWidgetItem *resultItem = new QTableWidgetItem(strResult);
    int rowCnt = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCnt);
    ui->tableWidget->setItem(rowCnt, 0, descItem);
    ui->tableWidget->setItem(rowCnt, 1, resultItem);
}

void BandwidthTest::onErrorMsg(const QString &errMsg)
{
    QMessageBox::warning(this, QStringLiteral("警告"), errMsg, QMessageBox::Cancel);
}

void BandwidthTest::onTestStatus(bool isTesting)
{
    m_isTesting = isTesting;
}

void BandwidthTest::initUi()
{
    QTableWidget* tablewidget = ui->tableWidget;
    QStringList strHeadList;
    strHeadList << QStringLiteral("字段名称") << QStringLiteral("值");
    tablewidget->setColumnCount(2);  // 设置表格的列数
    tablewidget->setColumnWidth(0, 175);
    tablewidget->setColumnWidth(1, 172);
    tablewidget->setHorizontalHeaderLabels(strHeadList);

    tablewidget->verticalHeader()->setVisible(false);
    tablewidget->horizontalHeader()->setSectionsMovable(false);
    tablewidget->horizontalHeader()->setSectionsClickable(false);
    tablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablewidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    tablewidget->setAlternatingRowColors(true);
    tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //禁止编辑表格
}
