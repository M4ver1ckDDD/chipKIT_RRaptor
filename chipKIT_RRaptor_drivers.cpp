//
//  chipKIT_RRaptor_drivers.cpp
//  
//
//  Created by Tomilov Andrey
//
//  RRaptor project team

#include "chipKIT_RRaptor_drivers.h"

uint8_t pin_step_x;  // пины двигателей;
uint8_t pin_dir_x;
uint8_t pin_enable_x;

uint8_t pin_step_y;
uint8_t pin_dir_y;
uint8_t pin_enable_y;

uint8_t pin_step_z;
uint8_t pin_dir_z;
uint8_t pin_enable_z;

uint8_t pin_sensor_x_f; // пины датчиков;
uint8_t pin_sensor_x_b;
uint8_t pin_sensor_y_f;
uint8_t pin_sensor_y_b;
uint8_t pin_sensor_z_f;
uint8_t pin_sensor_z_b;

bool dir_h; // для круговой интерполяции;
uint8_t pin_enable_h;

bool dir_v;
uint8_t pin_enable_v;

bool cycle_state; // иникатор цикла;

int priority_x=0; // приоритеты;
int priority_y=0;
int priority_z=0;

int pulse_delay_x=0; // величина импульса;
int pulse_delay_y=0;
int pulse_delay_z=0;

int step_delay_x=0; // задержка между импульсами;
int step_delay_y=0;
int step_delay_z=0;

int motor_step_counter_x=0; // счетчик шагов;
int motor_step_counter_y=0;
int motor_step_counter_z=0;

int motor_step_timer_x=0; // таймер мотора (период следования импульсов);
int motor_step_timer_y=0;
int motor_step_timer_z=0;

void get_motor_data(motor_data_stb57* data, char lable)
{
    if (lable=='x')
    {
    (*data).MOTOR_PIN_DIR=pin_dir_x;
    (*data).MOTOR_PIN_STEP=pin_step_x;
    (*data).MOTOR_PIN_ENABLE=pin_enable_x;
    }
    
    if (lable=='y')
    {
        (*data).MOTOR_PIN_DIR=pin_dir_y;
        (*data).MOTOR_PIN_STEP=pin_step_y;
        (*data).MOTOR_PIN_ENABLE=pin_enable_y;
    }
    
    if (lable=='z')
    {
        (*data).MOTOR_PIN_DIR=pin_dir_z;
        (*data).MOTOR_PIN_STEP=pin_step_z;
        (*data).MOTOR_PIN_ENABLE=pin_enable_z;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_motor_data(char lable, int pin_step, int pin_dir, int pin_enable)
{
    if (lable=='x')
    {
        pin_step_x=pin_step;
        pin_dir_x=pin_dir;
        pin_enable_x=pin_enable;
    }
    
    if (lable=='y')
    {
        pin_step_y=pin_step;
        pin_dir_y=pin_dir;
        pin_enable_y=pin_enable;
    }
    
    if (lable=='z')
    {
        pin_step_z=pin_step;
        pin_dir_z=pin_dir;
        pin_enable_z=pin_enable;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void prepare_motor(char lable, int steps, int mdelay, bool dir, int priority) // подготовка моторов к работе;
{
  if (lable=='x') // подготовить двигатель X
  {    
    pinMode(pin_enable_x,OUTPUT);
    digitalWrite(pin_enable_x, LOW);    

    pinMode(pin_dir_x,OUTPUT);
    if (dir==true)
    digitalWrite(pin_dir_x, HIGH);
    else
    digitalWrite(pin_dir_x, LOW);            

    pinMode(pin_step_x,OUTPUT);

    pin_sensor_x_f=sensors_pins.x_up;
    pin_sensor_x_b=sensors_pins.x_down;

    priority_x=priority;
    
    motor_step_counter_x=steps;

    step_delay_x=mdelay;

    motor_step_timer_x=mdelay;    
  }
  else{
  if (lable=='y') // подготовить двигатель Y
  {    
    pinMode(pin_enable_y,OUTPUT);
    digitalWrite(pin_enable_y, LOW);    

    pinMode(pin_dir_y,OUTPUT);
    if (dir==true)
    digitalWrite(pin_dir_y, HIGH);
    else
    digitalWrite(pin_dir_y, LOW);            

    pinMode(pin_step_y,OUTPUT);

    pin_sensor_y_f=sensors_pins.y_up;
    pin_sensor_y_b=sensors_pins.y_down;

    priority_y=priority;
    
    motor_step_counter_y=steps;

    step_delay_y=mdelay;

    motor_step_timer_y=mdelay;  
  }
  else{
  if (lable=='z') // подготовить двигатель Z
  {    
    pinMode(pin_enable_z,OUTPUT);
    digitalWrite(pin_enable_z, LOW);    

    pinMode(pin_dir_z,OUTPUT);
    if (dir==true)
    digitalWrite(pin_dir_z, HIGH);
    else
    digitalWrite(pin_dir_z, LOW);            

    pinMode(pin_step_z,OUTPUT);

    pin_sensor_z_f=sensors_pins.z_up;
    pin_sensor_z_b=sensors_pins.z_down;

    priority_z=priority;
    
    motor_step_counter_z=steps;

    step_delay_z=mdelay;

    motor_step_timer_z=mdelay;  
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

void handle_pwm(int timer)
{
    if(motor_step_counter_x > 0)
    {
        
        if(motor_step_timer_x < timer_freq)
        {
            digitalWrite(pin_step_x, HIGH);

            delayMicroseconds(pulse_delay_x);
            
            digitalWrite(pin_step_x, LOW);
            
            motor_step_timer_x = step_delay_x + timer_freq;
           
            motor_step_counter_x--;
        }
        
        motor_step_timer_x -= timer_freq;
        time_counter +=timer_freq;
        
    } 
        
    if(motor_step_counter_y > 0)
    {
        
        if(motor_step_timer_y < timer_freq)
        {            
            digitalWrite(pin_step_y, HIGH);

            delayMicroseconds(pulse_delay_y);
            
            digitalWrite(pin_step_y, LOW);
            
            motor_step_timer_y = step_delay_y + timer_freq;
            
            motor_step_counter_y--;
        }
        
        motor_step_timer_y -= timer_freq;
        time_counter +=timer_freq;
        
    }        
       
    if(motor_step_counter_z > 0)
    {
        
        if(motor_step_timer_z < timer_freq)
        {            
            digitalWrite(pin_step_z, HIGH);

            delayMicroseconds(pulse_delay_z);
            
            digitalWrite(pin_step_z, LOW);
            
            motor_step_timer_z = step_delay_z + timer_freq;
            
            motor_step_counter_z--;
        }
        
        motor_step_timer_z -= timer_freq;
        time_counter +=timer_freq;
        
    }
        
    if (motor_step_counter_x==0 && motor_step_counter_y==0 && motor_step_counter_z==0)
    {
        stopTimerISR(TIMER3);
        cycle_state = false;
    }
    
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

bool cycle_status()
{
    return cycle_state;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void stop_cycle()
{
    stopTimerISR(TIMER3);
    cycle_state = false;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

int get_pulse_delay(char lable)
{
    if(lable=='x')
    return pulse_delay_x;
    else{

    if(lable=='y')
    return pulse_delay_y;
    else{

    if(lable=='z')
    return pulse_delay_z;
    }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_pulse_delay(char lable, int new_delay)
{
    if(lable=='x')
    pulse_delay_x=new_delay;
    else{

    if(lable=='y')
    pulse_delay_y=new_delay;
    else{

    if(lable=='z')
    pulse_delay_z=new_delay;
    }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

int get_time_counter()
{
    return time_counter;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void get_sensors_data(sensors_data* s_data)
{
    (*s_data).x_up=pin_sensor_x_f;
    (*s_data).x_down=pin_sensor_x_b
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

void line (double x0, double x1, double y0, double y1, double z0, double z1, int time, int step_prescalar) // линейная интерполяция (перемещения на мм), за время time (мс);

{
    int pulse_delay=0;

    double delta_x=x1-x0;
    double delta_y=y1-y0;
    double delta_z=z1-z0;

    bool direction_x, direction_y, direction_z;

    if (delta_x>0)
        direction_x=false;
    else
        direction_x=true;

    if (delta_y>0)
        direction_y=false;
    else
        direction_y=true;

    if (delta_z>0)
        direction_z=false;
    else
        direction_z=true;

    int steps_x_int=abs(number_translate((x1-x0)/STEPS_IN_MILL)*step_prescalar);
    int steps_y_int=abs(number_translate((y1-y0)/STEPS_IN_MILL)*step_prescalar);
    int steps_z_int=abs(number_translate((z1-z0)/STEPS_IN_MILL)*step_prescalar);
    
    if(steps_x_int!=0)
    {
    int step_delay_x=number_translate(time/steps_x_int);

    pulse_delay=step_delay_x%timer_freq;
    pulse_delay_x=pulse_delay;

    prepare_motor('x',steps_x_int,step_delay_x,direction_x,step_prescalar);
    }

    if(steps_y_int!=0)
    {
    int step_delay_y=number_translate(time/steps_y_int);

    pulse_delay=step_delay_y%timer_freq;
    pulse_delay_y=pulse_delay;

    prepare_motor('y',steps_y_int,step_delay_y,direction_y,step_prescalar);
    }

    if(steps_z_int!=0)
    {
    int step_delay_z=number_translate(time/steps_z_int);

    pulse_delay=step_delay_z%timer_freq;
    pulse_delay_z=pulse_delay;
    
    prepare_motor('z',steps_z_int,step_delay_z,direction_z,step_prescalar);
    }
  
    start_cycle();
 
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void arc (char lable_h, char lable_v, double x0, double y0, double x1, double y1, double x_c, double y_c, double radius, double speed, bool clockwise, int prescalar) // дуга окружности
{
    uint8_t plane;

    if (clockwise==true)
    {
        if (x0>x_c && y0>y_c)
        {
             dir_h=false;
             dir_v=true;
             plane=1;
        }

        else{
            if (x0>x_c && y0<y_c)
            {
                 dir_h=true;
                 dir_v=true;
                 plane=2;
            }

        else{
                if (x0<x_c && y0<y_c)
                {
                      dir_h=true;
                      dir_v=false;
                      plane=3;
                }

        else{
                    if (x0<x_c && y0>y_c)
                    {
                          dir_h=false;
                          dir_v=false;
                          plane=4;
                    }
                }
            }
        }
    }

    else
    {
        if (x0>x_c && y0>y_c)
        {
             dir_h=true;
             dir_v=false;
             plane=1;
        }

        else{
            if (x0>x_c && y0<y_c)
            {
                  dir_h=false;
                  dir_v=false;
                  plane=2;
            }

        else{
                if (x0<x_c && y0<y_c)
                {
                      dir_h=false;
                      dir_v=true;
                      plane=3;
                }

        else{
                    if (x0<x_c && y0>y_c)
                    {
                          dir_h=true;
                          dir_v=false;
                          plane=4;
                    }
                }
            }
        }
    }

int delta_h=abs(number_translate((x1-x0)/STEPS_IN_MILL));
int delta_v=abs(number_translate((y1-y0)/STEPS_IN_MILL));

int acceleration=

while (cycle_state==true)
{

}

}
