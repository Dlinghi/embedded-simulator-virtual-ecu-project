#include "ecu/Ecu.h"
#include <iostream>
#include <limits>


int main () {
    Ecu ecu;
    int read_command{};

    while (true) {
        std::cout << '\n';
        std::cout << '\n';
        std::cout << "=== ECU Interface Command Menu ===" << '\n';
        std::cout << "1. Start Motor" << '\n';
        std::cout << "2. Stop Motor" << '\n';
        std::cout << "3. Get Status of Motor" << '\n';
        std::cout << "0. Quit" << '\n';

        if (!(std::cin >> read_command)) {
            if (std::cin.eof()) {
                break;
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number from 0 to 3.\n";
            continue;
        }

        switch (read_command) {
            case 1:
                ecu.execute_command(Commands::START);
                break;


            case 2:
                ecu.execute_command(Commands::STOP);
                break;


            case 3:
                ecu.execute_command(Commands::STATUS);
                break;

        
            case 0:
                return 0;


            default:
                std::cout << "Wrong input "<< read_command << ", please try again." << '\n';
        }
    }

    return 0;
}