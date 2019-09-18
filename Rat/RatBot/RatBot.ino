#include <nRF24L01.h>
#include <printf.h>
#include <receiver.h>
#include <RF24.h>
#include <RF24_config.h>

float rval = 0;
float xval;
float yval;

int en1map;
int en2map;

const int out1 = 2;
const int out2 = 3;
const int en1  = 19;
const int out3 = 4;
const int out4 = 5;
const int en2  = 20;

void movemotors(int one, int two, int three, int four)
{
  digitalWrite(out1, one);
  digitalWrite(out2, two);
  digitalWrite(out4, four);
  digitalWrite(out3, three);
} 

void setup() 
{
  Serial.begin(9600);
  receiver_setup();
  // Configure the pins
  // For the motor to move forward:  pin 1 = HIGH and pin 2 = LOW
  // For the motor to move backward: pin 1 = LOW  and pin 2 = HIGH
  // For the motor to stop or break: pin 1 = LOW  and pin 2 = LOW
  // The PWM pin determines the speed of the motor
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(en2, OUTPUT); 
}

void loop() 
{
    if (receiving(rval)) {
    Serial.print("Received value: ");
    Serial.print(rval); 
    }
    
    //testing - runs motors forward at full speed for 2 seconds one time only 
    /*if (!receivedValue)
    {
      movemotors(LOW, HIGH, HIGH, LOW);
      analogWrite(en1, 255);
      analogWrite(en2, 255);
      delay(2000);
      movemotors(LOW, LOW, LOW, LOW);
      analogWrite(en1, 0);
      analogWrite(en2, 0);
      delay(2000);
      receivedValue = 1;
    }*/
    if (receiving(rval)) {
    //determines turning component
    if (rval >= 1 && rval <= 511)
      xval = rval - 256; 

    //determines forward and backward component
    else if (rval >= 1001 && rval <= 1511)
      yval = rval - 1256;

    //version 1 ==> smooth motion (speed and turning are functions of xval and yval)
    if (yval > 0) //range is not 0 adjust as needed while testing
      movemotors(LOW, HIGH, HIGH, LOW); //forward
    else if (yval < 0)
      movemotors(HIGH, LOW, LOW, HIGH); //backward
    else
    {
      if (xval == 0)
        movemotors(LOW, LOW, LOW, LOW); //STOP
      else if (xval > 0)
        movemotors(LOW, HIGH, LOW, LOW); //turn right forward (testing needed) CW
      else
        movemotors(LOW, LOW, HIGH, LOW); //turn left forward (testing needed) CCW
    }
    
    //WHAT IS THE FUNCTION
    analogWrite(en1, xval);
    analogWrite(en2, xval);
    }

        /*movemotors(HIGH, LOW, LOW, LOW); //turn right backward (testing needed) CCW
      else if () 
        movemotors(LOW, LOW, LOW, HIGH); //turn left backward (testing needed) CW
      else if () 
        movemotors(LOW, LOW, LOW, LOW); //STOP

    //version2 ==> easier to implement but not as smooth
    //speed of motors is completely dependent on forward and backward intensity ==> turning intrensity not a factor 
    //aka the motors will stop going forward as we are turning and only focus on turning 
    //which means we need a viable range where the motors do NOT turn 
    analogWrite(en1, yval);
    analogWrite(en2, yval);
        
      //map syntax reference
      //en1map = map (en1map, 0, 100, 0, 255);
      //en2map = map (en2map, 0, 100, 0, 255);*/
}
