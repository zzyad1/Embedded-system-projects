/*
 * project.c
 *
 *  Created on: Jan 7, 2024
 *      Author: zyadm
 */


#include <stdio.h>

// Bonus Requirement
#define WITH_ENGINE_TEMP_CONTROLLER 1

// Function prototypes
void displayMenu();
void displayVehicleState(int engineState, int acState, int speed, int roomTemp, int engineTempControllerState, int engineTemp);

int main() {
    char input;
    int engineState = 0; // 0: OFF, 1: ON
    int acState = 0;     // 0: OFF, 1: ON
    int speed = 0;       // Vehicle speed in km/hr
    int roomTemp = 0;    // Room temperature in Celsius
    int engineTempControllerState = 0; // 0: OFF, 1: ON
    int engineTemp = 0;  // Engine temperature in Celsius

    do {
        displayMenu();
        scanf(" %c", &input);

        switch (input) {
            case 'a':
                // Turn on the vehicle engine
                engineState = 1;
                speed = 0; // default speed when engine is turned on
                roomTemp = 25; // default room temperature
                engineTempControllerState = 0; // default state of engine temperature controller
                engineTemp = 100; // default engine temperature
                break;

            case 'b':
                // Turn off the vehicle engine
                engineState = 0;
                displayMenu();
                scanf(" %c", &input); // go back to the main menu
                break;

            case 'c':
                // Quit the system
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        // Display the Sensors Set Menu
        while (engineState) {
            printf("\nSensors Set Menu:\n");
            printf("a. Turn off the engine\n");
            printf("b. Set the traffic light color\n");
            printf("c. Set the room temperature\n");
            printf("d. Set the engine temperature\n");
            printf("Enter your choice: ");

            scanf(" %c", &input);

            switch (input) {
                case 'a':
                    // Turn off the engine
                    engineState = 0;
                    break;

                case 'b':
                    // Set traffic light color
                    printf("Enter traffic light color (G/O/R): ");
                    scanf(" %c", &input);
                    switch (input) {
                        case 'G':
                            speed = 100;
                            break;
                        case 'O':
                            speed = 30;
                            break;
                        case 'R':
                            speed = 0;
                            break;
                        default:
                            printf("Invalid traffic light color. Setting speed to 0 km/hr.\n");
                            speed = 0;
                    }
                    break;

                case 'c':
                    // Set room temperature
                    printf("Enter room temperature: ");
                    scanf("%d", &roomTemp);
                    if (roomTemp < 10 || roomTemp > 30) {
                        acState = 1;
                        roomTemp = 20;
                    } else {
                        acState = 0;
                    }
                    break;

                case 'd':
                    // Set engine temperature
                    printf("Enter engine temperature: ");
                    scanf("%d", &engineTemp);
                    #if WITH_ENGINE_TEMP_CONTROLLER
                        if (engineTemp < 100 || engineTemp > 150) {
                            engineTempControllerState = 1;
                            engineTemp = 125;
                        } else {
                            engineTempControllerState = 0;
                        }
                    #endif
                    break;

                default:
                    printf("Invalid choice. Please try again.\n");
            }

            // Display current vehicle state
            displayVehicleState(engineState, acState, speed, roomTemp, engineTempControllerState, engineTemp);
        }
    } while (1);

    return 0;
}

void displayMenu() {
    printf("a. Turn on the vehicle engine\n");
    printf("b. Turn off the vehicle engine\n");
    printf("c. Quit the system\n\n");
}

void displayVehicleState(int engineState, int acState, int speed, int roomTemp, int engineTempControllerState, int engineTemp) {
    printf("\nCurrent Vehicle State:\n");
    printf("Engine state: %s\n", engineState ? "ON" : "OFF");
    printf("AC: %s\n", acState ? "ON" : "OFF");
    printf("Vehicle Speed: %d km/hr\n", speed);
    printf("Room Temperature: %d Celsius\n", roomTemp);
    #if WITH_ENGINE_TEMP_CONTROLLER
        printf("Engine Temperature Controller State: %s\n", engineTempControllerState ? "ON" : "OFF");
        printf("Engine Temperature: %d Celsius\n", engineTemp);
    #endif
}
