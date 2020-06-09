#ifndef WAITOBJ_H
#define WAITOBJ_H

#include <QObject>
#include <QTimer>
#include <QEventLoop>

class WaitObj : public QObject
{
    Q_OBJECT
public:
    explicit WaitObj(QObject *parent = nullptr);

signals:

public slots:
    int  waitOne(quint32 id, int waitTime = 3000);
    void wakeOne(quint32 id);

private slots:
    void onTimeOut();

private:
    quint32     m_id;
    QTimer      *m_timer;
    QEventLoop  m_loop;
};

#endif // WAITOBJ_H
