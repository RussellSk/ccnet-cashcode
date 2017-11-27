TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    cashcodeprotocol.cpp \
    serialport.cpp \
    ccpackage.cpp

HEADERS += cashcodeprotocol.h \
    cashcodeerrors.h \
    serialport.h \
    ccpackage.h \
    commands.h

INCLUDEPATH += H:\Libs\boost_1_62_0
LIBS += -lws2_32
LIBS += -LH:\Libs\bin \
        -lboost_system-mgw53-1_62 \
        -lboost_thread-mgw53-mt-1_62 \
        -lboost_chrono-mgw53-1_62



