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
