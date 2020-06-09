#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWnd; }
QT_END_NAMESPACE

class MonitorUi;
class DeviceUi;
class MainWnd : public QWidget
{
    Q_OBJECT

public:
    MainWnd(QWidget *parent = nullptr);
    ~MainWnd();

private slots:
    void on_cmdLinkBtnSender_clicked(bool checked);

    void on_cmdLinkBtnRecver_toggled(bool checked);

private:
    void adaptSize(QDialog *dlg);
private:
    Ui::MainWnd *ui;
    QDialog     *m_dlgMonitor = nullptr;
    QDialog     *m_dlgDevice = nullptr;
    MonitorUi   *m_monitorUi = nullptr;
    DeviceUi    *m_deviceUi = nullptr;
};
#endif // MAINWND_H
