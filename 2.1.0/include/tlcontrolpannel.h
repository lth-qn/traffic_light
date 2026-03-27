#pragma once
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include "traffic_signal.pb.h"
#include "mqtt/async_client.h"

class TLControlPannel : public QObject {
    Q_OBJECT
public:
    explicit TLControlPannel(QObject *parent = nullptr);
    void connectToBroker(const std::string& address);
    void sendCommand(const std::string& id, traffic_signal::LightColor target);

// signals:
    // void trafficLightUpdated(const traffic_signal::TrafficLightStatus& status);
    // void commandReceived(const traffic_signal::TrafficLightCommand& cmd);

private:
    QLabel* redLight;
    QLabel* orangeLight;
    QLabel* greenLight;
    QPushButton* btnRed;
    QPushButton* btnGreen;
    QPushButton* btnContinue;

    void nextAutomaticLight();
    void updateLights();

    mqtt::async_client* client;
    traffic_signal::LightColor currentColor;
    void onMessage(mqtt::const_message_ptr msg);
};
