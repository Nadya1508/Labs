QT += core gui widgets core5compat

CONFIG += c++17
CONFIG += qt

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    shape.cpp \
    rectangle.cpp \
    car.cpp

HEADERS += \
    mainwindow.h \
    shape.h \
    rectangle.h \
    car.h

macx {
    QMAKE_INFO_PLIST = Info.plist
    TARGET = CarApp
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
    QMAKE_APPLE_SILICON_PROCESSOR = arm64
}