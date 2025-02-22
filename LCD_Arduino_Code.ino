// include the library code:
#include <LiquidCrystal.h>

//Define pins
int pinD0 = 11;
int pinD1 = 10;
int pinD2 = 9;
int pinD3 = 8;
/**/
int pinD4 = 4;
int pinD5 = 5;
int pinD6 = 6;
int pinD7 = 7;

int pinEnable = 11;
int pinRS = 12;
int pinRW = 13;


// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(pinRS, pinRW, pinEnable, pinD4, pinD5, pinD6, pinD7);
//LiquidCrystal lcd(pinRS, pinRW, pinEnable, pinD0, pinD1, pinD2, pinD3, pinD4, pinD5, pinD6, pinD7);

const byte numChars = 33;
boolean newData = false;
char receivedChars[numChars];
//char out1[16];
//char out2[16];
String out1,out2;


void setup() 
{
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	lcd.clear();
  lcd.print("Please wait...");

  Serial.begin(9600);
  Serial.println("Diagnostic Tool ready to receive data! Confirmation: e326a5");
}

void loop() 
{
  recvData();
  showData();
}



void recvData(){
  static byte i = 0;
  char rc;
  char endMarker = '\n';

  while(Serial.available() > 0 && !newData){
    rc = Serial.read();

    if (rc != endMarker){
      receivedChars[i] = rc;
      i++;
      if (i >= numChars) {
        i = numChars-1;
        continue;
      }
    }
    else {
      receivedChars[i] = '\0';
      i = 0;
      newData = true;
    }
  }

}

void showData(){
  if (newData == true) {
    
    //Serial.print("Length: ");
    //Serial.println(sizeof(receivedChars));

    out1 = String(receivedChars).substring(0,16);
    out2 = String(receivedChars).substring(16,32);

    Serial.print("Received Data: ");
    Serial.println(out1);
    Serial.print("Received Data: ");
    Serial.println(out2);

    //Serial.println(sizeof(out1));
    //Serial.println(sizeof(out2));

    lcd.clear();

    //lcd.setCursor(0, 0);
    //lcd.print(receivedChars);

    lcd.setCursor(0, 0);
    lcd.print(out1);
    
    lcd.setCursor(0, 1);
    lcd.print(out2);

    newData = false;
  }
}

//lcd.clear();
	// Print a message to the LCD.
	//lcd.print("Hello world!");

	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	//lcd.setCursor(0, 1);
	// Print a message to the LCD.
	//lcd.print(" LCD Tutorial");