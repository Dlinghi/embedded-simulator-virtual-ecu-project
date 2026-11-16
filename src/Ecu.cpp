#include "ecu/Ecu.h"
#include <iostream>
#include <thread>
#include <chrono>



void Ecu::execute_command(Commands command) {
    switch (command) {
        case Commands::START:
            start_motor();
            break;


        case Commands::STOP:
            stop_motor();
            break;


        case Commands::STATUS:
            print_motor_state();
            break;
    }
}


void Ecu::print_motor_state() const{
    switch (motor_state_) {
        case MotorStates::OFF:
            std::cout << "Motor state: OFF" << '\n';
            break;


        case MotorStates::STARTING:
            std::cout << "Motor state: STARTING" << '\n';
            break;


        case MotorStates::RUNNING:
            std::cout << "Motor state: RUNNING" << '\n';
            break;


        case MotorStates::STOPPING:
            std::cout << "Motor state: STOPPING" << '\n';
            break;


        case MotorStates::FAULT:
            std::cout << "Motor state: FAULT" << '\n';
            break;


        default:
            std::cout << "Motor state: UNKNOWN" << '\n';
            break;
    }
}


void Ecu::start_motor() {
    if (!change_motor_state(MotorStates::STARTING)) {
        return;
    }
    std::cout << "Motor is starting..." << '\n';

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (!change_motor_state(MotorStates::RUNNING)) {
        return;
    }
    std::cout << "Motor is running" << '\n';
}


void Ecu::stop_motor() {
    if (!change_motor_state(MotorStates::STOPPING)) {
        return;
    }
    std::cout << "Motor is stopping..." << '\n';

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (!change_motor_state(MotorStates::OFF)) {
        return;
    }
    std::cout << "Motor is OFF" << '\n';
}


bool Ecu::change_motor_state(MotorStates new_motor_state) {
    if (is_transition_allowed(new_motor_state)) {
        motor_state_ = new_motor_state;
        return true;
    }

    std::cout << "Command is not valid in the current motor state" << '\n';
    return false;
}


bool Ecu::is_transition_allowed(MotorStates new_motor_state) const {
    if (motor_state_ == MotorStates::FAULT) {
        return false;
    }

    if (motor_state_ == new_motor_state) {
        return false;
    }

    if (motor_state_ == MotorStates::OFF && new_motor_state == MotorStates::STARTING) {
        return true;
    }

    if (motor_state_ == MotorStates::STARTING && new_motor_state == MotorStates::RUNNING) {
        return true;
    }

    if (motor_state_ == MotorStates::RUNNING && new_motor_state == MotorStates::STOPPING) {
        return true;
    }

    if (motor_state_ == MotorStates::STOPPING && new_motor_state == MotorStates::OFF) {
        return true;
    }

    return false;
}
