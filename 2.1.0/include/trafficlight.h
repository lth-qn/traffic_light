#pragma once
#include <atomic>
#include <QMainWindow> // Change from QApplication
#include <QLabel>
#include <QTimer>
#include <QtMqtt/qmqttclient.h>
#include "traffic_light/traffic_signal.pb.h"
// #include "tlcontrolpannel.h"

class TrafficLight : public QMainWindow { // Change from QApplication
    Q_OBJECT
public:
    TrafficLight(QWidget *parent = nullptr);
    ~TrafficLight();

private:
    QLabel* redLight;
    QLabel* orangeLight;
    QLabel* greenLight;
    std::atomic<bool> isContinuing;

    QTimer* timer;
    traffic_signal::LightColor currentColor;

    // TLControlPannel* mqttClient;
    QMqttClient client;

    void updateLights();
    void nextAutomaticLight();

private slots:
    void handleCommand(const traffic_signal::TrafficLightCommand& cmd);
};
