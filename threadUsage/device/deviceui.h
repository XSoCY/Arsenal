#ifndef DEVICEUI_H
#define DEVICEUI_H

#include <QWidget>

namespace Ui {
class DeviceUi;
}

class DeviceUi : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceUi(QWidget *parent = nullptr);
    ~DeviceUi();

private:
    Ui::DeviceUi *ui;
};

#endif // DEVICEUI_H
