//
//  chipKIT_RRaptor_drivers.h
//  
//
//  Created by Tomilov Andrey
//
//  RRaptor project team

#include "chipKIT_RRaptor_math.h"

#ifndef WProgram_h
#include "WProgram.h"
#endif

extern "C"{
#include "timer_setup.h"
}

#define STEPS_IN_MILL 0.005
#define MOTOR_MAX_DELAY 1000
#define timer_freq 10
#define PI 3.14159265

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

void get_motor_data(motor_data_stb57*, char);

void change_motor_data(char,int,int,int);

void prepare_motor (char, int, int, bool, int);

void start_cycle();

void stop_cycle();

void handle_pwm(int);

bool cycle_status();

int get_pulse_delay(char);

void change_pulse_delay(char, int);

int get_time_counter();

//void get_sensors_data (sensors_data*);

void change_sensors_data(int, int, int, int, int, int);

void line (double , double , double , double , double , double , int, int);

void arc (double, double, double, double, double, double, double, double, bool, char, int);
