cmake_minimum_required(VERSION 3.10)
project(machine-control-unit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required libraries
find_package(Threads REQUIRED)
find_package(EclipseMosquitto REQUIRED)

# Add source files
add_executable(machine-control-unit
    main.cpp
    mqtt_client.cpp
    sensor_manager.cpp
    actuator_manager.cpp
)

# Link libraries
target_link_libraries(machine-control-unit
    PRIVATE
    Threads::Threads
    EclipseMosquitto::mosquitto
)

# Install the executable
install(TARGETS machine-control-unit
    DESTINATION bin
)
