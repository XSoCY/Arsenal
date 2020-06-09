#include "TimeMeetAccuracyTest.h"
#include "ui_TimeMeetAccuracyTest.h"
#include "../monitorui.h"
#include <QMessageBox>

TimeMeetAccuracyTest::TimeMeetAccuracyTest(MonitorUi *monitorUi, MonitorSendWorker *sendWorker, MonitorRecvWorker *recvWorker, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeMeetAccuracyTest)
  , m_isTesting(false)
  , m_monitorUi(monitorUi)
  , m_sendWorker(sendWorker)
  , m_recvWorker(recvWorker)
{
    ui->setupUi(this);
    initUi();
}

TimeMeetAccuracyTest::~TimeMeetAccuracyTest()
{
    delete ui;
}

void TimeMeetAccuracyTest::on_pBtnStart_clicked()
{
    if(m_isTesting){
        QString str("上一次测试还未结束！");
        onErrorMsg(str);
        return;
    }
    m_isTesting = true;
    emit startTimeMeetTest(m_packMessage);
}

void TimeMeetAccuracyTest::on_pBtnStop_clicked()
{
    if(!m_isTesting){
        return;
    }
    m_isTesting = false;
}

void TimeMeetAccuracyTest::onTestResult(quint32 theoreticalSendTime, quint32 realSendTime, int accuracy)
{
    QString strCmdType = QString("遥控C7");
    QTableWidgetItem *descItem = new QTableWidgetItem(strCmdType);
    QString strTheoreticalTime = QString("%1").arg(theoreticalSendTime);
    QTableWidgetItem *theoreticalTimeItem = new QTableWidgetItem(strTheoreticalTime);
    QString strRealTime = QString("%1").arg(realSendTime);
    QTableWidgetItem *realTimeItem = new QTableWidgetItem(strRealTime);
    QString strAccuracy = QString("%1").arg(accuracy);
    QTableWidgetItem *accuracyItem = new QTableWidgetItem(strAccuracy);
    int rowCnt = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCnt);
    ui->tableWidget->setItem(rowCnt, 0, descItem);
    ui->tableWidget->setItem(rowCnt, 1, theoreticalTimeItem);
    ui->tableWidget->setItem(rowCnt, 2, realTimeItem);
    ui->tableWidget->setItem(rowCnt, 3, accuracyItem);
}

void TimeMeetAccuracyTest::onErrorMsg(const QString &errMsg)
{
    QMessageBox::warning(this, QStringLiteral("警告"), errMsg, QMessageBox::Cancel);
}

void TimeMeetAccuracyTest::onTestStatus(bool isTesting)
{
    m_isTesting = isTesting;
}

void TimeMeetAccuracyTest::initUi()
{
    QTableWidget* tablewidget = ui->tableWidget;
    QStringList strHeadList;
    strHeadList << QStringLiteral("命令类型") << QStringLiteral("理论发令时间") << QStringLiteral("实际发令时间") << QStringLiteral("精度");
    tablewidget->setColumnCount(4);  // 设置表格的列数
    tablewidget->setColumnWidth(0, 75);
    tablewidget->setColumnWidth(1, 95);
    tablewidget->setColumnWidth(2, 95);
    tablewidget->setColumnWidth(3, 82);
    tablewidget->setHorizontalHeaderLabels(strHeadList);

    tablewidget->verticalHeader()->setVisible(false);
    tablewidget->horizontalHeader()->setSectionsMovable(false);
    tablewidget->horizontalHeader()->setSectionsClickable(false);
    tablewidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablewidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter);
    tablewidget->setAlternatingRowColors(true);
    tablewidget->setEditTriggers(QAbstractItemView::NoEditTriggers);    //禁止编辑表格
}
