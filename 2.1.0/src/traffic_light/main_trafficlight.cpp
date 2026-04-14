#include "include/trafficlight.h"
#include <QApplication>
#include <google/protobuf/stubs/common.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    TrafficLight w;
    w.show(); // We don't need to call any functions since the constructor will do it

    int ret = a.exec();

    google::protobuf::ShutdownProtobufLibrary();
    return ret;
}
