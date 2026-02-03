QT += core gui widgets

TARGET = GeometryApp
TEMPLATE = app

CONFIG += c++17

SOURCES += \
    main.cpp \
    MainWindow.cpp \
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
    CustomFigure.cpp \
    DrawingTool.cpp \
    FigureCanvas.cpp

HEADERS += \
    MainWindow.h \
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
    CustomFigure.h \
    DrawingTool.h \
    FigureCanvas.h

# Добавьте, если используете иконки
RESOURCES += \
    icons.qrc

# Настройки компилятора
QMAKE_CXXFLAGS += -Wall -Wextra -Wpedantic