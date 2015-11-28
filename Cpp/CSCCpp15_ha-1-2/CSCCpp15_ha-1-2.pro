QT += core
QT -= gui

TARGET = CSCCpp15_ha-1-2
CONFIG += console
CONFIG -= app_bundle
CONFIG   += staticlib c++11

TEMPLATE = app

SOURCES += main.cpp \
    haffman.cpp \
    input_testing.cpp

DISTFILES += \
    Heap_sort/input.txt \
    Heap_sort/output.txt \
    endian_test_input \
    endian_test_output \
    haffman_input_test.txt

HEADERS += \
    haffman.hpp
