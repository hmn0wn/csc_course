QT += core
QT -= gui

TARGET = CSC3dContest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    03a.cpp \
    03b.cpp \
    03c.cpp \
    03g.cpp \
    03d.cpp

DISTFILES += \
    03a_input \
    03b_input \
    03c_input \
    03d_input \
    03g_input

HEADERS += \
    all.hpp

