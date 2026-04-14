#include "include/tlcontrolpannel.h"
#include <QApplication>
#include <google/protobuf/stubs/common.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    TLControlPannel w;
    w.show();

    int ret = a.exec();

    google::protobuf::ShutdownProtobufLibrary();
    return ret;
}
