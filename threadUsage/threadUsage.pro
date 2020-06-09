QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    device/devicerecvworker.cpp \
    device/devicesendworker.cpp \
    device/deviceui.cpp \
    main.cpp \
    mainwnd.cpp \
    monitor/SubTestItems/AGCAccuracyTest.cpp \
    monitor/SubTestItems/BandwidthTest.cpp \
    monitor/SubTestItems/CaptureTimeTest.cpp \
    monitor/SubTestItems/DemodulTimeDelay.cpp \
    monitor/SubTestItems/RCTimeDelayTest.cpp \
    monitor/SubTestItems/ScanFetureTest.cpp \
    monitor/SubTestItems/TimeMeetAccuracyTest.cpp \
    monitor/SubTestItems/waitobj.cpp \
    monitor/monitorrecvworker.cpp \
    monitor/monitorsendworker.cpp \
    monitor/monitorui.cpp

HEADERS += \
    commonTypes.h \
    device/devicerecvworker.h \
    device/devicesendworker.h \
    device/deviceui.h \
    mainwnd.h \
    monitor/SubTestItems/AGCAccuracyTest.h \
    monitor/SubTestItems/BandwidthTest.h \
    monitor/SubTestItems/CaptureTimeTest.h \
    monitor/SubTestItems/DemodulTimeDelay.h \
    monitor/SubTestItems/RCTimeDelayTest.h \
    monitor/SubTestItems/ScanFetureTest.h \
    monitor/SubTestItems/TimeMeetAccuracyTest.h \
    monitor/SubTestItems/waitobj.h \
    monitor/monitorrecvworker.h \
    monitor/monitorsendworker.h \
    monitor/monitorui.h

FORMS += \
    device/deviceui.ui \
    mainwnd.ui \
    monitor/SubTestItems/AGCAccuracyTest.ui \
    monitor/SubTestItems/BandwidthTest.ui \
    monitor/SubTestItems/CaptureTimeTest.ui \
    monitor/SubTestItems/DemodulTimeDelay.ui \
    monitor/SubTestItems/RCTimeDelayTest.ui \
    monitor/SubTestItems/ScanFetureTest.ui \
    monitor/SubTestItems/TimeMeetAccuracyTest.ui \
    monitor/monitorui.ui

TRANSLATIONS += \
    threadUsage_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
