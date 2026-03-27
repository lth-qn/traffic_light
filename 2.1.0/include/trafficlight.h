#pragma once
#include <atomic>
#include <QTrafficLight>
#include <QLabel>
#include <QTimer>
#include "mqttclient.h"
#include "traffic_signal.pb.h"

class TrafficLight : public QTrafficLight {
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

    TLControlPannel* mqttClient;

    void updateLights();
    void nextAutomaticLight();

private slots:
    void handleCommand(const traffic_signal::TrafficLightCommand& cmd);
};
