#include <transmitter.h>
#include <IMU.h>
#include <sensor_fusion.h>

extern float IMU_X; //three axes for gyro values
extern float IMU_Y;
extern float IMU_Z;
#define SCL 19 //IMU pins
#define SDA 18

int getGyro(float input) //converts gyro values to servo angles for the rat wheels
{
  int val = input * 100;
  val = map(val, -100, 100, 0, 511);
  return val;
}

void setup() { 
  imu_setup();
  pinMode(SCL, INPUT);
  pinMode(SDA, INPUT); 
  transmitter_setup();
  Serial.begin(115200);
}

void loop() {
  imu_loop();
  float v1 = getGyro(IMU_X);
  float v2 = 1000 + getGyro(IMU_Y);
  
  sending(v1); //sending to rat
  Serial.print("v1: ");
  Serial.println(v1);
  
  sending(v2); //sending to rat
  Serial.print("v2: ");
  Serial.println(v2);
  
  //Serial.println("sent y");
//delay(30);
}
