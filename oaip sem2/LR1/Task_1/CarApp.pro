QT += core gui widgets

# Использование C++17
CONFIG += c++17

# Название проекта и тип
TARGET = CarApp
TEMPLATE = app

# Исходные файлы
SOURCES += \
    main.cpp \
    movable_rectangle.cpp \
    car.cpp \
    mainwindow.cpp \
    inputdialog.cpp

HEADERS += \
    movable_rectangle.h \
    car.h \
    mainwindow.h \
    inputdialog.h

# Настройки компилятора
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS += -Wall -Wextra

# Для отладки
CONFIG += debug
CONFIG += console

# Параметры сборки
macx {
    # Для macOS используем системные настройки
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 11.0
    QMAKE_APPLE_SILICON_PROCESSOR = arm64
}
else:unix:CONFIG(release, debug|release): {
    QMAKE_CXXFLAGS_RELEASE += -O2
}

# Предкомпилированные заголовки (опционально)
# PRECOMPILED_HEADER = stdafx.h