#include "mqtt_client.h"
#include "sensor_manager.h"
#include "actuator_manager.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Starting Agricultural Machine Control Unit..." << std::endl;

    // Initialize components
    SensorManager sensorManager;
    ActuatorManager actuatorManager;
    MQTTClient mqttClient("agri-mqtt-broker", 1883, "machine-01");

    // Connect to MQTT broker and subscribe to the commands topic
    mqttClient.connect();
    mqttClient.subscribe("agri/machine/01/commands");

    // Main control loop
    while (true) {
        // 1. Read sensor data
        auto sensorData = sensorManager.readAllSensors();

        // 2. Publish sensor data via MQTT
        mqttClient.publish("agri/machine/01/sensors", sensorData);

        // 3. Check for incoming commands from MQTT
        std::string command = mqttClient.getNextCommand();
        if (!command.empty()) {
            actuatorManager.processCommand(command);
        }

        // 4. Sleep for a cycle
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}