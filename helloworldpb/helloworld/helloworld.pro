QT += widgets

CONFIG += c++17
CONFIG += static


VCPKG_PATH = "D:/Workspace/vcpkg/installed/x64-mingw-static"

INCLUDEPATH += $$VCPKG_PATH/include
# 1. Link to the Protobuf library
# On Linux: -lprotobuf | On Windows: point to your .lib path
LIBS += -L$$VCPKG_PATH/lib \
    -lprotobuf \
    -labsl_base \
    -labsl_throw_delegate \
    -labsl_strings \
    -labsl_synchronization \
    -labsl_status \
    -labsl_statusor \
    -labsl_time \
    -labsl_time_zone \
    -labsl_raw_logging_internal \
    -labsl_cord \
    -labsl_cord_internal \
    -labsl_cordz_info \
    -labsl_log_internal_message \
    -ladvapi32

# 2. Define the Custom Compiler for .proto files
PROTO_FILE = message.proto

protobuf_decl.name = protobuf header
protobuf_decl.input = PROTO_FILE
protobuf_decl.output = ${QMAKE_FILE_BASE}.pb.h
protobuf_decl.commands = protoc --cpp_out=. --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_decl.variable_out = HEADERS
QMAKE_EXTRA_COMPILERS += protobuf_decl

protobuf_impl.name = protobuf source
protobuf_impl.input = PROTO_FILE
protobuf_impl.output = ${QMAKE_FILE_BASE}.pb.cc
protobuf_impl.commands = protoc --cpp_out=. --proto_path=${QMAKE_FILE_IN_PATH} ${QMAKE_FILE_NAME}
protobuf_impl.variable_out = SOURCES
QMAKE_EXTRA_COMPILERS += protobuf_impl


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    message.proto
