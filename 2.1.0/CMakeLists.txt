cmake_minimum_required(VERSION 3.16)
project(TrafficSystem LANGUAGES CXX)
# project(QtProtobufExample LANGUAGES CXX)

# Qt Automatisierung
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

# Abhängigkeiten finden (vcpkg erledigt den Rest)
find_package(Qt6 COMPONENTS Core Gui Widgets Mqtt REQUIRED)
# find_package(Qt5Mqtt REQUIRED) # Entspricht QT += mqtt
find_package(Protobuf REQUIRED)
# find_package(Qt5 COMPONENTS Mqtt REQUIRED)
# find_package(Qt5 COMPONENTS Widgets Mqtt REQUIRED)

# Unterprojekte einbinden
add_subdirectory(src/traffic_light)
add_subdirectory(src/control_pannel)
