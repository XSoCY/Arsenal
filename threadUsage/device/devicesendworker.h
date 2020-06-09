#ifndef DEVICESENDWORKER_H
#define DEVICESENDWORKER_H

#include <QObject>

class DeviceSendWorker : public QObject
{
    Q_OBJECT
public:
    explicit DeviceSendWorker(QObject *parent = nullptr);

signals:

};

#endif // DEVICESENDWORKER_H
