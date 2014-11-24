//
//  gcode_handlers.h
//  
//
//  Created by Tomilov Andrey on 16.05.14.
//
//  RRaptor project team

#include "chipKIT_RRaptor_drivers.h"
#include "chipKIT_RRaptor_math.h"

//#######################################

typedef struct coordinate_buffer
{
    double x;
    double y;
    double z;
}coordinate_buffer;

void clear_coordinate_buffer();

//#######################################


void G00 (double, double, double); //холостое перемещение

void G01 (double, double, double, double); // линейная интерполяция

void G01 (double, double, double); // линейная интерполяция с максимальной скоростью (G00)

void G02 (double, double, double, double, double); // круговая интерполяция (с заданием центра)по часовой стрелке

void G02 (double, double, double, double); // круговая интерполяция (с заданием радиуса)по часовой стрелке

void G03 (double, double, double, double, double); // круговая интерполяция (с заданием центра)против часовой стрелке

void G03 (double, double, double, double); // круговая интерполяция (с заданием радиуса)против часовой стрелке

void G04 (int time, char identificator); // задержка выполнения программы

void G17 (); // рабочая плоскость X-Y

void G18 (); // рабочая плоскость Z-X

void G19 (); // рабочая плоскость Y-Z

void G90 (); // абсолютные координаты

void G91 (); // относительные координаты






