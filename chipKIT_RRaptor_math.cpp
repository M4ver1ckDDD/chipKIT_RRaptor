//
//  chipKIT_RRaptor_math.cpp
//  
//
//  Created by Tomilov Andrey on 04.05.14.
//
//  RRaptor project team

#include "chipKIT_RRaptor_math.h"

int number_translate(double number_float) // функция округления числа до ближайшего целого;
{
    double number_fraction, number_int;// определяем переменные для целой и дробной части;
    
    number_fraction=modf(number_float,&number_int); // отделяем целые и дробные части в определенные переменные;
    
    if (number_float>=0)
    {
        if (2*number_fraction>=1) // если исходное число положительно и дробная часть > 0.5, то увеличиваем целую часть на 1;
        {
            number_int++;
        }
    }
    
    else
    {
        if (2*number_fraction>=-1) // если исходное число отрицательно и дробная часть > 0.5, то уменьшаем целую часть на 1;
        {
            number_int--;
        }
    }
    
    number_int=(int)number_int; // переводим целую часть в int;
    
    return number_int;
}
//---------------------------------------------------------------------------------

int max_distance(int steps_x, int steps_y, int steps_z)
{
    int distance_array[3]={steps_x,steps_y,steps_z};

    int max=0;

    for (int i=0;i<=2;i++)
    {
        if (distance_array[i]>max)
        {
            max=distance_array[i];
            return max;
        }
    }
}
