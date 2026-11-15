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
    if (motor_state_ == MotorStates::FAULT) {
        std::cout << "Motor has a FAULT on startup, please inspect." << '\n';
        return;
    }

    if (motor_state_ == MotorStates::OFF) {
        std::cout << "Motor is starting..." << '\n';
        change_motor_state(MotorStates::STARTING);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        change_motor_state(MotorStates::RUNNING);
        std::cout << "Motor is running" << '\n';
    } else {
        std::cout << "Motor is already ON" << '\n';
    }
}


void Ecu::stop_motor() {
    if (motor_state_ == MotorStates::FAULT) {
        std::cout << "Motor has a FAULT on shutdown, please inspect." << '\n';
        return;
    }

    if (motor_state_ != MotorStates::OFF) {
        std::cout << "Motor is stopping..." << '\n';

        change_motor_state(MotorStates::STOPPING);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        change_motor_state(MotorStates::OFF);
        std::cout << "Motor is OFF" << '\n';
    } else {
        std::cout << "Motor is already OFF" << '\n';
    }

}


void Ecu::change_motor_state(MotorStates new_motor_state) {
    motor_state_ = new_motor_state;
}