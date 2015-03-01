//
//  chipKIT_RRaptor_driver.h
//  
//
//  Created by Tomilov Andrey on 20.02.15.
//
//

#include "chipKIT_RRaptor_math.h"

#include "WProgram.h"

extern "C"{
#include "timer_setup.h"
}

#include <limits.h>

//#######################################

const int STEPS_IN_MILL=200;
const float MILL_IN_STEP=0.005;
const int MOTOR_MIN_DELAY=800;
const int timer_freq=20;

typedef struct motor_data_stb57
{
    uint8_t MOTOR_PIN_STEP;
    uint8_t MOTOR_PIN_DIR;
    uint8_t MOTOR_PIN_ENABLE;
}motor_data_stb57;

typedef struct sensors_data
{
    int x_up;
    int x_down;
    int y_up;
    int y_down;
    int z_up;
    int z_down;
}sensors_data;

//#######################################

void get_motor_data(motor_data_stb57*, char);

void change_motor_data(char,int,int,int);

void get_sensors_data (sensors_data*);

void change_sensors_data(int, int, int, int, int, int);

bool cycle_status();

short get_priority(char);

void change_priority(char, short);

int get_pulse_delay(char);

void change_pulse_delay(char, int);

int get_step_delay (char);

void change_step_delay (char, int);

int get_step_counter(char);

void change_step_counter(char, int);

void prepare_motor (char, int, int, bool, short);

void start_cycle();

void stop_cycle();

void handle_pwm(int);

void start_motor(char, int, int, bool, int);

void line (double , double , double , double , double , double , int, int);

void arc_xy (double, double, double, double, double, double, double, double, bool, int);
