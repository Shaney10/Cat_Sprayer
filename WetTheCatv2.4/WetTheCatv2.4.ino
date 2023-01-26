/***********************************************************
  File name: WetTheCatv1.0.ino
  Description: The Relay will be turned on when the motion has been detected.
  v2.0 The Relay will be turned on when the cats weight has been detected
  Author: SPH
  Date: 2018/06/22
***********************************************************/

int analogPin = 0;  // Analog pin 0 connected to Srain Gage Bending Bridgr=e Output

int WeightSensor = 0;
unsigned int Weight;              // Final weight Value with mutiplier and offset
unsigned int weightoffset = 94;   // Offset to bring pounds to zero
unsigned int SprayCount = 0;      // Spray Counter
const int SprayReset = 5;         //Spray Counter value to reset zero value

const int lowweight = 5;          // Weight value to trigger event
const int highweight = 25;        // Weight value to not trigger event
const int triggercounter = 3;     // Weight trigger counter to delay spray event
const int spraytime = 300;        // Spary on time
unsigned int counter = 0;         // Spary delay counter
unsigned int zerocount = 0;       // zero dely counter
const int RelayPin = 6;           //Set the digital 6 to RelayPin

// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
/*
   LCD RS pin to digital pin 7
   LCD Enable pin to digital pin 8
   LCD D4 pin to digital pin 9
   LCD D5 pin to digital pin 10
   LCD D6 pin to digital pin 11
   LCD D7 pin to digital pin 12
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
*/

void setup()
{
  // put your setup code here, to run once:
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode( RelayPin, OUTPUT);     //initialize the Relay pin as output 6
  pinMode (LED_BUILTIN, OUTPUT);  //initialize digital pin LED_BUILTIN as an output
  pinMode(WeightSensor, INPUT);   //Set the connection analog 0 pin to Input
}

void loop()
// put your main code here, to run repeatedly:
{
  WeightSensor  = analogRead(analogPin);
  Weight = (WeightSensor * 0.2) - weightoffset + 1000; // Add 1000 to keep value positive
  lcd.setCursor(0, 1);        // set the cursor to column 0, line 1 // (note: line 1 is the second row, since counting begins with 0)
  lcd.print("Pounds:");       // Print a message of "Pounds: "to the LCD.
  lcd.print(Weight - 1000);   // Print a weight value to the LCD.
  lcd.print("LBS / ");        // Print a message of "Pounds: "to the LCD.
  lcd.print(SprayCount);      // Print spary counter value to the LCD

//Needed for when dog drops bone on weight board
if (SprayCount >= SprayReset)                        //Zero weight value on spary reset 
{
  weightoffset = (Weight - 1000 + weightoffset);     // Zero weight value
  SprayCount = 0;                                    // Zero Spray Counter
}

//Needed for when dog drops picks up bone from weight board
//Addded delay for when dog jumps off board 
if (Weight < 1000)
{
  zerocount = (zerocount + 1);
  delay(250);
}
else // of (Weight < 1000)
{
  zerocount = (0);
}
  if (zerocount >= 10)
{  
  weightoffset = (Weight - 1000 + weightoffset);     // Zero weight value
}


if (counter >= triggercounter)    // Check for counter to turn on sprayer
{
  digitalWrite(RelayPin, LOW);    // Turns on spray relay
  lcd.clear();                    // Clears the LCD screen and positions the cursor in the upper-left corner
  lcd.setCursor(0, 0);
  lcd.print("Wet_Kitty");
  counter = 0;                     // Reset counter to zero
  SprayCount = (SprayCount + 1);   // Increment spary counter
  delay(spraytime);                // wait to turn off relay
  digitalWrite(RelayPin, HIGH);    // Turn Off Relay
}

if (Weight >= lowweight + 1000 && Weight <= highweight + 1000)  // Add 1000 to keep value positive
{
  digitalWrite (LED_BUILTIN, LOW);  // turn the LED off
  lcd.clear();                      // Clears the LCD screen and positions the cursor in the upper-left corner
  lcd.setCursor(0, 0);
  lcd.print("Hi_Kitty");
  counter = (counter + 1);          // counter to run sprayer
  lcd.setCursor(0, 1);
  lcd.print(counter);
  lcd.print(" Count to ");
  lcd.print(triggercounter);         // print trigger counter value to LCD
  delay(250);                        // Delay loop to check for weight again
} 
else // Else statement to print live values to LCD
{
  digitalWrite (LED_BUILTIN, HIGH);  //turn the LED ON
  digitalWrite(RelayPin, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Here_Kitty:");
  lcd.print(lowweight);
  lcd.print("/");
  lcd.print(highweight);
  counter = (0);
  delay(100);
}
}
