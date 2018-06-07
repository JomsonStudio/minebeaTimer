#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x3F, 20, 4);

long int time = (100);
int blue = 32;
int green = 33;
int red = 34;
int relay1 = 30;
int relay2 = 31;


//Define time Channel
float ch1 = 0;
float ch2 = 0;
float ch3 = 0;
float ch4 = 0;

//Define Channel Timmer stage
bool chStage1 = false;
bool chStage2 = false;
bool chStage3 = false;
bool chStage4 = false;

//Define Stage
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
int buttonState5 = 0;
String TimeFormat(long int value)
{
  int sec = value % 60;
  int min = (value / 60) % 60;
  int hour = value / 3600;
  return String(hour) + ":" + String(min) + ":" + String(sec);
}
// lcd.print(TimeFormat(sec));
const byte ROWS = 4; //four rows for keypad
const byte COLS = 4; //four columns for keypad
int Buzzer = 37; //Active LOW
char customKey;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {29, 28, 27, 26};//connect to the row pinouts of the keypad
byte colPins[COLS] = {25, 24, 23, 22};
Keypad  buttonKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin();
  // lcd.setCursor(0, 0);
  // lcd.print("Timer Control Box");
  // lcd.setCursor(0, 1);
  //lcd.print("Rev.1.0");
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Ch1:");
  lcd.setCursor(0, 1);
  lcd.print("Ch2:");
  lcd.setCursor(0, 2);
  lcd.print("Ch3:");
  lcd.setCursor(0, 3);
  lcd.print("Ch4:");
}

void loop() {
  customKey =  buttonKeypad.getKey(); //read form keypad
  printTime();
  buttonState1 = (customKey == '1');
  buttonState2 = (customKey == '2');
  buttonState3 = (customKey == '3');
  buttonState4 = (customKey == '4');
  buttonState5 = (customKey == 'A');
  btnCheck();
  CheckTimmer();
  //Delay 1 sec
  delay(100);
}
void printTime() {
  int temp = ch1;
  lcd.setCursor(4, 0);
  lcd.print(TimeFormat(temp));
  int temp2 = ch2;
  lcd.setCursor(4, 1);
  lcd.print(TimeFormat(temp2));
  int temp3 = ch3;
  lcd.setCursor(4, 2);
  lcd.print(TimeFormat(temp3));
  int temp4 = ch4;
  lcd.setCursor(4, 3);
  lcd.print(TimeFormat(temp4));
}
void clearPrintValue() {

  lcd.setCursor(4, 0);
  lcd.print("   ");
  lcd.setCursor(4, 1);
  lcd.print("   ");
  lcd.setCursor(4, 2);
  lcd.print("   ");
  lcd.setCursor(4, 3);
  lcd.print("   ");
}
void btnCheck() {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1) {
    chStage1 = true;
  } else if (buttonState2) {
    chStage2 = true;
  } else if (buttonState3) {
    chStage3 = true;
  } else if (buttonState4) {
    chStage4 = true;
  }
  else if (buttonState5) {
    StopandReset();
  } else {
    //Notthing
  }
}
void CheckTimmer() {
  int temp1 = ch1;
  int temp2 = ch2;
  int temp3 = ch3;
  int temp4 = ch4;
  if (temp1 == time) {
    chStage1 = false;
    ch1 = 0;
    lcd.setCursor(4, 0);
    lcd.print("*  ");
    digitalWrite(relay1, HIGH);
    delay(2000);
    digitalWrite(relay1, LOW);
  }
  if (temp2 == time) {
    chStage2 = false;
    ch2 = 0;
    lcd.setCursor(4, 1);
    lcd.print("*  ");
    digitalWrite(relay2, HIGH);
    delay(1000);
    digitalWrite(relay2, LOW);
  }
  if (temp3 == time) {
    chStage3 = false;
    ch3 = 0;
    lcd.setCursor(4, 2);
    lcd.print("*  ");
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(red, LOW);
  }
  if (temp4 == time) {
    chStage4 = false;
    ch4 = 0;
    lcd.setCursor(4, 3);
    lcd.print("*  ");
    digitalWrite(blue, HIGH);
    delay(1000);
    digitalWrite(blue, LOW);
  }
  if (chStage1) {
    ch1 = ch1 + 0.1;
  }
  if (chStage2) {
    ch2 = ch2 + 0.1;
  }
  if (chStage3) {
    ch3 = ch3 + 0.1;
  }
  if (chStage4) {
    ch4 = ch4 + 0.1;
  }

}
void StopandReset()
{
  //Define time Channel
  ch1 = 0;
  ch2 = 0;
  ch3 = 0;
  ch4 = 0;

  //Define Channel Timmer stage
  chStage1 = false;
  chStage2 = false;
  chStage3 = false;
  chStage4 = false;
  clearPrintValue();
}
