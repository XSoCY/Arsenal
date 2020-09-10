#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include "commonTypes.h"
#include "configablewidget/qtobjectregesitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWnd; }
QT_END_NAMESPACE

class MonitorUi;
class DeviceUi;
class MainWnd : public Widget
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = nullptr);
    ~MainWnd();

private slots:
    void on_cmdLinkBtnMonitor_clicked(bool checked);

    void on_cmdLinkBtnDevice_toggled(bool checked);

private:
    void initMainUi();
    void adaptSize(QDialog *dlg);

private:
    Ui::MainWnd *ui;
    QDialog     *m_dlgMonitor = nullptr;
    QDialog     *m_dlgDevice = nullptr;
    MonitorUi   *m_monitorUi = nullptr;
    DeviceUi    *m_deviceUi = nullptr;
};
BEGIN_REGIST_CONFIGABLEOBJECT_FUNC(MainWnd)
REGIST_CONFIGABLEOBJECT_FUNC(MainWnd)
END_REGIST_CONFIGABLEOBJECT_FUNC()

#endif // MAINWND_H
