QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

INCLUDEPATH += D:\OpenCV\opencv\release\install\include

LIBS += D:\OpenCV\opencv\release\bin\libopencv_core455.dll
LIBS += D:\OpenCV\opencv\release\bin\libopencv_highgui455.dll
LIBS += D:\OpenCV\opencv\release\bin\libopencv_imgcodecs455.dll
LIBS += D:\OpenCV\opencv\release\bin\libopencv_imgproc455.dll
LIBS += D:\OpenCV\opencv\release\bin\libopencv_calib3d455.dll

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
greaterThan(QT_MAJOR_VERSION, 4) {
    TARGET_ARCH=$${QT_ARCH}
} else {
    TARGET_ARCH=$${QMAKE_HOST.arch}
}

contains(TARGET_ARCH, x86_64) {
    ARCHITECTURE = x64
} else {
    ARCHITECTURE = x86
}

win32-g++:contains(ARCHITECTURE, x86): {
    INCLUDEPATH += D:/Developing/boost/boost_mingw1120_64/include/boost-1_79
    LIBS += "-LD:/Developing/boost/boost_mingw1120_64/lib" \
                -llibboost_date_time-mgw11-mt-x32-1_79 \
                -llibboost_system-mgw11-mt-x32-1_79 \
                -llibboost_filesystem-mgw11-mt-x32-1_79
}
win32-g++:contains(ARCHITECTURE, x64): {
    INCLUDEPATH += D:/Developing/boost/boost_mingw1120_64/include/boost-1_79
    LIBS += "-LD:/Developing/boost/boost_mingw1120_64/lib" \
                -llibboost_date_time-mgw11-mt-x64-1_79 \
                -llibboost_system-mgw11-mt-x64-1_79 \
                -llibboost_filesystem-mgw11-mt-x64-1_79
}

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

win32:RC_FILE = iconfile.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
