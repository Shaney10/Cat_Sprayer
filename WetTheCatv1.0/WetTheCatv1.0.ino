/***********************************************************
File name: WetTheCatv1.0.ino
Description: The Relay will be turned on when the motion has been detected.
Author: SPH
Date: 2018/06/06
***********************************************************/

// include the library code:
#include <LiquidCrystal.h>

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
int PIRpin=13;           //Set the digital 5 to PIR
void setup() {
  // put your setup code here, to run once:
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello_Kitty");    
  pinMode( RelayPin,OUTPUT);     //initialize the  led pin as output 
  pinMode( PIRpin,INPUT);     //initialize the  PIR pin as input
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(digitalRead(PIRpin)==LOW)
  {
    digitalWrite(RelayPin,LOW);
  // set the cursor to column 0, line 0
  // (note: line 1 is the second row, since counting begins with 0):
  // print to the LCD Display:
  lcd.setCursor(0, 0);
  lcd.print("Here_Kitty");
    delay(1000); //wait to loop
  }else
  {
  // print to the LCD Display:
  lcd.setCursor(0, 0);
  lcd.print("Hi_Kitty");
    delay(2000); //wait to see if cat is still there
    if(digitalRead(PIRpin)==HIGH)
    {
  // print to the LCD Display:
  lcd.setCursor(0, 0);
  lcd.print("Wet_Kitty");
    digitalWrite(RelayPin,HIGH);
    delay(2000); //wait to loop
    }else
    delay(1000); //wait to loop
  }
}
