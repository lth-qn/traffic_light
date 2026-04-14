set(CMAKE_AUTOMOC ON)

add_executable(traffic_pannel 
    ${CMAKE_SOURCE_DIR}/src/control_pannel/main_controlpannel.cpp 
    ${CMAKE_SOURCE_DIR}/src/control_pannel/tlcontrolpannel.cpp
    ${CMAKE_SOURCE_DIR}/include/tlcontrolpannel.h  # 👈 REQUIRED: for MOC
)

# protobuf_generate(TARGET traffic_pannel)

target_include_directories(traffic_pannel PRIVATE 
    src 
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/include/"
    "${CMAKE_BINARY_DIR}/src"
)

target_link_libraries(traffic_pannel PRIVATE 
    Qt5::Widgets 
    Qt5::Mqtt 
    protobuf::libprotobuf
)
