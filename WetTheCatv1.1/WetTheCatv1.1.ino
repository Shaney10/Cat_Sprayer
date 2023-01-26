/***********************************************************
File name: WetTheCatv1.0.ino
Description: The Relay will be turned on when the motion has been detected.
Author: SPH
Date: 2018/06/06
***********************************************************/

// include the library code:
#include <LiquidCrystal.h>
const int echoPin = 4;  // pin connected to Echo Pin in the ultrasonic distance sensor
const int trigPin  = 5; // pin connected to trig Pin in the ultrasonic distance sensor

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
/*
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
*/
int RelayPin=6;         //Set the digital 6 to RelayPin
void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();             //Clears the LCD screen and positions the cursor in the upper-left corner 
  lcd.print("Hello_Kitty");    
   pinMode( RelayPin,OUTPUT);     //initialize the  led pin as output 
   pinMode(echoPin, INPUT); //Set the connection pin output mode Echo pin
   pinMode(trigPin, OUTPUT);//Set the connection pin output mode trog pin
  //initialize digital pin LED_BUILTIN as an output .
  pinMode (LED_BUILTIN,OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
   int cm = ping(echoPin) ;
  // set the cursor to column 0, line 0
  // (note: line 1 is the second row, since counting begins with 0):
  // print to the LCD Display:
  lcd.clear();             //Clears the LCD screen and positions the cursor in the upper-left corner 
  lcd.setCursor(0, 0);
  lcd.print("Here_Kitty");
  lcd.setCursor(0, 1);
   lcd.print("distance: ");      // Print a message of "Temp: "to the LCD.
   lcd.print(cm);                // Print a centigrade temperature to the LCD. 
   lcd.print(" cm    ");         // Print the unit of the centigrade temperature to the LCD.
  
    digitalWrite (LED_BUILTIN,LOW);   //turn the LED off 
    digitalWrite(RelayPin,HIGH);
    

    delay(1000); //wait to loop
  }
  int ping(int echoPin)
{ 
   // establish variables for duration of the ping, 
   // and the distance result in inches and centimeters: 
   long duration, cm; 
   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds. 
   // Give a short LOW pulse beforehand to ensure a clean HIGH pulse: 
   pinMode(trigPin, OUTPUT); 
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(2); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(5); 
   digitalWrite(trigPin, LOW); 

   pinMode(echoPin, INPUT); 
   duration = pulseIn(echoPin, HIGH); 

   // convert the time into a distance 
   cm = microsecondsToCentimeters(duration); 
   return cm ; 
} 

long microsecondsToCentimeters(long microseconds) 
{ 
   // The speed of sound is 340 m/s or 29 microseconds per centimeter. 
   // The ping travels out and back, so to find the distance of the 
   // object we take half of the distance travelled. 
   return microseconds / 29 / 2; 
}

