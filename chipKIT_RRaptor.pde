#include "chipKIT_RRaptor_gcode_handlers.h"
#include "chipKIT_RRaptor_parse.h"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /*G00(15,5,3);
  delay(1000);
  G00(0,0,0);
  delay(100);*/
  
  arc_xy(0,5,5,0,0,0,5,10,true,1);
}


