#include "gcode_handlers.h"

//motor_data_stb57 data_x = {26, 5, 6};    // двигатель X
//int pin=data_x.MOTOR_PIN_STEP;

void setup()
{
  Serial.begin(9600);
  //pinMode(pin,OUTPUT);
//prepare_motor(&data_x,1000,1000,true,'x',1);
//start_cycle();

//line(0,1,0,10,0,0,10000000,1);
//clear_coordinate_buffer();

//G01 (0,10,0);

//G00(5,0,0);
//delay(5000);
//G00(0,0,0);

}

void loop()
{
G00(5,0,0);
delay(1000);
G00(5,5,0);
delay(1000);
G00(0,5,0);
delay(1000);
G00(0,0,0);
delay(1000);
}


