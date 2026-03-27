#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPainter>

// TODO: we need a configuration file/section
TrafficLight::TrafficLight(QWidget *parent)
    : QTrafficLight(parent), currentColor(traffic_signal::RED), isContinuing(true) {

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

    mqttClient = new TLControlPannel(this);
    connect(mqttClient, &TLControlPannel::commandReceived, this, &TrafficLight::handleCommand);
    mqttClient->connectToBroker("tcp://127.0.0.1:1883");

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TrafficLight::nextAutomaticLight);
    timer->start(1000);

    updateLights();
}

TrafficLight::~TrafficLight() {}

void TrafficLight::updateLights() {
    redLight->setStyleSheet(currentColor == traffic_signal::RED ? "background-color:red; border-radius:50px;" : "background-color:gray; border-radius:50px;");
    orangeLight->setStyleSheet(currentColor == traffic_signal::ORANGE ? "background-color:orange; border-radius:50px;" : "background-color:gray; border-radius:50px;");
    greenLight->setStyleSheet(currentColor == traffic_signal::GREEN ? "background-color:green; border-radius:50px;" : "background-color:gray; border-radius:50px;");

    // Publish current color
    mqttClient->publishStatus("TL1", currentColor);
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
    if (cmd.id() != "TL1") return;
    if (cmd.target_color() == traffic_signal::DEFAULT) {
        isContinuing = true;
        nextAutomaticLight();
    }
    else {
        currentColor = cmd.target_color();
        isContinuing = false;
        updateLights();
    }
}
