/***********************************************************
  File name: WetTheCatv1.0.ino
  Description: The Relay will be turned on when the motion has been detected.
  v2.0 The Relay will be turned on when the cats weight has been detected
  v3.0 Added Zero on Positive Value two pounds less than low weight
  v4.0 Changed Weight Sensors added ADC
  Author: SPH
  Date: 2018/06/22
***********************************************************/

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

signed int Weight;                // Final weight Value with mutiplier and offset
signed int rawWeight;             // Raw weight Value from ADC
signed int weightoffset = 0;      // Offset to bring pounds to zero
unsigned int SprayCount = 0;      // Spray Counter
const int SprayReset = 3;         //Spray Counter value to reset zero value

const float kFactor = -0.001;     // Multiplier to bring reading to pounds
const int poszero = 3;            // Positive weight value to apply zero function
const int negzero = -3;            // Negative weight value to apply zero function
const int lowweight = 5;         // Weight value to trigger event
const int highweight = 105;       // Weight value to not trigger event
const int triggercounter = 2;     // Weight trigger counter to delay spray event
const int spraytime = 300;        // Spary on time
unsigned int counter = 0;         // Spary delay counter
unsigned int zerocount = 0;       // zero dely counter
const int RelayPin = 6;           //Set the digital 6 to RelayPin

// include the library code:
#include <HX711.h>
HX711 scale;
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
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode( RelayPin, OUTPUT);     //initialize the Relay pin as output 6
  pinMode (LED_BUILTIN, OUTPUT);  //initialize digital pin LED_BUILTIN as an output
  digitalWrite(RelayPin, HIGH);   //High Turns off pump
  rawWeight = (scale.read_average(20));
  weightoffset = (rawWeight);     // Zero weight value
}

void loop()
// put your main code here, to run repeatedly:
{
    rawWeight = (scale.read_average(5));
    Weight = ((rawWeight - weightoffset) * kFactor); // Add 1000 to keep value positive

//Needed for when dog drops bone on weight board
if (SprayCount >= SprayReset)                        //Zero weight value on spary reset 
{
  rawWeight = (scale.read_average(20));
  weightoffset = (rawWeight);     // Zero weight value
  SprayCount = 0;                                    // Zero Spray Counter
}
//Needed for when dog drops picks up bone from weight board
//Addded delay for when dog jumps off board
// Added "or" to zero out floating positive value
if (Weight <= negzero or Weight >= poszero && Weight < lowweight)
{
  zerocount = (zerocount + 1);
  delay(250);
}
else // of (Weight < 1000)
{
  zerocount = (0);
}
  if (zerocount >= 5)
{  
  rawWeight = (scale.read_average(20));
  weightoffset = (rawWeight);     // Zero weight value
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

if (Weight >= lowweight && Weight <= highweight)  // Add 1000 to keep value positive
{
  digitalWrite (LED_BUILTIN, LOW);  // turn the LED off
  lcd.clear();                      // Clears the LCD screen
  lcd.setCursor(0, 0);              // Positions the cursor in the upper-left corner
  lcd.print("Hi_Kitty");
  counter = (counter + 1);          // counter to run sprayer
  lcd.setCursor(0, 1);
  lcd.print(counter);
  lcd.print(" Count to ");
  lcd.print(triggercounter);         // print trigger counter value to LCD
  delay(1);                        // Delay loop to check for weight again
} 
else // Else statement to print live values to LCD
{
  digitalWrite (LED_BUILTIN, HIGH);  //turn the LED ON
  digitalWrite(RelayPin, HIGH);
  lcd.clear();                      // Clears the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("HereKitty:");
  lcd.print(lowweight);
  lcd.print("/");
  lcd.print(highweight);
  lcd.setCursor(0, 1);        // set the cursor to column 0, line 1 // (note: line 1 is the second row, since counting begins with 0)
  lcd.print("Lbs:");          // Print a message of "Pounds: "to the LCD.
  lcd.println(Weight);          // Print a weight value to the LCD.
  lcd.print(" / ");        // Print a message of "Pounds: "to the LCD.
  lcd.print(zerocount);      // Print spary counter value to the LCD

  counter = (0);
  delay(10);
}
}
