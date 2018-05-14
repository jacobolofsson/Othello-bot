#ifndef CONFIG_H
#define CONFIG_H
// In this file all the constants for the project are defined, change any values needed here

#include "Arduino.h"

// Debug macros
#define DEBUG 1 // Comment out this row to remove all debug statements
#ifdef DEBUG
    #define DEBUG_SETUP Serial.begin(9600)
    #define DEBUG_WR(x) Serial.print (x)
    #define DEBUG_STATE(state)                 \
    switch(state) {                            \
        case 0:                                \
            DEBUG_WR("State: IDLE\n");         \
            break;                             \
        case 1:                                \
            DEBUG_WR("State: Reading board\n");\
            break;                             \
        case 2:                                \
            char buffer[100];                  \
            Game(*board).toString(buffer);     \
            DEBUG_WR("State: AI thinking\n");  \
            DEBUG_WR(buffer);                  \
            DEBUG_WR("\n");                    \
            break;                             \
        case 3:                                \
            DEBUG_WR("State: Making move\n");  \
            DEBUG_WR(AImove->rowPos);          \
            DEBUG_WR(", ");                    \
            DEBUG_WR(AImove->colPos);          \
            DEBUG_WR("\n");                    \
            break;                             \
    } // DEBUG_STATE
#else
    #define DEBUG_SETUP 
    #define DEBUG_WR(x)
    #define DEBUG_STATE(state)
#endif

// Pins for motor controls
#define CONF_SENSOR_PINS A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15
#define CONF_SENSOR_PINS_V { CONF_SENSOR_PINS } 
#define CONF_X_STEPPER_PINS 22,24,26,28 // Not used when using AF-shield
#define CONF_Y_STEPPER_PINS 23,25,27,29 // Not used when using AF-shield
#define CONF_Z_SERVO_PIN    10
#define CONF_MAGNET_PIN_NEG 20
#define CONF_MAGNET_PIN_POS 21

// IO pins
#define CONF_IO_BUTTON_PIN    22
#define CONF_IO_SWITCH_PIN    15 // Not used
#define CONF_IDLE_LED_PIN     14 // Not used
#define CONF_READING_LED_PIN  24
#define CONF_THINKING_LED_PIN 26
#define CONF_MOVING_LED_PIN   28
#define CONF_GAMEOVER_LED_PIN 28
#define CONF_ERROR_LED_PIN    28

// Limits for sensors
#define CONF_UPPER_SENS_LIM 800
#define CONF_LOWER_SENS_LIM 200

// Physical constants
#define CONF_STEPPER_STEPS   100
#define CONF_STEPPER_RPM     30
#define CONF_STEPPER_START_X 30
#define CONF_STEPPER_START_Y 30
#define CONF_MAX_STEPS       30
#define CONF_SERVO_MAX       180

#define CONF_BOARD_COL_SZ      4
#define CONF_BOARD_ROW_SZ      4
#define CONF_BOARD_W_MM        200
#define CONF_BOARD_L_MM        200
#define CONF_STEPS_PER_COORD_X 100
#define CONF_STEPS_PER_COORD_Y 100

#define CONF_N_SENSORS CONF_BOARD_COL_SZ*CONF_BOARD_ROW_SZ

// Memory and program constants
#define CONF_AI_TIME_LIMIT_MS 5000

#define CONF_PLANNER_QUEUE_SZ 100

#endif //CONFIG_H
