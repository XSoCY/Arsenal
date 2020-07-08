#ifndef DEVICEUI_H
#define DEVICEUI_H

#include <QWidget>
#include "commonTypes.h"

namespace Ui {
class DeviceUi;
}

class DeviceUi : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceUi(QWidget *parent = nullptr);
    ~DeviceUi();

signals:
    void sigDisplayStatus(UiType uiType, bool isDisplay);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::DeviceUi *ui;
};

#endif // DEVICEUI_H
