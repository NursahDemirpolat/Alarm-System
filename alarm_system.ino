#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>

int buzzerPin = 4;
int PirSenPin = 5; 
int pirValue; 
int ValuePirSenPin = 0;
int RLed= 2;
int GLed = 3;
String pass = "1234";
String mypass = "";
int c = -1;

const byte ROWS = 4; //rows
const byte COLS = 3; //columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {12,11,10,9 }; //Row
byte colPins[COLS] = {8,7,6}; //Column

LiquidCrystal_I2C lcd(0x27,16,2);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(buzzerPin, OUTPUT);
  pinMode(PirSenPin, INPUT);
  pinMode(RLed, OUTPUT);
  pinMode(GLed, OUTPUT);
}

void loop(){
  ValuePirSenPin = digitalRead(PirSenPin);
  Serial.println(ValuePirSenPin);
  digitalWrite(buzzerPin,LOW);
  if (ValuePirSenPin == HIGH) {
      digitalWrite(buzzerPin,HIGH);
      digitalWrite(RLed, HIGH);
      digitalWrite(GLed, LOW);
      lcd.setCursor(0,0);
      lcd.print("Detected motion!");
      char key = keypad.getKey();
      if (key){
        Serial.println(key);
        c = c + 1; 
        lcd.setCursor(c, 1);
        lcd.print("*");
      }
      if (key == '1'){
        mypass = mypass + 1;   
      }
      if (key == '2'){
        mypass = mypass + 2;  
      }
      if (key == '3'){
        mypass = mypass + 3; 
      }
       if (key == '4'){
        mypass = mypass + 4;  
      }
      if (key == '5'){
        mypass = mypass + 5;
      }
       if (key == '6'){ 
        mypass = mypass + 6; 
      }
       if (key == '7'){
        mypass = mypass + 7; 
      }
       if (key == '8'){
        mypass = mypass + 8; 
      }
      if (key == '9'){
        mypass = mypass + 9;
      }            
      if (key == '0'){
        mypass = mypass + 0; 
      }
      if (key == '*')
        {
          Serial.println(mypass); 
          if (pass == mypass){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Pass True Locked");
              delay(3000);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Locked");
              digitalWrite(RLed, LOW);
              digitalWrite(GLed, HIGH);
              digitalWrite(buzzerPin,LOW);
              delay(3000);
              ValuePirSenPin = LOW;
              digitalWrite(PirSenPin,LOW);
              mypass = "";
            }
            else
            {
              lcd.clear(); 
              lcd.setCursor(0,0); 
              lcd.print("Not locked");
              delay(1000);
              lcd.clear(); 
              lcd.println("Enter password: ");
              ValuePirSenPin = 1;
            }
        }
     digitalWrite(PirSenPin,LOW);
     digitalWrite(PirSenPin,LOW);
  }
  else{
     digitalWrite(RLed, LOW);
     digitalWrite(GLed, HIGH);
     delay(1000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Locked");
     digitalWrite(buzzerPin,LOW);
     delay(1000);
     c=-1;
   }
}
