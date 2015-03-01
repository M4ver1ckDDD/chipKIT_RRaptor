//
//  chipKIT_RRaptor_driver.cpp
//  
//
//  Created by Tomilov Andrey on 20.02.15.
//
//

#include "chipKIT_RRaptor_driver.h"

uint8_t pin_step_x=5;  // пины двигателей;
uint8_t pin_dir_x=4;
uint8_t pin_enable_x=3;

uint8_t pin_step_y=8;
uint8_t pin_dir_y=7;
uint8_t pin_enable_y=6;

uint8_t pin_step_z=11;
uint8_t pin_dir_z=10;
uint8_t pin_enable_z=9;

uint8_t pin_sensor_x_f; // пины датчиков;
uint8_t pin_sensor_x_b;
uint8_t pin_sensor_y_f;
uint8_t pin_sensor_y_b;
uint8_t pin_sensor_z_f;
uint8_t pin_sensor_z_b;

bool cycle_state=false; // иникатор цикла;

short priority_x=0; // приоритеты;
short priority_y=0;
short priority_z=0;

int pulse_delay_x=0; // величина импульса;
int pulse_delay_y=0;
int pulse_delay_z=0;

int step_delay_x=0; // задержка между импульсами;
int step_delay_y=0;
int step_delay_z=0;

int motor_step_counter_x=0; // счетчик шагов;
int motor_step_counter_y=0;
int motor_step_counter_z=0;

int motor_step_timer_x=0; // таймер мотора;
int motor_step_timer_y=0;
int motor_step_timer_z=0;

int steps_x=0;
int steps_y=0;
int steps_z=0;

//#######################################

double a_x, a_y, b_x, b_y;

//#######################################

void get_motor_data(motor_data_stb57* data, char lable)
{
    if (lable == 'x')
    {
        (*data).MOTOR_PIN_DIR=pin_dir_x;
        (*data).MOTOR_PIN_STEP=pin_step_x;
        (*data).MOTOR_PIN_ENABLE=pin_enable_x;
    }
    else{
        
        if (lable == 'y')
        {
            (*data).MOTOR_PIN_DIR=pin_dir_y;
            (*data).MOTOR_PIN_STEP=pin_step_y;
            (*data).MOTOR_PIN_ENABLE=pin_enable_y;
        }
        else{
            
            if (lable == 'z')
            {
                (*data).MOTOR_PIN_DIR=pin_dir_z;
                (*data).MOTOR_PIN_STEP=pin_step_z;
                (*data).MOTOR_PIN_ENABLE=pin_enable_z;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_motor_data(char label, int pin_step, int pin_dir, int pin_enable)
{
    if (label == 'x')
    {
        pin_step_x=pin_step;
        pin_dir_x=pin_dir;
        pin_enable_x=pin_enable;
    }
    else{
        
        if (label == 'y')
        {
            pin_step_y=pin_step;
            pin_dir_y=pin_dir;
            pin_enable_y=pin_enable;
        }
        else{
            
            if (label == 'z')
            {
                pin_step_z=pin_step;
                pin_dir_z=pin_dir;
                pin_enable_z=pin_enable;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void get_sensors_data(sensors_data* s_data)
{
    (*s_data).x_up=pin_sensor_x_f;
    (*s_data).x_down=pin_sensor_x_b;
    
    (*s_data).y_up=pin_sensor_y_f;
    (*s_data).y_down=pin_sensor_y_b;
    
    (*s_data).z_up=pin_sensor_z_f;
    (*s_data).z_down=pin_sensor_z_b;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_sensors_data(int sensor_x_up, int sensor_x_down, int sensor_y_up, int sensor_y_down, int sensor_z_up, int sensor_z_down )
{
    pin_sensor_x_f=sensor_x_up;
    pin_sensor_x_b=sensor_x_down;
    
    pin_sensor_y_f=sensor_y_up;
    pin_sensor_y_b=sensor_y_down;
    
    pin_sensor_z_f=sensor_z_up;
    pin_sensor_z_b=sensor_z_down;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

bool cycle_status()
{
    return cycle_state;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

short get_priority(char label)
{
    if (label == 'x')
    {
        return priority_x;
    }
    else{
        
        if (label == 'y')
        {
            return priority_x;
        }
        else{
            
            if (label == 'z')
            {
                return priority_x;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_priority(char label, short priority)
{
    if (label == 'x')
    {
        priority_x=priority;
    }
    else{
        
        if (label == 'y')
        {
            priority_y=priority;
        }
        else{
            
            if (label == 'z')
            {
                priority_z=priority;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
 //----------------------------------------------------------------------------------------------------------------------------------------------------

int get_pulse_delay(char lable)
{
    if(lable == 'x')
    {
        return pulse_delay_x;
    }
    else{
        
        if(lable == 'y')
        {
            return pulse_delay_y;
        }
        else{
            
            if(lable == 'z')
            {
                return pulse_delay_z;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_pulse_delay(char lable, int delay)
{
    if(lable == 'x')
    {
        pulse_delay_x=delay;
    }
    else{
        
        if(lable == 'y')
        {
            pulse_delay_y=delay;
        }
        else{
            
            if(lable == 'z')
            {
                pulse_delay_z=delay;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

int get_step_delay (char lable)
{
    if(lable == 'x')
    {
        return step_delay_x;
    }
    else{
        
        if(lable == 'y')
        {
            return step_delay_y;
        }
        else{
            
            if(lable == 'z')
            {
                return step_delay_z;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_step_delay (char lable, int delay)
{
    if(lable == 'x')
    {
        step_delay_x=delay;
    }
    else{
        
        if(lable == 'y')
        {
            step_delay_y=delay;
        }
        else{
            
            if(lable == 'z')
            {
                step_delay_z=delay;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
 //----------------------------------------------------------------------------------------------------------------------------------------------------

int get_step_counter(char lable)
{
    if(lable == 'x')
    {
        return motor_step_counter_x;
    }
    else{
        
        if(lable == 'y')
        {
            return motor_step_counter_y;
        }
        else{
            
            if(lable == 'z')
            {
                return motor_step_counter_z;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void prepare_motor(char label, int steps, int delay, bool dir, short priority) // подготовка моторов к работе;
{
    int pulse_delay;
    
    if (label == 'x') // подготовить двигатель X
    {
        pinMode(pin_enable_x,OUTPUT);
        digitalWrite(pin_enable_x, LOW);
        pinMode(pin_dir_x,OUTPUT);
        
        if (dir==true)
        {
            digitalWrite(pin_dir_x, HIGH);
        }
        else{
            
            digitalWrite(pin_dir_x, LOW);
        }
        
        pinMode(pin_step_x,OUTPUT);
        
        //pin_sensor_x_f=sensors_pins.x_up;
        //pin_sensor_x_b=sensors_pins.x_down;
        
        priority_x=priority;
        motor_step_counter_x=steps;
        step_delay_x=delay;
        pulse_delay=step_delay_x%timer_freq;
        pulse_delay_x=pulse_delay;
        motor_step_timer_x=delay-pulse_delay;
        steps_x=0;
    }
    else{
        
        if (label == 'y') // подготовить двигатель Y
        {
            pinMode(pin_enable_y,OUTPUT);
            digitalWrite(pin_enable_y, LOW);
            pinMode(pin_dir_y,OUTPUT);
            
            if (dir==true)
            {
                digitalWrite(pin_dir_y, HIGH);
            }
            else{
                
                digitalWrite(pin_dir_y, LOW);
            }
            
            pinMode(pin_step_y,OUTPUT);
            
            //pin_sensor_y_f=sensors_pins.y_up;
            //pin_sensor_y_b=sensors_pins.y_down;
            
            priority_y=priority;
            motor_step_counter_y=steps;
            step_delay_y=delay;
            pulse_delay=step_delay_y%timer_freq;
            pulse_delay_y=pulse_delay;
            motor_step_timer_y=delay-pulse_delay;
            steps_y=0;
        }
        else{
            
            if (label == 'z') // подготовить двигатель Z
            {
                pinMode(pin_enable_z,OUTPUT);
                digitalWrite(pin_enable_z, LOW);
                pinMode(pin_dir_z,OUTPUT);
                
                if (dir==true)
                {
                    digitalWrite(pin_dir_z, HIGH);
                }
                else{
                    
                    digitalWrite(pin_dir_z, LOW);
                }
                
                pinMode(pin_step_z,OUTPUT);
                
                //pin_sensor_z_f=sensors_pins.z_up;
                //pin_sensor_z_b=sensors_pins.z_down;
                
                priority_z=priority;
                motor_step_counter_z=steps;
                step_delay_z=delay;
                pulse_delay=step_delay_y%timer_freq;
                pulse_delay_y=pulse_delay;
                motor_step_timer_z=delay-pulse_delay;
                steps_z=0;
            }
            else{
                
                Serial.println("Error: wrong argument (label)!");
            }
        }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void start_cycle()
{
    cycle_state=true;
    
    initTimerISR(TIMER3,TIMER_PRESCALAR_1_8,0x64);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void stop_cycle()
{
    stopTimerISR(TIMER3);
    
    cycle_state=false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void handle_pwm(int timer)
{
    if(motor_step_counter_x > 0)
    {
        if(motor_step_timer_x < timer_freq)
        {
            digitalWrite(pin_step_x, HIGH);
            delayMicroseconds(pulse_delay_x);
            digitalWrite(pin_step_x, LOW);
            
            motor_step_timer_x=step_delay_x+timer_freq;
            motor_step_counter_x--;
            steps_x++;
        }
        
        motor_step_timer_x=motor_step_timer_x-timer_freq;
    }
    
    if(motor_step_counter_y > 0)
    {
        if(motor_step_timer_y < timer_freq)
        {
            digitalWrite(pin_step_y, HIGH);
            delayMicroseconds(pulse_delay_y);
            digitalWrite(pin_step_y, LOW);
            
            motor_step_timer_y=step_delay_y+timer_freq;
            motor_step_counter_y--;
            steps_y++
        }
        
        motor_step_timer_y=motor_step_timer_y-timer_freq;
    }
    
    if(motor_step_counter_z > 0)
    {
        if(motor_step_timer_z < timer_freq)
        {
            digitalWrite(pin_step_z, HIGH);
            delayMicroseconds(pulse_delay_z);
            digitalWrite(pin_step_z, LOW);
            
            motor_step_timer_z=step_delay_z+timer_freq;
            motor_step_counter_z--;
            steps_z++;
        }
        
        motor_step_timer_z=motor_step_timer_z-timer_freq;
    }
    
    if (motor_step_counter_x == 0 && motor_step_counter_y == 0 && motor_step_counter_z == 0)
    {
        stopTimerISR(TIMER3);
        
        cycle_state=false;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void start_motor(char label, int steps, int mdelay, bool dir, int priority)
{
    prepare_motor(label,steps,mdelay,dir,priority);
    
    start_cycle();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void line (double x0, double x1, double y0, double y1, double z0, double z1, int time, int step_prescalar) // линейная интерполяция (перемещения на мм), за время time (мс) с постоянной скоростью;
{
    pulse_delay_x=0;
    pulse_delay_y=0;
    pulse_delay_z=0;
    
    int pulse_delay=0;
    
    double delta_x=x1-x0;
    double delta_y=y1-y0;
    double delta_z=z1-z0;
    
    bool direction_x, direction_y, direction_z;
    
    if (delta_x > 0)
    {
        direction_x=false;
    }
    else{
        
        direction_x=true;
    }
    
    if (delta_y > 0)
    {
        direction_y=false;
    }
    else{
        
        direction_y=true;
    }
    
    if (delta_z > 0)
    {
        direction_z=false;
    }
    else{
        
        direction_z=true;
    }
    
    int steps_x_int=abs(number_translate((x1-x0)*STEPS_IN_MILL)*step_prescalar);
    int steps_y_int=abs(number_translate((y1-y0)*STEPS_IN_MILL)*step_prescalar);
    int steps_z_int=abs(number_translate((z1-z0)*STEPS_IN_MILL)*step_prescalar);
    
    if(steps_x_int != 0)
    {
        int step_delay_x=number_translate(time/steps_x_int);
        
        prepare_motor('x',steps_x_int,step_delay_x,direction_x,priority_x);
    }
    
    if(steps_y_int != 0)
    {
        int step_delay_y=number_translate(time/steps_y_int);
        
        prepare_motor('y',steps_y_int,step_delay_y,direction_y,priority_y);
    }
    
    if(steps_z_int != 0)
    {
        int step_delay_z=number_translate(time/steps_z_int);
        
        prepare_motor('z',steps_z_int,step_delay_z,direction_z,priority_z);
    }
    
    start_cycle();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void arc_xy (double x0, double y0, double x1, double y1, double x_c, double y_c, double radius, double speed, bool clockwise, int prescalar) // дуга окружности в одной из четвертей
{
    bool dir_x, dir_y;
    
    int k_x, k_y;
    
    if (clockwise == true)
    {
        if (x0 >= x_c && y0 > y_c)
        {
            dir_x=false;
            dir_y=true;
            k_x=1;
            k_y=-1;
        }
        else{
            
            if (x0 > x_c && y0 =< y_c)
            {
                dir_x=true;
                dir_y=true;
                k_x=-1;
                k_y=1;
            }
            else{
                
                if (x0 =< x_c && y0 < y_c)
                {
                    dir_x=true;
                    dir_y=false;
                    k_x=1;
                    k_y=-1;
                }
                else{
                    
                    if (x0 < x_c && y0 >= y_c)
                    {
                        dir_x=false;
                        dir_y=false;
                        k_x=-1;
                        k_y=1;
                    }
                }
            }
        }
    }
    
    else
    {
        if (x0 > x_c && y0 >= y_c)
        {
            dir_x=true;
            dir_y=false;
            k_x=-1;
            k_y=1;
        }
        else{
            
            if (x0 >= x_c && y0 < y_c)
            {
                dir_x=false;
                dir_y=false;
                k_x=1;
                k_y=-1;
            }
            
            else{
                
                if (x0 < x_c && y0 =< y_c)
                {
                    dir_x=false;
                    dir_y=true;
                    k_x=-1;
                    k_y=1;
                }
                else{
                    
                    if (x0 =< x_c && y0 > y_c)
                    {
                        dir_x=true;
                        dir_y=false;
                        k_x=1;
                        k_y=-1;
                    }
                }
            }
        }
    }
    
    int steps_x=abs(number_translate((x1-x0)*STEPS_IN_MILL));//кол-во шагов по горизонтали
    int steps_y=abs(number_translate((y1-y0)*STEPS_IN_MILL));//кол-во шагов по вертикали
    
    double x0_steps=abs(x0-x_c)*STEPS_IN_MILL;
    double y0_steps=abs(y0-y_c)*STEPS_IN_MILL;
    
    a_x=speed*x0_steps/radius;
    b_x=speed*k_x/radius;
    
    a_y=speed*y0_steps/radius;
    b_y=speed*k_y/radius;
    
    int start_delay_x=number_translate(1000000/a_x);
    int start_delay_y=number_translate(1000000/a_y);
    
    prepare_motor('x',steps_x,start_delay_x,dir_x,1);
    prepare_motor('y',steps_y,start_delay_y,dir_y,1);
    
    start_cycle();
}
//----------------------------------------------------------------------------------------------------------------------------------------------------


