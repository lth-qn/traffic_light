#include "trafficlight.h"
#include <QVBoxLayout>
#include <QPainter>

// TODO: we need a configuration file/section, e.g., json
const QString brokerHost = "127.0.0.1"; // Hint: no http://, only IP
const quint16 brokerPort = 1883;
const QString cmdTopic = "traffic/1/command";
const QString staTopic = "traffic/1/status";

TrafficLight::TrafficLight(QWidget *parent)
    : QMainWindow(parent), // This was QApplication(parent)
    currentColor(traffic_signal::RED), isContinuing(true) {

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

    client.setHostname(brokerHost);
    client.setPort(brokerPort);
    client.setClientId("TrafficLight_1"); // In trafficlight.cpp

    // configure receiving cmd function
    QObject::connect(&client, &QMqttClient::messageReceived, 
        [this](const QByteArray &message, const QMqttTopicName &topic) {
            // TODO: this is use to receive cmd (protobuf)
            qDebug() << "[Traffic light] Nachricht empfangen auf" << topic.name() << ":" << message;
    });

    // Sobald verbunden: Topic abonnieren
    QObject::connect(&client, &QMqttClient::connected, [this]() {
        auto sub = client.subscribe(cmdTopic);
        if (sub) {
            qDebug() << "[Subscriber] subscribe successfully for:" << cmdTopic;
        }
    });

    // // QObject::connect(&client, &QMqttClient::connected, [this]() {
    // //     qDebug() << "[Publisher] Sende Nachricht...";
    // //     // TODO: this is use to send status (protobuf)
    // //     client.publish(QMqttTopicName(staTopic), "Hallo Welt von Qt MQTT! traffic light");
    // // });

    // QTimer *pubTimer = new QTimer(this);
    // connect(pubTimer, &QTimer::timeout, [this]() {
    //     client.publish(QMqttTopicName(staTopic), "Traffic Light alive");
    // });
    // pubTimer->start(20000);

    // --- 4. VERBINDUNG STARTEN ---
    client.connectToHost();

    // mqttClient = new QMqttClient*("", CLIENT_ID); // TODO: well .. is this the design you want
    // connect(mqttClient, &TLControlPannel::sendCommand, this, &TrafficLight::handleCommand);
    // mqttClient->connectToBroker("tcp://127.0.0.1:1883");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TrafficLight::nextAutomaticLight);
    timer->start(1000);

    updateLights();
    nextAutomaticLight();
}

TrafficLight::~TrafficLight() {}

void TrafficLight::updateLights() {
    redLight->setStyleSheet(currentColor == traffic_signal::RED ? "background-color:red; border-radius:50px;" : "background-color:gray; border-radius:50px;");
    orangeLight->setStyleSheet(currentColor == traffic_signal::ORANGE ? "background-color:orange; border-radius:50px;" : "background-color:gray; border-radius:50px;");
    greenLight->setStyleSheet(currentColor == traffic_signal::GREEN ? "background-color:green; border-radius:50px;" : "background-color:gray; border-radius:50px;");

    // Publish current color
    // mqttClient->publishStatus("TL1", currentColor);
    // client->sendCommand("TL1", currentColor);
    QByteArray currentColorPayload = QByteArray::number(static_cast<int>(currentColor));
    client.publish(QMqttTopicName(staTopic), currentColorPayload);
}

// TODO: create a var for counter instead of fixed value of 5,3
void TrafficLight::nextAutomaticLight() {
    static int counter = 0;
    counter++;
    // Timing logic: red 5s, green 5s, orange 3s
    if (isContinuing) {
        if ((currentColor == traffic_signal::RED && counter >= 5) ||
            (currentColor == traffic_signal::GREEN && counter >= 5) ||
            (currentColor == traffic_signal::ORANGE && counter >= 3)) {

            switch (currentColor) {
                case traffic_signal::RED: currentColor = traffic_signal::GREEN; break;
                case traffic_signal::GREEN: currentColor = traffic_signal::ORANGE; break;
                case traffic_signal::ORANGE: currentColor = traffic_signal::RED; break;
            }
            counter = 0;
            updateLights();
        }
    }
}

void TrafficLight::handleCommand(const traffic_signal::TrafficLightCommand &cmd) {
    // if (cmd.id() != "TL1") return;
    // if (cmd.target_color() == traffic_signal::DEFAULT) {
    //     isContinuing = true;
    //     nextAutomaticLight();
    // }
    // else {
    //     currentColor = cmd.target_color();
    //     isContinuing = false;
    //     updateLights();
    // }
}
