#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T13:38:09
#
#-------------------------------------------------

QT       += core gui network multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nyasha_0X4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        Crc.cpp \
        DebugDialog.cpp \
        LogWidget.cpp \
        RegulatorsWidget.cpp \
        RovCameraWidget.cpp \
        RovSingleton.cpp \
        RovTelimetryWidget.cpp \
        RovUdpConnection.cpp \
        ScaleFactorWidget.cpp \
        SfJoystick.cpp \
        SfJoystickSettingsDialog.cpp \
    LogWidget.cpp \
    timerwidget.cpp

HEADERS += \
        mainwindow.hpp \
        CallOnce.hpp \
        Crc.hpp \
        DebugDialog.hpp \
        LogWidget.hpp \
        RegulatorsWidget.hpp \
        RovCameraWidget.hpp \
        RovDataTypes.hpp \
        RovSingleton.hpp \
        RovTelimetryWidget.hpp \
        RovUdpConnection.hpp \
        ScaleFactorWidget.hpp \
        SfJoystick.hpp \
        SfJoystickSettingsDialog.hpp \
        Singleton.hpp \
    LogWidget.hpp \
    timerwidget.h



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-main
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-main-d
else:unix: LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-main

INCLUDEPATH += $$PWD/thirdpaty/SFML-2.4.2/include
DEPENDPATH += $$PWD/thirdpaty/SFML-2.4.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-system
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-system-d
else:unix: LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-system

INCLUDEPATH += $$PWD/thirdpaty/SFML-2.4.2/include
DEPENDPATH += $$PWD/thirdpaty/SFML-2.4.2/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-window
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-window-d
else:unix: LIBS += -L$$PWD/thirdpaty/SFML-2.4.2/lib/ -lsfml-window

INCLUDEPATH += $$PWD/thirdpaty/SFML-2.4.2/include
DEPENDPATH += $$PWD/thirdpaty/SFML-2.4.2/include



