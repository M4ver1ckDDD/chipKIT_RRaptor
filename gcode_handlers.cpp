//
//  gcode_handlers.cpp
//  
//
//  Created by Tomilov Andrey on 16.05.14.
//
//  RRaptor project team

#include "gcode_handlers.h"

coordinate_buffer buffer={0,0,0};

int prescalar=1;

char plane_number;

bool coordinate_state=true; // абсолютные/относительные координаты

bool cycle_stat;

void G00 (double X, double Y, double Z) // холостой ход
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
  
    if (coordinate_state==false)
    {
        X+=buffer.x;
        Y+=buffer.y;
        Z+=buffer.z;
    }
    
    int steps_x_int=abs((number_translate((X-buffer.x)/STEPS_IN_MILL))*prescalar);
    int steps_y_int=abs((number_translate((Y-buffer.y)/STEPS_IN_MILL))*prescalar);
    int steps_z_int=abs((number_translate((Z-buffer.z)/STEPS_IN_MILL))*prescalar);

    int max_d=max_distance(steps_x_int,steps_y_int,steps_z_int);

    int time=max_d*MOTOR_MAX_DELAY;

    line (buffer.x,X,buffer.y,Y,buffer.z,Z,time,prescalar);

    buffer.x=X;
    buffer.y=Y;
    buffer.z=Z;

    Serial.print("Done: G0; ");
}
}

void G01 (double X, double Y, double Z, double F) // линейная интерполяция
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    if (coordinate_state==false)
    {
        X+=buffer.x;
        Y+=buffer.y;
        Z+=buffer.z;
    }
    double distance=sqrt(((X-buffer.x)*(X-buffer.x))+((Y-buffer.y)*(Y-buffer.y))+((Z-buffer.z)*(Z-buffer.z)));

    int time=number_translate(distance/(0.005*F));

    line (buffer.x,X,buffer.y,Y,buffer.z,Z,time,prescalar);

    buffer.x=X;
    buffer.y=Y;
    buffer.z=Z;

    Serial.print("Done: G1; ");
}
}

void G01 (double X, double Y, double Z) // линейная интерполяция
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    G00(X, Y, Z);

    Serial.print('Done: G1; ');
  }
}

void G02 (double X, double Y, double I, double J, double F) // круговая интерполяция
{

}

void G02 (double X, double Y, double R, double F) // круговая интерполяция
{

}

void G03 (double X, double Y, double I, double J, double F) // круговая интерполяция
{

}

void G03 (double X, double Y, double R, double F) // круговая интерполяция
{

}

void G04 (int time, char identificator) // задержка выполнения программы
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    if (identificator=='S')
    delay(time);
    else{

    if (identificator=='P')
        delayMicroseconds(time);
    else
        Serial.print('ERROR! Undefine settings!');
    }

    Serial.print('Done: G4; ');
  }
}

void G17 ()
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    plane_number='1';

    Serial.print('Done: G17; ');
  }
}

void G18 ()
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    plane_number='2';

    Serial.print('Done: G18; ');
  }
}

void G19 ()
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    plane_number='3';

    Serial.print('Done: G19; ');
  }
}

void G90 ()
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    coordinate_state=true;

    Serial.print('Done: G90; ');
  }
}

void G91 ()
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
    coordinate_state=false;

    Serial.print('Done: G91; ');
  }
}

void clear_coordinate_buffer()
{
  cycle_stat=cycle_status();
  if (cycle_stat==false)
  {
  buffer={0,0,0};
  }
}




