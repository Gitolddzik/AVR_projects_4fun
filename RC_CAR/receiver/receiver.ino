#include <ServoTimer2.h>

ServoTimer2 myservo; 

int time=0;

#include <VirtualWire.h>              
byte message[VW_MAX_MESSAGE_LEN]; 
byte messageLength = VW_MAX_MESSAGE_LEN; 

int received_number = 0;

int pos = 850;   
int sil = 0;
int timer=0; //szybkosc silnika
  
void setup()
{
  Serial.begin(115200);
  
  Serial.println("Ready_To_Connect");
  
  vw_set_rx_pin(11); 
  vw_setup(2000); 
  
  vw_rx_start();
  myservo.attach(9); 

  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT); 
  pinMode(7, OUTPUT);

  pinMode(10, OUTPUT); 
  pinMode(13, OUTPUT); 
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT); 
}

void loop()
{
   if (vw_get_message(message, &messageLength)) // odebrano cokolwiek
   {
    
    for (int i = 0; i < messageLength; i++)
    {
      received_number = message[i];
    }

    if(received_number>127)
    {
        pos=map(received_number,128,255,1200,2250);
        myservo.write(pos); 
        //Serial.println(pos);   
    }
       
    if(received_number<51&&received_number>0)
    {
        digitalWrite(10, LOW); 
        digitalWrite(13, HIGH); 
        digitalWrite(2, HIGH); 
        digitalWrite(3, LOW);  
    }
      
    if(received_number>51&&received_number<63)
    {
        digitalWrite(10, HIGH); 
        digitalWrite(13, HIGH);  
        digitalWrite(2, HIGH); 
        digitalWrite(3, HIGH);  
    }
       
    if(received_number>63&&received_number<127)
    {
        digitalWrite(10, HIGH); 
        digitalWrite(13, LOW);  
        digitalWrite(2, LOW); 
        digitalWrite(3, HIGH);  
    }
       
    delay(10);
  }
  
}
