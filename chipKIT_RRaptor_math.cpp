//
//  chipKIT_RRaptor_math.cpp
//  
//
//  Created by Tomilov Andrey on 04.05.14.
//
//  RRaptor project team

#include "chipKIT_RRaptor_math.h"

int number_translate(double number_double) // функция округления числа до ближайшего целого;
{
  int number_int = round(number_double);
    
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

