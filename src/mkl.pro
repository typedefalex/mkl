TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    preset.cpp \
    hidmanager.cpp \
    settings.cpp

HEADERS += \
    preset.h \
    hidmanager.h \
    settings.h

LIBS    += -lhidapi-libusb
