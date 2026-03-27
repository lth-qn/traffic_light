QT += core gui widgets
CONFIG += c++17
TARGET = traffic_pannel

include(common.pri)

SOURCES += src/main_controlpannel.cpp \
           src/tlcontrolpannel.cpp \
           protobuf/traffic_signal.pb.cc
