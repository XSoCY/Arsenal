#include "deviceui.h"
#include "ui_deviceui.h"

DeviceUi::DeviceUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceUi)
{
    ui->setupUi(this);
}

DeviceUi::~DeviceUi()
{
    delete ui;
}

void DeviceUi::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    qDebug() << Q_FUNC_INFO;
}
