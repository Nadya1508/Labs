QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

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

FORMS +=