QT += core gui widgets
CONFIG += c++17
TARGET = traffic_light

include(common.pri)

SOURCES += src/main_trafficlight.cpp \
           src/trafficlight.cpp \
           protobuf/traffic_signal.pb.cc
