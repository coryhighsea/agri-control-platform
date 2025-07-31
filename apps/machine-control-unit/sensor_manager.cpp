#include "sensor_manager.h"
#include <random>
#include <sstream>

std::string SensorManager::readAllSensors() {
    // Simulate reading sensor data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(20.0, 30.0);

    double temp = distr(gen);
    double moisture = distr(gen) + 20.0;

    // Format data as a JSON string
    std::stringstream ss;
    ss << "{\"temperature\": " << temp << ", \"soil_moisture\": " << moisture << "}";
    return ss.str();
}