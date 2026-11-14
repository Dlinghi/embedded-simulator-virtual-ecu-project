
#!/bin/bash

# Stop the script immediately if a command fails
set -e

BUILD_DIR="build"
BUILD_TYPE="Debug"
EXECUTABLE="$BUILD_DIR/embedded-simulator"

# Configure and compile the project
build_project () {
    echo "--> Configuring $BUILD_TYPE build..."
    cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

    echo "--> Compiling project..."
    cmake --build "$BUILD_DIR"

    echo "--> Build complete: $EXECUTABLE"
}

echo "========================================"
echo "   Embedded Simulator - Build Manager   "
echo "========================================"
echo "  1) Build Debug"
echo "  2) Clean project"
echo "  3) Build and Run"
echo "  4) Build and Debug (GDB)"
echo "  q) Quit"
echo "========================================"

read -p "Choose an option [1-4 or q]: " choice

case "$choice" in
    1)
        build_project
        ;;
    2)
        echo "--> Removing $BUILD_DIR/..."
        rm -rf "$BUILD_DIR"
        echo "--> Clean complete!"
        ;;
    3)
        build_project

        echo "--> Running executable..."
        echo "----------------------------------------"
        "./$EXECUTABLE"
        ;;
    4)
        build_project

        echo "--> Launching GDB..."
        gdb --args "./$EXECUTABLE"
        ;;
    q|Q)
        echo "Exiting."
        exit 0
        ;;
    *)
        echo "Invalid option."
        exit 1
        ;;
esac

