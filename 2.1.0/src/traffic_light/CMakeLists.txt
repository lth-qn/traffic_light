set(CMAKE_AUTOMOC ON)

add_executable(traffic_light 
    ${CMAKE_SOURCE_DIR}/src/traffic_light/main_trafficlight.cpp
    ${CMAKE_SOURCE_DIR}/src/traffic_light/trafficlight.cpp
    ${CMAKE_SOURCE_DIR}/include/trafficlight.h  # 👈 REQUIRED: for MOC
    ${CMAKE_SOURCE_DIR}/protobuf/traffic_signal.proto
)

# target_include_directories(traffic_light PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")
# Protobuf Generierung für dieses Target
protobuf_generate(TARGET traffic_light
                    IMPORT_DIRS ${CMAKE_SOURCE_DIR}/protobuf/)

target_include_directories(traffic_light PRIVATE 
    src 
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/include/"
    "${CMAKE_BINARY_DIR}/src"
)

target_link_libraries(traffic_light PRIVATE 
    Qt5::Widgets 
    Qt5::Mqtt 
    protobuf::libprotobuf
)
