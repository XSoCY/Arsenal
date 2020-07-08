#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <qglobal.h>
#include <QVector>
#include <QMetaType>

enum UiType
{
    UiType_Device = 0,
    UiType_Monitor = 1
};

struct PackMessage
{
    quint32 steps;                      //当前测试需要的步骤数
    quint32 operateId;                  //操作的唯一标志
    quint32 sendTimeRC;                 //遥控发令时延测试用到的发令时间
    quint32 sendTimeMeet;               //时间符合精度测试用到的发令时间
    quint8 rcDelayRetCnt;               //遥控发令时延测试结果个数
    quint8 demodulRetCnt;               //遥测解调时延测试结果个数
    QVector<double> agcRegisterVal;     //AGC精度测试用到的寄存器值存储容器
    QVector<double> agcResultVal;       //AGC精度测试的结果值个数
    QVector<double> bandwidthRegVal;    //环路带宽测试用到的寄存器值存储容器
    QVector<double> bandwidthResultVal; //环路带宽测试用到的结果值存储容器
    PackMessage() {
        steps = 0;
        operateId = 0;
        sendTimeRC = 0;
        sendTimeMeet = 0;
        rcDelayRetCnt = 0;
        demodulRetCnt = 0;
    }
};
Q_DECLARE_METATYPE(PackMessage)

struct UnpackMessage
{
    quint32 operateId;                  //操作的唯一标志
    quint32 sendTimeRC;                   //遥控发令时延测试用到的发令时间
    quint32 sendTimeMeet;                 //时间符合精度测试用到的发令时间
    quint8 rcDelayRetCnt;                 //遥控发令时延测试结果个数
    quint8 demodulRetCnt;                 //遥测解调时延测试结果个数
    QVector<double> agcRegisterVal;       //AGC精度测试用到的寄存器值存储容器
    QVector<double> agcResultVal;         //AGC精度测试的结果值个数
    QVector<double> bandwidthRegVal;      //环路带宽测试用到的寄存器值存储容器
    QVector<double> bandwidthResultVal;   //环路带宽测试用到的结果值存储容器
    UnpackMessage() {
        operateId = 0;
        sendTimeRC = 0;
        sendTimeMeet = 0;
        rcDelayRetCnt = 0;
        demodulRetCnt = 0;
    }
};
Q_DECLARE_METATYPE(UnpackMessage)

#endif // COMMONTYPES_H
