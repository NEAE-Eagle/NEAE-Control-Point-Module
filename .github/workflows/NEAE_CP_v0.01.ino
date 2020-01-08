//NEAE Control Point Software v0.01
//For use with ArduinoUno3

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>


//Menu Variables
int counter = 0;
int screen=0;
int Ready=1;
int menuWake = 0; //Used for screen timeout.  When 0, display Main Screen, Input from RotEncoder, set to 1, start 10000 timer, at expiration, set to 0


//Game Variables
int gameIncrSet = 0;
int gamePointSet = 0;
int teamToggle = 0;


//Define Pins
#define push 5 //Rotary Encoder Push Button
#define yellowLED 11
#define greenLED 10
#define grnToggle 12
#define tanToggle 13

/*  BASIC NOTES
 * teamToggle: Tan = 1; Green = 2
 * Use tanScore and grnScore for respective scores 
 * Screens:
 *  Screen==0 Main Screen
 *  Screen==1 Enter PIN Screen (When menuWake==1, set screen to 1)
 *  Screen==2 Menu Page
 *  
 * Menus:
 *  
 */


// LCD Address
LiquidCrystal_I2C lcd(0x27, 16, 2)

void setup() {
  // put your setup code here, to run once:
  lcd.begin

  // backlight on
  lcd.backlight
}

void loop() {

  if((last_counter > counter) || (last_counter < counter)  || pushed) //Only print on the LCD when a step is detected or the button is pushed.
  {
    Ready=1; //NOTE may need to change

    //Main Screen, No Team Selected
    if(screen == 0 && TeamToggle == 0)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("No Team Selected")
    }

    //Main Screen, Tan Team
    if(screen == 0 && TeamToggle == 1)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Team Tan")
      lcd.setCursor(0,1);
      lcd.print("Score")
      lcd.setCursor(7,1)
      lcd.print(tanScore) //Placeholder  - Get Integer for tanScore
    }
    
    //Main Screen, Green Team
    if(screen == 0 && TeamToggle == 2)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Team Green")
      lcd.setCursor(0,1);
      lcd.print("Score")
      lcd.setCursor(7,1)
      lcd.print(grnScore) //Placeholder  - Get Integer for grnScore
    }
    
    }

  //Tan Scoring and LED activation
  if(digitalRead(tanToggle) == HIGH)
    {
      digitalWrite(yellowLED,HIGH)
      teamToggle=1 //Toggle 1 for Tan
    }else
    {
    digitalWrite(yellowLED,LOW)
    }

  //Green Scoring and LED activation
  if(digitalRead(grnToggle) == HIGH)
    {
      digitalWrite(greenLED,HIGH)
      teamToggle=2
    }else
    {
      digitalWrite(greenLED,LOW)
    }

}
