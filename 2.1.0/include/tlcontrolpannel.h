#pragma once
#include <QMainWindow> // Change from QApplication
#include <QLabel>
#include <QPushButton>
#include "traffic_light/traffic_signal.pb.h"
// Ersetze: #include "mqtt/async_client.h"
// Durch:
#include <QtMqtt/qmqttclient.h>

class TLControlPannel : public QMainWindow { // change from qobject to qmainwindow
    Q_OBJECT
public:
    TLControlPannel(QWidget *parent = nullptr);
    // ~TLControlPannel();
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

    // mqtt::async_client* client;
    QMqttClient client;
    traffic_signal::LightColor currentColor;
    // void onMessage(mqtt::const_message_ptr msg);
    void onMessage(const QByteArray &payload, const QMqttTopicName &topic);
};
