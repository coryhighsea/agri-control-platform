#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <string>

class SensorManager {
public:
    SensorManager() = default;
    std::string readAllSensors();
};

#endif // SENSOR_MANAGER_H