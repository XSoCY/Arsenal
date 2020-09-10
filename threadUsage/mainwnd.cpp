#include "mainwnd.h"
#include "ui_mainwnd.h"
#include "monitor/monitorui.h"
#include "device/deviceui.h"

#include <QDialog>
#include <QScreen>
#include <QLabel>

MainWnd::MainWnd(QWidget *parent)
    : Widget(parent)
    , ui(new Ui::MainWnd)
{
    ui->setupUi(this);
    initMainUi();
}

MainWnd::~MainWnd()
{
    delete ui;
}

void MainWnd::on_cmdLinkBtnMonitor_clicked(bool checked)
{
    if(m_dlgMonitor == nullptr) {
        m_dlgMonitor = new QDialog(this);
    }
    if(checked) {

        //create and show Monitor UI.
        if(m_monitorUi == nullptr) {

            QVBoxLayout *vLayout = new QVBoxLayout(m_dlgMonitor);
            vLayout->setContentsMargins(0, 0, 0, 0);
            m_monitorUi = new MonitorUi(m_dlgMonitor);
            vLayout->addWidget(m_monitorUi);
            adaptSize(m_dlgMonitor);

            connect(m_dlgMonitor, &QDialog::finished, this, [this]{
                ui->cmdLinkBtnMonitor->setChecked(false);
            });
        }
        m_dlgMonitor->show();

    } else {

        //close the Monitor UI.
        m_dlgMonitor->close();
    }
    //temp test
    QWidget *label = new QLabel(this);
    ui->textEdit->setText(label->metaObject()->className());
    qDebug() << "objectName: " << label->objectName();
}

void MainWnd::on_cmdLinkBtnDevice_toggled(bool checked)
{
    if(m_dlgDevice == nullptr) {
        m_dlgDevice = new QDialog(this);
    }
    if(checked) {

        //create and show Device UI.
        if(m_deviceUi == nullptr) {

            QVBoxLayout *vLayout = new QVBoxLayout(m_dlgDevice);
            vLayout->setContentsMargins(0, 0, 0, 0);
            m_deviceUi = new DeviceUi(m_dlgDevice);
            vLayout->addWidget(m_deviceUi);
            adaptSize(m_dlgDevice);

            connect(m_dlgDevice, &QDialog::finished, this, [this]{
                ui->cmdLinkBtnDevice->setChecked(false);
            });
        }
        m_dlgDevice->show();

    } else {

        //close the Device UI.
        m_dlgDevice->close();
    }
}

void MainWnd::initMainUi()
{
}

void MainWnd::adaptSize(QDialog *dlg)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenRect =  screen->availableVirtualGeometry();

    dlg->resize(screenRect.width()/2+3,screenRect.height()*3/5);
}
