QT += core gui widgets

TARGET = GeometryApp
TEMPLATE = app

CONFIG += c++17

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    FigureCanvas.cpp \
    DrawingTool.cpp \
    Figure.cpp \
    PolygonFigure.cpp \
    Triangle.cpp \
    Rectangle.cpp \
    Square.cpp \
    Circle.cpp \
    Polygon.cpp \
    Star.cpp \
    Hexagon.cpp \
    Rhombus.cpp \
    Quadrilateral.cpp \
    CustomFigure.cpp

HEADERS += \
    MainWindow.h \
    FigureCanvas.h \
    DrawingTool.h \
    Figure.h \
    PolygonFigure.h \
    Triangle.h \
    Rectangle.h \
    Square.h \
    Circle.h \
    Polygon.h \
    Star.h \
    Hexagon.h \
    Rhombus.h \
    Quadrilateral.h \
    CustomFigure.h

# Для Mac
macx {
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
    QMAKE_APPLE_DEVICE_ARCHS = arm64
}

# Компиляторные флаги
QMAKE_CXXFLAGS += -Wall -Wextra