/***********************************************************
  File name: WetTheCatv1.0.ino
  Description: The Relay will be turned on when the motion has been detected.
  v2.0 The Relay will be turned on when the cats weight has been detected
  v3.0 Added Zero on Positive Value two pounds less than low weight
  v4.0 Changed Weight Sensors added ADC
  Author: SPH
  Date: 2018/06/22
***********************************************************/

signed int Weight;                // Final weight Value with offset
signed int rawWeight;             // Value from ADC with mutiplier
signed int weightoffset = 0;      // Offset to bring pounds to zero
unsigned int SprayCount = 0;      // Spray Counter to apply zero function if greater than SprayReset
const int SprayReset = 3;         // Spray Counter to apply zero function if reached
unsigned int TotalCount = 0;      // Total Spray Counter

const float kFactor = -0.0002;    // Multiplier to bring reading to pounds
const int poszero = 3;            // Positive weight value to apply zero function
const int negzero = -1;           // Negative weight value to apply zero function
const int lowweight = 5;          // Weight value to trigger event
const int highweight = 95;        // Weight value to not trigger event
const int triggercounter = 3;     // Spray counter to delay spray event
const int spraytime = 200;        // Spray on time
unsigned int counter = 0;         // Spray delay counter
unsigned int zerocounter = 0;     // zero delay counter
const int zerocount = 3;          // zero delay count value to apply zero function

// include the library code for HX711 Analog to Digital Convertor:
#include <HX711.h>
HX711 scale;
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

// include the library code for Liquid Cystal Display:
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
const int RelayPin = 6;           // Relay Wired to digital pin 6

void setup() // put your setup code here, to run once:
{
//  Serial.begin(57600);  // Start Serial Stream
  
  // Initialize library with data output pin, clock input pin 
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  
  
  // Initialize library set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode( RelayPin, OUTPUT);                     // Initialize Relay pin 6 as output
  digitalWrite(RelayPin, HIGH);                   // High Turns off pump
  pinMode (LED_BUILTIN, OUTPUT);                  // Initialize digital pin LED_BUILTIN as an output
  rawWeight = (scale.read_average(20)* kFactor);  // Read average of 20 readings from the ADC
  weightoffset = (rawWeight);                     // Set weight offset value
}

void loop()
// put your main code here, to run repeatedly:
{
  digitalWrite (LED_BUILTIN, LOW);                   // turn the LED off
  rawWeight = (scale.read_average(2) * kFactor);     // Read average of 5 readings from the ADC
  Weight = ((rawWeight - weightoffset));             // Calculate final weight Value with mutiplier and offset

//  Serial.println(rawWeight);                       // print a raw reading from the ADC
//  Serial.println(Weight);                          // print calculated final weight value

if (counter >= triggercounter)    // Check for counter to turn on sprayer
{
  digitalWrite(RelayPin, LOW);    // Turns on spray relay
  lcd.clear();                    // Clears the LCD screen and positions the cursor in the upper-left corner
  lcd.setCursor(0, 0);
  lcd.print("Wet_Kitty");
  counter = 0;                     // Reset counter to zero
  SprayCount = (SprayCount + 1);   // Increment spary counter
  TotalCount = (TotalCount + 1);   // Increment total spary counter
  delay(spraytime);                // wait to turn off relay
  digitalWrite(RelayPin, HIGH);    // Turn Off Relay
  delay(10);                        // Delay loop to check for weight again
}
else if (Weight >= lowweight && Weight <= highweight)  // Cat on board start counting
{
  digitalWrite (LED_BUILTIN, LOW);  // turn the LED off
  lcd.clear();                      // Clears the LCD screen
  lcd.setCursor(0, 0);              // Positions the cursor in the upper-left corner
  lcd.print("Hi_Kitty");
  counter = (counter + 1);          // increament counter to turn on sprayer
  lcd.setCursor(0, 1);
  lcd.print(counter);
  lcd.print(" Count to ");
  lcd.print(triggercounter);        // print trigger counter value to LCD
  delay(10);                        // Delay loop to check for weight again
} 
else // Else statement to print live values to LCD
{
  digitalWrite (LED_BUILTIN, HIGH);  // Turn the LED ON
  digitalWrite(RelayPin, HIGH);      // High Turns off pump
  lcd.clear();                       // Clears the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("HereKitty:");
  lcd.print(lowweight);
  lcd.print("/");
  lcd.print(highweight);
  lcd.setCursor(0, 1);        // set the cursor to column 0, line 1 // (note: line 1 is the second row, since counting begins with 0)
  lcd.print("Lbs:");          // Print message of "Lbs: "to the LCD.
  lcd.println(Weight);        // Print weight value to the LCD.
  lcd.print(" / ");           // Print message of " / "to the LCD.
  lcd.print(TotalCount);      // Print spary counter value to the LCD
  counter = (0);
  SprayCount = (0);           // Zero Spray Counter
//  delay(10);
}
// Function to zero out drift in weight value
if (Weight <= negzero or Weight >= poszero && Weight < lowweight)
{
  zerocounter = (zerocounter + 1);
  delay(10);
}
else
{
  zerocounter = (0);
}
if (zerocounter >= zerocount)
{  
  rawWeight = (scale.read_average(20)* kFactor);
  weightoffset = (rawWeight);     // Zero weight value
}
//Needed for when dog drops bone on weight board
if (SprayCount >= SprayReset)                        //Zero weight value on spary reset 
{
  rawWeight = (scale.read_average(20) * kFactor);
  weightoffset = (rawWeight);                        // Zero weight value
  SprayCount = (0);                                  // Zero Spray Counter
}
}
