#include<Servo.h>
Servo myservo;
String data = "";
String password = "aaa\n"; 
boolean stringComplete = false; 

void setup()
{
    Serial.begin(9600); 

   data.reserve(50);
  
  myservo.attach(9);  
  
}

void loop()
{
  serialEvent();
  if (stringComplete) 
   {
      Serial.println(data);
      delay(100);
      
        if(password.compareTo(data) == 0)
        {
              openDoor(); 
              Serial.println(" OPEN"); 
              delay(100);
         }
        else if(data.compareTo("0\n") == 0)
          {
              closeDoor();
              Serial.println(" CLOSE");  
              delay(100);
            }
        else if(password.compareTo(data))
            {
              Serial.println(" WRONG");
              delay(100);
            } 

             data= "";
       stringComplete = false;
        } 
            
}


void serialEvent() 
{
  while (Serial.available()) 
  {
      char inChar = (char)Serial.read(); 
     data += inChar;
      if (inChar == '\n') {
      stringComplete = true;
       return;
    } 
  }
 
}

void openDoor(){
  myservo.write(0);
  delay(100);   
}

void closeDoor(){
  myservo.write(90); 
  delay(100); 
}
