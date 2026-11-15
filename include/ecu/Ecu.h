#pragma once

// ==================================================
// CONSTANTS
// ==================================================

// --------------------------------------------------
// The State in which the Motor is in
enum class MotorStates {
    OFF,
    STARTING,
    RUNNING,
    STOPPING,
    FAULT
};


// --------------------------------------------------
// Basic ECU Commands
enum class Commands {
    START,
    STOP,
    STATUS
};





// ==================================================
// CLASSES
// ==================================================

// --------------------------------------------------
// Ecu Class
class Ecu {
public:
  void execute_command (Commands command);
  void print_motor_state () const;

private:
  MotorStates motor_state_{MotorStates::OFF};

  void start_motor ();
  void stop_motor ();
  void change_motor_state (MotorStates new_motor_state);
};