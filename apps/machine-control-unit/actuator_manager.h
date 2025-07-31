#ifndef ACTUATOR_MANAGER_H
#define ACTUATOR_MANAGER_H

#include <string>

class ActuatorManager {
public:
    ActuatorManager() = default;
    void processCommand(const std::string& command);
};

#endif // ACTUATOR_MANAGER_H

