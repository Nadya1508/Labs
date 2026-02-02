QT += core gui widgets

CONFIG += c++17
CONFIG += debug_and_release

TARGET = GeometryApp
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    FigureCanvas.cpp \
    Figure.cpp \
    PolygonFigure.cpp \
    Triangle.cpp \
    Quadrilateral.cpp \
    Rectangle.cpp \
    Square.cpp \
    Rhombus.cpp \
    Hexagon.cpp \
    Star.cpp \
    Circle.cpp \
    CustomFigure.cpp

HEADERS += \
    MainWindow.h \
    FigureCanvas.h \
    Figure.h \
    PolygonFigure.h \
    Triangle.h \
    Quadrilateral.h \
    Rectangle.h \
    Square.h \
    Rhombus.h \
    Hexagon.h \
    Star.h \
    Circle.h \
    CustomFigure.h

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
macx: QMAKE_APPLE_DEVICE_ARCH = arm64