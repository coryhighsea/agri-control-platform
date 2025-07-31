#include "actuator_manager.h"
#include <iostream>

void ActuatorManager::processCommand(const std::string& command) {
    std::cout << "[ACTUATOR] Received command: " << command << std::endl;
    
    // In a real system, you would parse the command and control hardware.
    // For example, if command is "TURN_ON_VALVE_1", you'd write to a GPIO pin.
    if (command == "ACTIVATE_IRRIGATION") {
        std::cout << "[ACTUATOR] SIMULATING: Opening irrigation valve." << std::endl;
    } else if (command == "DEACTIVATE_IRRIGATION") {
        std::cout << "[ACTUATOR] SIMULATING: Closing irrigation valve." << std::endl;
    } else {
        std::cout << "[ACTUATOR] WARNING: Unknown command received." << std::endl;
    }
}
