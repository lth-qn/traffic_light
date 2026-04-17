#include "tlcontrolpannel.h"
#include <QtMqtt/qmqttclient.h>
#include <QVBoxLayout>
#include <QDebug>
#include <QMqttClient>

// const std::string STATUS_TOPIC = "traffic_signal/status";
// const std::string COMMAND_TOPIC = "traffic_signal/command";
// const std::string CLIENT_ID = "qt_subscriber";
const QString brokerHost = "127.0.0.1"; // Hint: no http://, only IP
const quint16 brokerPort = 1883;
const QString cmdTopic = "traffic/1/command";
const QString staTopic = "traffic/1/status";

TLControlPannel::TLControlPannel(QWidget *parent) 
    : QMainWindow(parent) // This was QApplication(parent)
    {

    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout(central);

    redLight = new QLabel(this);
    orangeLight = new QLabel(this);
    greenLight = new QLabel(this);

    redLight->setFixedSize(100,100);
    orangeLight->setFixedSize(100,100);
    greenLight->setFixedSize(100,100);

    layout->addWidget(redLight);
    layout->addWidget(orangeLight);
    layout->addWidget(greenLight);

    // new Buttons 
    btnRed = new QPushButton("Set Red", this);
    btnGreen = new QPushButton("Set Green", this);
    btnContinue = new QPushButton("Continue", this);

    // add Buttons to Layout
    layout->addWidget(btnRed);
    layout->addWidget(btnGreen);
    layout->addWidget(btnContinue);

    // client = new mqtt::async_client("", CLIENT_ID);
    // client = new QMqttClient*("", CLIENT_ID);
    client.setClientId("ControlPanel_1"); // In tlcontrolpannel.cpp
    
    // configure receiving cmd function
    QObject::connect(&client, &QMqttClient::messageReceived, 
        [](const QByteArray &message, const QMqttTopicName &topic) {
            // TODO: this is use to receive cmd (protobuf)
            qDebug() << "[Control pannel] message received" << topic.name() << ":" << message;
    });

    // Sobald verbunden: Topic abonnieren
    QObject::connect(&client, &QMqttClient::connected, [this]() {
        auto sub = client.subscribe(staTopic);
        if (sub) {
            qDebug() << "[Subscriber] subscribe successfully for:" << staTopic;
        }
    });

    QObject::connect(&client, &QMqttClient::connected, [this]() {
        qDebug() << "[Publisher] Sende Nachricht...";
        // TODO: this is use to send status (protobuf)
        client.publish(QMqttTopicName(cmdTopic), "Hallo Welt von Qt MQTT control panel!");
    });

    // --- 4. VERBINDUNG STARTEN ---
    client.connectToHost();

    
    // // 1. Verbindung für den "Red" Button
    // connect(btnRed, &QPushButton::clicked, this, [this]() {
    //     qDebug() << "red control clicked!";
    //     sendCommand("TL1", traffic_signal::RED);
    // });

    // // 2. Verbindung für den "Green" Button
    // connect(btnGreen, &QPushButton::clicked, this, [this]() {
    //     qDebug() << "green control clicked!";
    //     sendCommand("TL1", traffic_signal::GREEN);
    // });

    // // 3. Verbindung für den "Continue" Button (z.B. für MQTT-Logik)
    // connect(btnContinue, &QPushButton::clicked, this, [this]() {
    //     // Hier deine Logik für den MQTT-Client oder Programmfluss
    //     qDebug() << "Continue clicked!";
    //     sendCommand("TL1", traffic_signal::DEFAULT);
    // });

}

void TLControlPannel::connectToBroker(const std::string &address) {
    // client->set_server_uri(address);
    // client->connect()->wait();
    // client->start_consuming();
    // client->subscribe(STATUS_TOPIC, 1)->wait();

    // std::thread([this]() {
    //     while (true) {
    //         auto msg = client->consume_message();
    //         if (msg) onMessage(msg);
    //     }
    // }).detach();
}

// void TLControlPannel::onMessage(mqtt::const_message_ptr msg) {
//     traffic_signal::TrafficLightStatus status;
//     if (status.ParseFromString(msg->get_payload())) {
//         updateLights();
//     }
// }

// 1. Ändere die Signatur: Qt MQTT übergibt meist das Payload (QByteArray) direkt
void TLControlPannel::onMessage(const QByteArray &payload, const QMqttTopicName &topic) {
    // traffic_signal::TrafficLightStatus status;

    // // 2. Nutze ParseFromArray, da QByteArray direkt darauf abgebildet werden kann
    // if (status.ParseFromArray(payload.data(), payload.size())) {
    //     // Hier kannst du jetzt auf die Daten in 'status' zugreifen
    //     updateLights();
    // }
}

void TLControlPannel::updateLights() {
    // redLight->setStyleSheet(currentColor == traffic_signal::RED ? "background-color:red; border-radius:50px;" : "background-color:gray; border-radius:50px;");
    // orangeLight->setStyleSheet(currentColor == traffic_signal::ORANGE ? "background-color:orange; border-radius:50px;" : "background-color:gray; border-radius:50px;");
    // greenLight->setStyleSheet(currentColor == traffic_signal::GREEN ? "background-color:green; border-radius:50px;" : "background-color:gray; border-radius:50px;");

}

void TLControlPannel::sendCommand(const std::string &id, traffic_signal::LightColor target) {
    // traffic_signal::TrafficLightCommand cmd;
    // cmd.set_id(id);
    // cmd.set_target_color(target);

    // std::string out;
    // cmd.SerializeToString(&out);
    // client->publish(COMMAND_TOPIC, out.c_str(), out.size(), 1, false);
}