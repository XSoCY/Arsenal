#ifndef DEVICERECVWORKER_H
#define DEVICERECVWORKER_H

#include <QObject>

class DeviceRecvWorker : public QObject
{
    Q_OBJECT
public:
    explicit DeviceRecvWorker(QObject *parent = nullptr);

signals:

};

#endif // DEVICERECVWORKER_H
