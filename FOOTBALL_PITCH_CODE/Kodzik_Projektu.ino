#include <Servo.h>


Servo numer1;
Servo numer2;
Servo numer3;
Servo numer4;


int x;
int y;
int a;
int b;
int time;
int war;
int war2;


void setup() {
  pinMode(4, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  
  Serial.begin(115200);
  
  numer1.attach(11);
  numer2.attach(10);
  numer3.attach(3);
  numer4.attach(9);
   
  digitalWrite(6,HIGH);
  digitalWrite(8,HIGH);
}

void loop() {
    if(time%20==19)
    {
     war2 = analogRead(A2); 
    }  
                 
     if(war2<50&&war2>0)
     {
       delay(5);
       digitalWrite(7,HIGH);
       delay(5);
       digitalWrite(7,LOW);
     }
  
     if(time%20==19)
     {
       war = analogRead(A5);      
       Serial.println(analogRead(A5)); 
     } 
     
     if(war<200&&war>0)
     {
       delay(5);
       digitalWrite(7,HIGH);
       delay(5);
       digitalWrite(7,LOW);
     }
  
  
  digitalWrite(7,LOW); 
  x=analogRead(A0);
  y=analogRead(A1);
  
    
    if(digitalRead(4)==LOW)
    {
    //there can be something intresting
    }
    
  x=map(x,0,1024,0,180); 
  y=map(y,0,1024,43,125);
  numer1.write(180-(y+3));
    
    if(x>25)
    {
      numer2.write(x);
    }
    
  a=analogRead(A3);
  b=analogRead(A4);
  
    if(digitalRead(12)==LOW)
    {
    //there can be something intresting
    }
    
  a=map(a,0,1024,0,180);  
  b=map(b,0,1024,43,125);
  numer3.write(180-(b-13));
    
    
    if(a>25)
    {
      numer4.write(a);
    }
  
  time++;
  
    if(time==30000)
    {
      time=0;
    }
  
  delay(5);
}
