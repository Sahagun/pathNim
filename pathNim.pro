TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsqlite3

SOURCES += main.cpp \
    position.cpp \
    sqlconnection.cpp

HEADERS += \
    position.h \
    sqlconnection.h
