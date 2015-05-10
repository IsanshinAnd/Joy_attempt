QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Joy_attempt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32: LIBS += -L$$PWD/SDL2-2.0.3/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/SDL2-2.0.3/i686-w64-mingw32/include
DEPENDPATH += $$PWD/SDL2-2.0.3/i686-w64-mingw32/include
