#include<Servo.h>
Servo myservo;
String data = "";
String password = "aaa\n"; // this is the password for opening and closing your door
                            // you can set any pasword you like using digit and symbols
boolean stringComplete = false; 

void setup()
{
    Serial.begin(9600); 

  //The String reserve() function allows you to allocate a buffer in memory for manipulating strings.

   data.reserve(50);  // reserve 50 bytes in memory to save for string manipulation 
    //boolean stringOK = false;
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
}

void loop()
{
  // if arduino receive a string termination character like \n stringComplete will set to true
  //serialEvent();
  
  if (stringComplete) 
   {
      Serial.println(data);
      delay(100);
      
        if(password.compareTo(data) == 0)
    {
              // if password matched and command is 'OPEN' than door should open

               openDoor(); // call openDoor() function
              Serial.println(" OPEN"); // sent open feedback to phone
              delay(100);
            }
        else if(data.compareTo("0\n") == 0)
          {
              // if password matched and command is 'CLOSE' than door should close

              closeDoor();
              Serial.println(" CLOSE"); // sent " CLOSE" string to the phone 
              delay(100);
            }
        else if(password.compareTo(data))
            {
              // if password not matched than sent wrong feedback to phone
              Serial.println(" WRONG");
              delay(100);
            } 

             data= "";
       stringComplete = false;
        } 
       // clear the string for next iteration
     
}


void serialEvent() 
{
  while (Serial.available()) 
  {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    //Serial.write(inChar);
    // add it to the inputString:
    data += inChar;
    // if the incoming character is a newline or a carriage return, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
 
}

void openDoor(){
  myservo.write(0); //place servo knob at 0 degree
  delay(100);   
}

void closeDoor(){
  myservo.write(90); //place servo knob at 65 degree to fully closed the lock
  delay(100); 
}
