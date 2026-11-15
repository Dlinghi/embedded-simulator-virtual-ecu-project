# Embedded Simulator – Virtual ECU

A native C++20 application that simulates the basic operating states of a motor-control ECU. The project is being developed incrementally as a learning and portfolio project.

## Current version: v0.1 – Basic ECU

The application currently provides:

- An `Ecu` class that owns the motor's operating state.
- A terminal menu for starting, stopping, and checking the motor, with an option to quit.
- `OFF`, `STARTING`, `RUNNING`, `STOPPING`, and `FAULT` state values.
- A 500 ms simulated startup and shutdown delay.
- Basic handling of invalid menu input, including non-numeric input and end-of-input.

### Menu options

| Option | Action |
| --- | --- |
| `1` | Start the motor |
| `2` | Stop the motor |
| `3` | Display the motor state |
| `0` | Quit the application |

The menu uses numbers so commands are quick to enter during a demonstration. For non-numeric input, the program reports an error and displays the menu again. Entering `0` or sending end-of-input (Ctrl+D in a Linux terminal) exits the application.

### Current limitation

Startup and shutdown use a blocking 500 ms delay. The program cannot accept another menu choice during that delay. `STARTING` and `STOPPING` are therefore transient internal states and cannot be queried while the delay is running. The `FAULT` state is defined, but v0.1 does not yet include fault detection or a way to inject a fault.

## Build and run

Requirements: GCC/G++, CMake 3.20 or newer, and a terminal on Linux.

From the repository root, configure and build with CMake:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Run the executable:

```sh
./build/embedded-simulator
```

The `build/` directory contains generated build files and is excluded from Git.

## Project layout

```text
include/ecu/Ecu.h   Ecu class and command/state declarations
src/Ecu.cpp         ECU command handling and motor-state behavior
src/main.cpp        Terminal menu and program entry point
CMakeLists.txt      Build configuration
```

## Version history

### v0.1 – Basic ECU (in progress)

Introduces the ECU class, basic motor-state transitions, status output, and numeric terminal menu. The v0.1 milestone is complete when its behavior and build instructions have been reviewed and verified.

### v0.05 – Initial project setup

Established the C++20 and CMake project, compiler warning and debug sanitizer configuration, and initial repository structure. The first executable was a Hello World program used to check the build workflow.

## Roadmap

The next planned increment is v0.2: simulate target and actual motor speed, acceleration/deceleration, and motor load. Later versions will introduce the HAL, periodic execution, sensors, fault management, communications, diagnostics, and automated testing.
