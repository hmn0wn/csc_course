QT += core
QT -= gui

TARGET = CSC2ndContest
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    02a.cpp \
    02b.cpp \
    02c.cpp \
    02d.cpp \
    02e.cpp \
    02f.cpp

HEADERS += \
    all.hpp

DISTFILES += \
    02a_input \
    02b_input \
    02c_input \
    02d_input \
    02e_input \
    02f_input

