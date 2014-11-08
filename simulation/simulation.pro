#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T21:03:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simulation
TEMPLATE = app

INCLUDEPATH += ../include
QMAKE_CXXFLAGS += -std=c++11
DEFINES += SIMULATION

SOURCES += main.cpp\
        mainwindow.cpp \
    ../src/i2c_bus.cpp \
    ../src/i2c_slave.cpp \
    ../src/lm75.cpp \
    ../src/motorisation.cpp \
    ../src/robot.cpp \
    ../src/tourelle.cpp \
    ../src/ultrasson.cpp

HEADERS  += mainwindow.hpp \
    ../include/i2c_bus.hpp \
    ../include/i2c_slave.hpp \
    ../include/lm75.hpp \
    ../include/motorisation.hpp \
    ../include/robot.hpp \
    ../include/tourelle.hpp \
    ../include/ultrasson.hpp \
    ../include/utils.hpp

FORMS    += mainwindow.ui
