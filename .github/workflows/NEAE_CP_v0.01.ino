//NEAE Control Point Software v0.01

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RotaryEncoder.h>


//Menu Variables
int counter = 0;
int screen=0; //start 10000 timer; Input from RotEncoder, reset timer; at expiration, set screen = 0
int menu=0;
int Ready=1;
int menuWake = 0; 
int pushed = 0;

//Game Variables
int gameIncrSet = 0; //time increments
int gamePointSet = 0; //points
int teamToggle = 0;
int tanScore = 0;
int grnScore = 0;
int pinStatus = 0;
int pinChange = 0; //SETUP PIN SYSTEM


//Define Pins
#define push 5 //Rotary Encoder Push Button
#define yellowLED 11
#define greenLED 10
#define grnToggle 12
#define tanToggle 13

/*BASIC NOTES
 * teamToggle: Tan = 1; Green = 2
 * Use tanScore and grnScore for respective scores 
 * Screens:
 *  screen==0 Main Screen
 *  screen==1 Enter PIN Screen (When menuWake==1, set screen to 1)
 *  screen==2 Menu Page
 *    menu==0 Reset
 *    menu==1 Time
 *    menu==2 Points
 *    menu==3 Change PIN
 *  screen==3 (Time Options)
 *    menu==0 1 min
 *    menu==1 10 min
 *    menu==2 30 min
 *  screen==4 (Point Options)
 *    menu==0 25
 *    menu==1 50
 *    menu==2 100
 *  screen==5 (Change PIN)
 *    menu==0 Enter new PIN
 *    menu==1 Pin Saved Screen
 *    
 *ToDo
 *  SETUP PIN SYSTEM
 *  SETUP SCORING SYSTEM
 *  SETUP MENU TIMEOUT
 *      
 *Working Notes:
 *  Counter may not work the way it is set up to return to a previously selected menu item (is defaulted to 1)
 */


// LCD Address
LiquidCrystal_I2C lcd(0x27, 16, 2)

void setup() {

  //Startup LCD
  lcd.begin

  // backlight on, home LCD
  lcd.backlight
  lcd.home

  //Print the home screen, set toggle to neutral
  teamToggle=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("No Team Selected")
  
  //Setup LED pins
  pinMode(yellowLED, OUTPUT)
  pinMode(greenLED, OUTPUT)
  
}//end void setup

void loop() {

  if(screen == 0)//Main Screen Bundle
  {
    Ready=1; //NOTE may need to change

    //Main Screen, No Team Selected
    if(teamToggle == 0)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("No Team Selected")
    }

    //Main Screen, Tan Team
    if(TeamToggle == 1)
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
    if(TeamToggle == 2)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Team Green")
      lcd.setCursor(0,1);
      lcd.print("Score")
      lcd.setCursor(7,1)
      lcd.print(grnScore) //Placeholder  - Get Integer for grnScore
    }
    
    }//end main screen bundle

  //Enter PIN Screen from Main Screen
  if((screen == 0) && (last_counter > counter) || (last_counter < counter)  || pushed) && (pinStatus == 0)//verify functionality of "pushed"
    {
      screen=1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter PIN")
      lcd.setCursor(0,1);
      lcd.print();//SETUP PIN SYSTEM
      lcd.print();
    
    
    //After successful PIN entry
      pinStatus=1;
      screen=2;
      pushed=0;
    
    }//Enter Pin Screen




  //Enter main menu on successful pin
  if(pinStatus == 1 && screen == 2)
    {
      
      //Menu Page 1
      if(0 <= counter && counter < 5)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Menu");
          lcd.setCursor(0,1);
          lcd.print("> Reset");
          menu=0;
        }

       //Menu Page 2
       if(5 <= counter && counter < 10)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Menu");
          lcd.setCursor(0,1);
          lcd.print("> Time");
          menu=1;
        }

        //Menu Page 3
       if(10 <= counter && counter < 15)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Menu");
          lcd.setCursor(0,1);
          lcd.print("> Points");
          menu=2;
        }

        //Menu Page 4
       if(15 <= counter && counter < 20)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Menu");
          lcd.setCursor(0,1);
          lcd.print("> Change PIN");
          menu=3;
        }
    }//end main menu

    //Time Menu
    if(pinStatus == 1 && screen == 3)
    {
      
      //Time Page 1
      if(0 <= counter && counter < 5)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Time");
          lcd.setCursor(0,1);
          lcd.print("> 1 Min");
          menu=0;
        }

       //Time Page 2
       if(5 <= counter && counter < 10)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Time");
          lcd.setCursor(0,1);
          lcd.print("> 10 Min");
          menu=1;
        }

        //Time Page 3
       if(10 <= counter && counter < 15)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Time");
          lcd.setCursor(0,1);
          lcd.print("> 30 Min");
          menu=2;
        }

    }//end time menu

    //Points Menu
    if(pinStatus == 1 && screen == 4)
    {
      
      //Points Page 1
      if(0 <= counter && counter < 5)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Points");
          lcd.setCursor(0,1);
          lcd.print("> 25");
          menu=0;
        }

       //Points Page 2
       if(5 <= counter && counter < 10)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Points");
          lcd.setCursor(0,1);
          lcd.print("> 50");
          menu=1;
        }

        //Points Page 3
       if(10 <= counter && counter < 15)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Points");
          lcd.setCursor(0,1);
          lcd.print("> 100");
          menu=2;
        }

    }//end Points menu

    //Change PIN Menu
    if(pinStatus == 1 && screen == 5)
    {
      
      //Enter New PIN
      if(0 <= counter && counter < 5)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Enter New PIN");
          lcd.setCursor(0,1);
          lcd.print();//SETUP PIN SYSTEM
          menu=0;
        }

       //New PIN Confirmed
       if()//SETUP PIN SYSTEM On successful PIN Change
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("PIN Saved");
          lcd.setCursor(0,1);
          lcd.print();//SETUP PIN SYSTEM Display new PIN
          menu=1;
          delay(4000)
          pinStatus=0;
          menu=0
          menuWake=0
          screen=0;//Should take user back to main screen
        }
        
    }//end PIN Change Menu

  //Button Press Detection
  if(digitalRead(push))
    {
      if((pinStatus == 1) && (screen == 2)//Menu Page
      {
        if(menu == 0)//Reset Command
        {
           tanScore=0;//assuming using integer style points
           grnScore=0;
           pinStatus=0;
           screen=0;
           counter=1;
        }//end reset command menu

        if(menu == 1)//Enter Time menu
        {
          screen=3;
          counter=1;
          if(gameIncrSet == 0)
          {
            menu=0;
          }
          if(gameIncrSet == 1)
          {
            menu=1;
          }
          if(gameIncrSet == 2)
          {
            menu=2;
          }          
        }//end enter time menu

        if(menu == 2)//Enter Points Menu
        {
          screen=4;
          counter=1;
          if(gamePointSet == 0)
          {
            menu=0;
          }
          if(gamePointSet == 1)
          {
            menu=1;
          }
          if(gamePointSet == 2)
          {
            menu=2;
          }
        }//end enter points menu

        if(menu == 3)//Enter Change PIN menu
        {
          screen=5;
          counter=1;
        }
      }//end screen 2 buttons

      if((pinStatus == 1) && (screen == 3)//Time Menu Page
      {
        if(menu == 0)
        {
          counter=1;
          pushed=0;
          gameIncrSet=0;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Timer Set");
          lcd.setCursor(0,1);
          lcd.print("> 1 Min");
          delay(3000)
          screen=0;
          pinStatus=0;
        }
        if(menu == 1)
        {
          counter=1;
          pushed=0;
          gameIncrSet=1;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Timer Set");
          lcd.setCursor(0,1);
          lcd.print("> 10 Min");
          delay(3000)
          screen=0;
          pinStatus=0;
        }
        if(menu == 2)
        {
          counter=1;
          pushed=0;
          gameIncrSet=2;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Timer Set");
          lcd.setCursor(0,1);
          lcd.print("> 30 Min");
          delay(3000)
          screen=0;
          pinStatus=0;
        }
      }//end time menu page

      if((pinStatus == 1) && (screen == 4)//Points menu page
      {
        if(menu == 0)
        {
          counter=1;
          pushed=0;
          gameIncrSet=0;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Points Set");
          lcd.setCursor(0,1);
          lcd.print("> 25");
          delay(3000)
          screen=0;
          pinStatus=0;
        }
        if(menu == 1)
        {
          counter=1;
          pushed=0;
          gameIncrSet=1;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Points Set");
          lcd.setCursor(0,1);
          lcd.print("> 50");
          delay(3000)
          screen=0;
          pinStatus=0;
        }
        if(menu == 2)
        {
          counter=1;
          pushed=0;
          gameIncrSet=2;
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Points Set");
          lcd.setCursor(0,1);
          lcd.print("> 100");
          delay(3000)
          screen=0;
          pinStatus=0;
        }
      }//end Points menu page

    //Here is where the PIN button press system works SETUP PIN SYSTEM
      
    }//end button press detection

  //Scoring Parameters to be met

  //Tan Scoring toggle and LED activation
  if(digitalRead(tanToggle) == HIGH)
    {
      digitalWrite(yellowLED,HIGH)
      teamToggle=1 //Toggle 1 for Tan
    }else
    {
    digitalWrite(yellowLED,LOW)
    }

  //Green Scoring toggle and LED activation
  if(digitalRead(grnToggle) == HIGH)
    {
      digitalWrite(greenLED,HIGH)
      teamToggle=2
    }else
    {
      digitalWrite(greenLED,LOW)
    }
    
  //Neutral Position Toggle
  if(digitalRead(grnToggle) == LOW) && (digitalRead(tanToggle) == LOW)
    {
      teamToggle=0
    }
    
  //end scoring parameters to be met

  //begin scoring point counter
  //Tan Scoring
  if(teamToggle == 1)
  {
    if(gamePointSet == 0)
    {
      //Setup timer to add 25 points for Tan
      //Reset timer
    }
    if(gamePointSet == 1)
    {
      //Setup timer to add 50 points for Tan
      //Reset timer
    }
    if(gamePointSet == 2)
    {
      //Setup timer to add 100 points for Tan
      //Reset timer
    }
  }//end Tan Scoring

  //Green Scoring
  if(teamToggle == 2)
  {
    if(gamePointSet == 0)
    {
      //Setup timer to add 25 points for Green
      //Reset timer
    }
    if(gamePointSet == 1)
    {
      //Setup timer to add 50 points for Green
      //Reset timer
    }
    if(gamePointSet == 2)
    {
      //Setup timer to add 100 points for Green
      //Reset timer
    }
  }//end Green Scoring

  //end scoring point counter


}//end void loop
