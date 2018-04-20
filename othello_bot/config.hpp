#ifndef CONFIG_H
#define CONFIG_H
// In this file all the constants for the project are defined, change any values needed here

#include "Arduino.h"

#define CONF_SENSOR_PINS A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15
#define CONF_SENSOR_PINS_V { CONF_SENSOR_PINS } 
#define CONF_X_STEPPER_PINS 22,24,26,28
#define CONF_Y_STEPPER_PINS 23,25,27,29
#define CONF_Z_SERVO_PIN 30
#define CONF_IO_PINS

#define CONF_STEPPER_STEPS 100

#define CONF_UPPER_SENS_LIM 800
#define CONF_LOWER_SENS_LIM 200

#define CONF_BOARD_COL_SZ 4
#define CONF_BOARD_ROW_SZ 4
#define CONF_BOARD_W_MM 200
#define CONF_BOARD_L_MM 200

#define CONF_N_SENSORS CONF_BOARD_COL_SZ*CONF_BOARD_ROW_SZ

#define CONF_AI_TIME_LIMIT_MS 5000

#endif //CONFIG_H
