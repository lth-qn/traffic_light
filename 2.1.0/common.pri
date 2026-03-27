HEADERS += include/trafficlight.h \
           include/tlcontrolpannel.h \
           protobuf/traffic_signal.pb.h

INCLUDEPATH += ../../../vcpkg/installed/x64-windows/include ./protobuf/include
LIBS += -L"../../../vcpkg/installed/x64-windows/debug/lib" -lpaho-mqttpp3 -lpaho-mqtt3as -lprotobuf
