
#include <VirtualWire.h>
#include <Wire.h>
#include <MPU6050.h>
#define size 1

MPU6050 mpu;

unsigned long timer = 0;
float timeStep = 0.01;
float pitch = 0;
float roll = 0;
float yaw = 0;
long int time=0;
int pot = A0;
byte TX_buffer[size]={0};
byte i;

void setup() 
{
  
  vw_set_tx_pin(12);
  vw_setup(2000); 
  for(i=0;i<size;i++)
  {
     TX_buffer[i]=i;
  }

  Serial.begin(115200);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Błąd łączenia z żyroskopem");
    delay(500);
  }
 
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  
  pinMode(7, INPUT_PULLUP);
}

void loop()
{ 
  Vector norm = mpu.readNormalizeGyro();
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  if(digitalRead(7)==LOW)
  {
    yaw=0;
    roll=0;
    pitch=0;
  }
  
  roll+=16;
  pitch+=16;

  if(time%2==0)
  {
    int val = map(roll,0,35,0,126);
    TX_buffer[0] = val;  
    vw_send(TX_buffer, size); 
    vw_wait_tx();
  }


  if(time%2==1)
  {
    int val = map(pitch,0,35,128,255);
    TX_buffer[0] = val;  
    vw_send(TX_buffer, size); 
    vw_wait_tx();
    //Serial.println(val);
  }

  timer = millis();

  roll-=16;
  pitch-=16;

  delay((timeStep*1000) - (millis() - timer));

  time++;
  if(time>=32000)
  {time=0;}
}
