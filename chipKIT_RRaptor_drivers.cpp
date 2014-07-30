//
//  chipKIT_RRaptor_drivers.cpp
//  
//
//  Created by Tomilov Andrey
//
//  RRaptor project team

#include "chipKIT_RRaptor_drivers.h"

motor_data_stb57 mdata_x = {3, 5, 6};    // двигатель X
motor_data_stb57 mdata_y = {26, 27, 28}; // двигатель Y
motor_data_stb57 mdata_z = {7, 8, 9};    // двигатель Z

uint8_t pin_step_x;
uint8_t pin_dir_x;
uint8_t pin_enable_x;

uint8_t pin_step_y;
uint8_t pin_dir_y;
uint8_t pin_enable_y;

uint8_t pin_step_z;
uint8_t pin_dir_z;
uint8_t pin_enable_z;

sensors_data sensors_pins = {10,11,12,13,14,15}; // пины конечных выключателей

uint8_t pin_sensor_x_f;
uint8_t pin_sensor_x_b;
uint8_t pin_sensor_y_f;
uint8_t pin_sensor_y_b;
uint8_t pin_sensor_z_f;
uint8_t pin_sensor_z_b;

motor_data_stb57 mdata_h, mdata_v; // для круговой интерполяции

bool cycle_state; // иникатор цикла;
char motor_lable; // идентификатор мотора;

int priority_x;
int priority_y;
int priority_z;

int pulse_delay_x=0;
int pulse_delay_y=0;
int pulse_delay_z=0;

int step_delay_x=0;            // задержка между импульсами;
int step_delay_y=0;
int step_delay_z=0;

int motor_step_counter_x=0;    // счетчик шагов;
int motor_step_counter_y=0;
int motor_step_counter_z=0;

int motor_step_timer_x=0;      // таймер мотора (период следования импульсов);
int motor_step_timer_y=0;
int motor_step_timer_z=0;

int time_counter=0;

void get_motor_data(motor_data_stb57* data, char lable)
{
    if (lable=='x')
    {
    (*data).MOTOR_PIN_DIR=mdata_x.MOTOR_PIN_DIR;
    (*data).MOTOR_PIN_STEP=mdata_x.MOTOR_PIN_STEP;
    (*data).MOTOR_PIN_ENABLE=mdata_x.MOTOR_PIN_ENABLE;
    }
    
    if (lable=='y')
    {
        (*data).MOTOR_PIN_DIR=mdata_y.MOTOR_PIN_DIR;
        (*data).MOTOR_PIN_STEP=mdata_y.MOTOR_PIN_STEP;
        (*data).MOTOR_PIN_ENABLE=mdata_y.MOTOR_PIN_ENABLE;
    }
    
    if (lable=='z')
    {
        (*data).MOTOR_PIN_DIR=mdata_z.MOTOR_PIN_DIR;
        (*data).MOTOR_PIN_STEP=mdata_z.MOTOR_PIN_STEP;
        (*data).MOTOR_PIN_ENABLE=mdata_z.MOTOR_PIN_ENABLE;
    }

}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_motor_data(char lable, int pin_step, int pin_dir, int pin_enable)
{
    if (lable=='x')
    {
        mdata_x.MOTOR_PIN_STEP=pin_step;
        mdata_x.MOTOR_PIN_DIR=pin_dir;
        mdata_x.MOTOR_PIN_ENABLE=pin_enable;
    }
    
    if (lable=='y')
    {
        mdata_y.MOTOR_PIN_STEP=pin_step;
        mdata_y.MOTOR_PIN_DIR=pin_dir;
        mdata_y.MOTOR_PIN_ENABLE=pin_enable;
    }
    
    if (lable=='z')
    {
        mdata_z.MOTOR_PIN_STEP=pin_step;
        mdata_z.MOTOR_PIN_DIR=pin_dir;
        mdata_z.MOTOR_PIN_ENABLE=pin_enable;
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void prepare_motor(motor_data_stb57* data, int steps, int mdelay, bool dir, char lable, int priority) // подготовка моторов к работе;
{
  if (lable=='x')
  {
    pin_enable_x=(*data).MOTOR_PIN_ENABLE;
    pinMode(pin_enable_x,OUTPUT);
    digitalWrite(pin_enable_x, LOW);
    
    pin_dir_x=(*data).MOTOR_PIN_DIR;
    pinMode(pin_dir_x,OUTPUT);
    if (dir==true)
    digitalWrite(pin_dir_x, HIGH);
    else
    digitalWrite(pin_dir_x, LOW);
            
    pin_step_x=(*data).MOTOR_PIN_STEP;
    pinMode(pin_step_x,OUTPUT);

    priority_x=priority;
    
    motor_step_counter_x=steps;

    step_delay_x=mdelay;

    motor_step_timer_x=mdelay;    
  }
  else{
  if (lable=='y')
  {
    pin_enable_y=(*data).MOTOR_PIN_ENABLE;
    pinMode(pin_enable_y,OUTPUT);
    digitalWrite(pin_enable_y, LOW);
    
    pin_dir_y=(*data).MOTOR_PIN_DIR;
    pinMode(pin_dir_y,OUTPUT);
    if (dir==true)
    digitalWrite(pin_dir_y, HIGH);
    else
    digitalWrite(pin_dir_y, LOW);
            
    pin_step_y=(*data).MOTOR_PIN_STEP;
    pinMode(pin_step_y,OUTPUT);

    priority_y=priority;
    
    motor_step_counter_y=steps;

    step_delay_y=mdelay;

    motor_step_timer_y=mdelay;  
  }
  else{
  if (lable=='z')
  {
    pin_enable_z=(*data).MOTOR_PIN_ENABLE;
    pinMode(pin_enable_z,OUTPUT);
    digitalWrite(pin_enable_z, LOW);
    
    pin_dir_z=(*data).MOTOR_PIN_DIR;
    pinMode(pin_dir_z,OUTPUT);
    if (dir==true)
    digitalWrite(pin_dir_z, HIGH);
    else
    digitalWrite(pin_dir_z, LOW);
            
    pin_step_z=(*data).MOTOR_PIN_STEP;
    pinMode(pin_step_z,OUTPUT);

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
            motor_lable='x';
            
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
            motor_lable='y';
            
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
             motor_lable='z';
            
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

char get_motor_lable()
{
    return motor_lable;
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

int get_step_delay(char lable)
{
    if(lable=='x')
    return step_delay_x;
    else{

    if(lable=='y')
    return step_delay_y;
    else{

    if(lable=='z')
    return step_delay_z;
    }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_step_delay(char lable, int new_delay)
{
    if(lable=='x')
    step_delay_x=new_delay;
    else{

    if(lable=='y')
    step_delay_y=new_delay;
    else{

    if(lable=='z')
    step_delay_z=new_delay;
    }
    }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

int get_timer_counter()
{
    return time_counter;
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void change_sensors_data(int sensor_x_up, int sensor_x_down, int sensor_y_up, int sensor_y_down, int sensor_z_up, int sensor_z_down )
{
    sensors_pins.x_up=sensor_x_up;
    sensors_pins.x_down=sensor_x_down;

    sensors_pins.y_up=sensor_y_up;
    sensors_pins.y_down=sensor_y_down;

    sensors_pins.z_up=sensor_z_up;
    sensors_pins.z_down=sensor_z_down;
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

    pulse_delay=step_delay_x;

    while (pulse_delay>timer_freq)
    {
        pulse_delay=pulse_delay-timer_freq;
    }  

    pulse_delay_x=pulse_delay;
    step_delay_x=step_delay_x-pulse_delay_x;
    
    prepare_motor(&mdata_x,steps_x_int,step_delay_x,direction_x,'x',step_prescalar);
    }

    if(steps_y_int!=0)
    {
    int step_delay_y=number_translate(time/steps_y_int);

    pulse_delay=step_delay_y;

    while (pulse_delay>timer_freq)
    {
       pulse_delay=pulse_delay-timer_freq;
    }

    pulse_delay_y=pulse_delay;
    step_delay_y=step_delay_y-pulse_delay_y;
    
    prepare_motor(&mdata_y,steps_y_int,step_delay_y,direction_y,'y',step_prescalar);
    }

    if(steps_z_int!=0)
    {
    int step_delay_z=number_translate(time/steps_z_int);

    pulse_delay=step_delay_z;

    while (pulse_delay>timer_freq)
    {
        pulse_delay=pulse_delay-timer_freq;
    }

    pulse_delay_z=pulse_delay;
    step_delay_z=step_delay_z-pulse_delay_z;
    
    prepare_motor(&mdata_z,steps_z_int,step_delay_z,direction_z,'z',step_prescalar);
    }
  
    start_cycle();

    pulse_delay_x=0;
    pulse_delay_y=0;
    pulse_delay_z=0;
 
}
//----------------------------------------------------------------------------------------------------------------------------------------------------

void arc (double coordinate_1_1, double coordinate_1_2, double coordinate_2_1, double coordinate_2_2, double center_h, double center_v, double speed, int step_prescalar, char plane_number, bool clockwise) // дуга окружности в одной из координатных четвертей
{
    double radius = sqrt(((coordinate_1_1-center_h)*(coordinate_1_1-center_h))+((coordinate_1_2-center_v)*(coordinate_1_2-center_v))); // радиус дуги
    //double m = sqrt(((coordinate_1_1-coordinate_2_1)*(coordinate_1_1-coordinate_2_1))+((coordinate_1_2-coordinate_2_2)*(coordinate_1_2-coordinate_2_2))); // хорда дуги

    double acceleration = speed*speed/radius; // центростремительное ускорение при текущей подаче

    double distance_h=abs(coordinate_2_1-center_h);
    double distance_v=abs(coordinate_2_2-center_v);

    double speed_h=abs(speed*(distance_h/radius)/STEPS_IN_MILL); // проекция подачи на горизонтальную ось
    double speed_v=abs(speed*(distance_v/radius)/STEPS_IN_MILL); // проекция подачи на вертикальную ось

    bool direction_h, direction_v; // направления вращения моторов

    double delta_h=abs((coordinate_2_1-coordinate_1_1)/STEPS_IN_MILL); // количество импульсов по горизонтали
    double delta_v=abs((coordinate_2_2-coordinate_1_2)/STEPS_IN_MILL); // количество импульсов по вертикали

    int step_delay_h=number_translate(1000000/speed_h); // начальная задержка для горизонтального мотора
    int step_delay_v=number_translate(1000000/speed_v); // начальная задержка для вертикального мотора

    char plane_start; // координатная четверть начальной точки
    
    double speed_dec_h, speed_dec_v; // декременты ск
    
    int speed_dec_ch = 1; 
    int speed_dec_cv = 1; // константы декрементов скорости

    if (clockwise==true) // выбор начальных направлений вращения моторов
    {
        if (coordinate_1_1>=center_h && coordinate_1_2>=center_v)
        {
        direction_h=true;
        direction_v=false;
        plane_start='1';
        speed_dec_ch=-speed_dec_ch;
        } else{

        if (coordinate_1_1<center_h && coordinate_1_2>=center_v)
        {
        direction_h=true;
        direction_v=true;
        plane_start='2';
        speed_dec_cv=-speed_dec_cv;
        } else{

        if (coordinate_1_1>=center_h && coordinate_1_2<center_v)
        {
        direction_h=false;
        direction_v=false;
        plane_start='4';
        speed_dec_ch=-speed_dec_ch;
        }else{

        if (coordinate_1_1<center_h && coordinate_1_2<center_v)
        {
        direction_h=false;
        direction_v=true;
        plane_start='3';
        speed_dec_cv=-speed_dec_cv;
        }
        }
        }
        }
    }

    else
    {
        if (coordinate_1_1>=center_h && coordinate_1_2>=center_v)
        {
        direction_h=false;
        direction_v=true;
        plane_start='1';
        speed_dec_cv=-speed_dec_cv;
        } else{

        if (coordinate_1_1<center_h && coordinate_1_2>=center_v)
        {
        direction_h=false;
        direction_v=false;
        plane_start='2';
        speed_dec_ch=-speed_dec_ch;
        } else{

        if (coordinate_1_1>=center_h && coordinate_1_2<center_v)
        {
        direction_h=true;
        direction_v=true;
        plane_start='4';
        speed_dec_cv=-speed_dec_cv;
        } else{

        if (coordinate_1_1<center_h && coordinate_1_2<center_v)
        {
        direction_h=true;
        direction_v=false;
        plane_start='3';
        speed_dec_ch=-speed_dec_ch;
        }
        }
        }
        }
    } // конец выбора начальных направлений вращения моторов

    //time_counter=0; // таймер

    char lable_h, lable_v; // лэйблы моторов

    if (plane_number=='1') // выбор соодтетствующих данных моторов в зависимости от координатной плоскости
    {
        mdata_h=mdata_x;
        lable_h='x';
        mdata_v=mdata_y;
        lable_v='y';
    } else{

    if (plane_number=='2')
    {
        mdata_h=mdata_x;
        lable_h='x';
        mdata_v=mdata_z;
        lable_v='z';
    } else{

    if (plane_number=='3')
    {
        mdata_h=mdata_y;
        lable_h='y';
        mdata_v=mdata_z;
        lable_v='z';
    }
    }
    }

    int steps_h=number_translate(delta_h);
    int steps_v=number_translate(delta_v);

    prepare_motor(&mdata_h, steps_h, step_delay_h, direction_h, lable_h, step_prescalar); // начальная установка мотора
    prepare_motor(&mdata_v, steps_v, step_delay_v, direction_v, lable_v, step_prescalar); // начальная установка мотора
    
    //Serial.print(radius);
    //Serial.print(" ");
    //Serial.print(acceleration);
    //Serial.print(" ");
    Serial.print(step_delay_h);
    Serial.print(" ");
    Serial.print(step_delay_v);
    Serial.print(" ");
    start_cycle();

    while(cycle_state==true) // цикл изменения задержки, для отрисовки контура (дуги окружности)
    {
        speed_dec_h=acceleration*time_counter/1000000000000;
        speed_dec_v=acceleration*time_counter/1000000000000;
    
        speed_h+=speed_dec_h*speed_dec_ch;

        speed_v+=speed_dec_v*speed_dec_cv;

        if (plane_number=='1')
        {
            step_delay_x=number_translate(1000000/speed_h);
            step_delay_y=number_translate(1000000/speed_v);
        } else{

        if (plane_number=='2')
        {
            step_delay_z=number_translate(1000000/speed_h);
            step_delay_x=number_translate(1000000/speed_v);
        } else{

        if (plane_number=='3')
        {
            step_delay_y=number_translate(1000000/speed_h);
            step_delay_z=number_translate(1000000/speed_v);
        }
        }
        }

        time_counter+=timer_freq;

        cycle_state = cycle_status();
    }
    
    Serial.print(step_delay_h);
    Serial.print(" ");
    Serial.print(step_delay_v);
}
