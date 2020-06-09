#include "monitorui.h"
#include "ui_monitorui.h"
#include "SubTestItems/waitobj.h"

MonitorUi::MonitorUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorUi),
    m_waitObj(new WaitObj(this)),
    m_sender(new MonitorSendWorker(this, m_sendTimeRC, m_sendTimeMeet, m_rcDelayRetCnt, m_demodulRetCnt, m_agcRegisterVal, m_agcResultVal, m_bandwidthRegVal, m_bandwidthResultVal, m_waitObj)),
    m_recver(new MonitorRecvWorker(this, m_sendTimeRC, m_sendTimeMeet, m_rcDelayRetCnt, m_demodulRetCnt, m_agcRegisterVal, m_agcResultVal, m_bandwidthRegVal, m_bandwidthResultVal, m_waitObj))
{
    ui->setupUi(this);
    initUI();
    initThreadWorker();
}

MonitorUi::~MonitorUi()
{
    delete ui;
    delete m_waitObj;
    delete m_sender;
    delete m_recver;
}

void MonitorUi::onItemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)

    if (item == NULL)
    {
        return;
    }
    int type = item->type();
    bool isChecked = Qt::Checked==item->checkState(0);
    //同步父子项的状态(两级树结构)
    int cnt = item->childCount();
    if (isChecked)
    {
        CaptureTimeTest *wid = qobject_cast<CaptureTimeTest*>(ui->stackedWidget->widget(1));
        //设置勾选项对应的显示状态
        if(item->text(1).compare(QString("capTimeTest")) == 0)
        {
            if(item->checkState(0) != Qt::PartiallyChecked) //处理父子项状态同步时造成的影响
                wid->setItemVisible(ALL_ITEMS, isChecked);
        }
        else if(item->text(1).compare(QString("carrierDouble")) == 0)
        {
            wid->setItemVisible(CAEEIER_DOUBLE, isChecked);
        }
        else if(item->text(1).compare(QString("distanceCap")) == 0)
        {
            wid->setItemVisible(DISTANCE_CAPTURE, isChecked);
        }
        else if(item->text(1).compare(QString("systemCap")) == 0)
        {
            wid->setItemVisible(SYSTEM_CAPTURE, isChecked);
        }
        //设置测试项勾选状态（最多勾选一个测试项）
        stateExclusion(type);

        if (cnt > 0)
        {
            for(int i=0; i<cnt; i++)
            {
                item->child(i)->setCheckState(0, Qt::Checked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
    else if (item->checkState(0) == Qt::Unchecked)
    {
        if (cnt > 0)
        {
            for(int i=0; i<cnt; i++)
            {
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
    switch (type) {
    case 0:
        break;
    case 1:
    {
        //放置对应的展示界面
        ui->stackedWidget->setCurrentIndex(1);
    }
        break;
    case 2:
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
        break;
    case 3:
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
        break;
    case 4:
    {
        ui->stackedWidget->setCurrentIndex(4);
    }
        break;
    case 5:
    {
        ui->stackedWidget->setCurrentIndex(5);
    }
        break;
    case 6:
    {
        ui->stackedWidget->setCurrentIndex(6);
    }
        break;
    case 7:
    {
        ui->stackedWidget->setCurrentIndex(7);
    }
        break;
    default:
        break;
    }
}

void MonitorUi::onErrMsg(const QString &errMsg)
{
    qDebug() << "【Err Message】" << errMsg;
}

void MonitorUi::initThreadWorker()
{
    m_sender->moveToThread(&m_sendThread);
    m_recver->moveToThread(&m_recvThread);

    connect(&m_sendThread, &QThread::finished, m_sender, &MonitorSendWorker::deleteLater);
    connect(&m_recvThread, &QThread::finished, m_recver, &MonitorRecvWorker::deleteLater);

    m_sendThread.start();
    m_recvThread.start();
}

void MonitorUi::initUI()
{
    // 创建树形列表表头
    QStringList headerLables{"测试项", "ID"};
    ui->treeWidget->setHeaderLabels(headerLables);
    ui->treeWidget->setColumnCount(headerLables.size()-1);
    ui->treeWidget->setColumnWidth(0, 200);

    /******************* 创建测试项1 *******************/
    //创建“捕获时间测试”项 type == 1
    QTreeWidgetItem *capTimeItem = new QTreeWidgetItem(ui->treeWidget,
                       QStringList{QString("捕获时间测试"), QString("capTimeTest")}, 1);
    capTimeItem->setCheckState(0, Qt::Unchecked);
    m_testItems << capTimeItem;

    QTreeWidgetItem *carrierDouble = new QTreeWidgetItem(capTimeItem,
                     QStringList{QString("载波双捕"), QString("carrierDouble")}, 1);
    carrierDouble->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem *distanceCap = new QTreeWidgetItem(capTimeItem,
                     QStringList{QString("距离捕获"), QString("distanceCap")}, 1);
    distanceCap->setCheckState(0, Qt::Unchecked);

    capTimeItem->setExpanded(true);

//    QTreeWidgetItem *systemCap = new QTreeWidgetItem(capTimeItem,
//                     QStringList{QString("系统捕获"), QString("systemCap")}, 1);
//    systemCap->setCheckState(0, Qt::Unchecked);

    connect(ui->treeWidget, &QTreeWidget::itemChanged, this, &MonitorUi::onItemChanged);

    CaptureTimeTest *capTimeTestWid = new CaptureTimeTest(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(1, capTimeTestWid);

    /******************* 创建测试项2 *******************/
    QTreeWidgetItem *agcTestItem = new QTreeWidgetItem(ui->treeWidget,
                     QStringList{QString("AGC控制范围和控制精度测试"), QString("agcTest")}, 2);
    agcTestItem->setCheckState(0, Qt::Unchecked);
    m_testItems << agcTestItem;
    AGCAccuracyTest *AGCTestWid = new AGCAccuracyTest(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(2, AGCTestWid);

    /******************* 创建测试项3 *******************/
    QTreeWidgetItem *scanTestItem = new QTreeWidgetItem(ui->treeWidget,
                     QStringList{QString("扫描特性测试"), QString("scanTest")}, 3);
    scanTestItem->setCheckState(0, Qt::Unchecked);
    m_testItems << scanTestItem;
    ScanFetureTest *scanTestWid = new ScanFetureTest(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(3, scanTestWid);

    /******************* 创建测试项4 *******************/
    QTreeWidgetItem *bandwidthTestItem = new QTreeWidgetItem(ui->treeWidget,
                     QStringList{QString("环路带宽测试"), QString("bandwidthTest")}, 4);
    bandwidthTestItem->setCheckState(0, Qt::Unchecked);
    m_testItems << bandwidthTestItem;
    BandwidthTest *bandwidthTestWid = new BandwidthTest(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(4, bandwidthTestWid);

    /******************* 创建测试项5 *******************/
    QTreeWidgetItem *rcTimeDelayTestItem = new QTreeWidgetItem(ui->treeWidget,
                     QStringList{QString("遥控发令时延测试"), QString("rcTimeDelayTestItem")}, 5);
    rcTimeDelayTestItem->setCheckState(0, Qt::Unchecked);
    m_testItems << rcTimeDelayTestItem;
    RCTimeDelayTest *rcTimeDelayWid = new RCTimeDelayTest(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(5, rcTimeDelayWid);

    /******************* 创建测试项6 *******************/
    QTreeWidgetItem *demodulTimeDelayTestItem = new QTreeWidgetItem(ui->treeWidget,
                     QStringList{QString("遥测解调时延测试"), QString("demodulTimeDelayTestItem")}, 6);
    demodulTimeDelayTestItem->setCheckState(0, Qt::Unchecked);
    m_testItems << demodulTimeDelayTestItem;
    DemodulTimeDelay *demodulTimeDelayWid = new DemodulTimeDelay(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(6, demodulTimeDelayWid);

    /******************* 创建测试项7 *******************/
    QTreeWidgetItem *timeMeetAccuracyTestItem = new QTreeWidgetItem(ui->treeWidget,
                     QStringList{QString("时间符合精度测试"), QString("timeMeetAccuracyTestItem")}, 7);
    timeMeetAccuracyTestItem->setCheckState(0, Qt::Unchecked);
    m_testItems << timeMeetAccuracyTestItem;
    TimeMeetAccuracyTest *timeMeetAccuracyWid = new TimeMeetAccuracyTest(this, m_sender, m_recver, ui->groupBoxResult);
    ui->stackedWidget->insertWidget(7, timeMeetAccuracyWid);
}

void MonitorUi::initConnection()
{
    connect(m_sender, &MonitorSendWorker::sendMessage, this, &MonitorUi::sendMessage/*, Qt::BlockingQueuedConnection*/);
    connect(this, &MonitorUi::onMessageRecved, m_recver, &MonitorRecvWorker::onMessageRecved);
    connect(m_sender, &MonitorSendWorker::errMsg, this, &MonitorUi::onErrMsg);
    connect(m_recver, &MonitorRecvWorker::errMsg, this, &MonitorUi::onErrMsg);
}

void MonitorUi::stateExclusion(int type)
{
    foreach (QTreeWidgetItem *item, m_testItems) {
        if((item->checkState(0) != Qt::Unchecked) && (item->type() != type))
        {
            item->setCheckState(0, Qt::Unchecked);
            int cnt = item->childCount();
            if(cnt > 0)
            {
                for(int i=0; i < cnt; i++)
                {
                    item->child(i)->setCheckState(0, Qt::Unchecked);
                }
            }
        }
    }
}

void MonitorUi::updateParentItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *parent = item->parent();
    if (parent == NULL)
    {
        return;
    }

    int selectedCount = 0;
    int childCount = parent->childCount();
    for (int i = 0; i < childCount; i++)
    {
        QTreeWidgetItem *childItem = parent->child(i);
        if (childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
    }
    if (selectedCount <= 0)
    {
        parent->setCheckState(0, Qt::Unchecked);
    }
    else if (selectedCount > 0 && selectedCount < childCount)
    {
        parent->setCheckState(0, Qt::PartiallyChecked);
    }
    else if (selectedCount == childCount)
    {
        parent->setCheckState(0, Qt::Checked);
    }
}
