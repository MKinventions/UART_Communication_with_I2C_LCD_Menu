#include <ArduinoJson.h>
#include<EEPROM.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display


int btn = A2;
int btn1 = 3;
int btn2 = 5;
int btn3 = 7;
int led1 = 10;
int led2 = 2;

int menu_select = 0;
int menu_select_value = 0;

int btn_count = 0;
int led1_address = 4;
int led2_address = 5;
byte btn_value;

byte led1_value;
byte led2_value;

void(* resetFunc) (void) = 0; //declare reset function @ address 0


void setup() {
//  lcd.init();
  lcd.begin();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on


  Serial.begin(9600);
  pinMode(btn, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  led1_value = EEPROM.read(led1_address);//EEPROM.read(ADDRESS 0-255);
  led2_value = EEPROM.read(led2_address);//EEPROM.read(ADDRESS 0-255);


//  Serial.println("Device restarted");
//  Serial.println("Reading memory");
//  Serial.print("LED1 :"); Serial.println(led1_value);
//  Serial.print("LED2 :"); Serial.println(led2_value);

    StaticJsonDocument<200> doc;
    String SendJSONData;  
    doc["btn1"] = led1_value;
    doc["btn2"] = led2_value;
    serializeJson(doc, SendJSONData);
    Serial.println(SendJSONData);

    
  delay(1000);
}

void loop() {
//  String led1_state = (led1_value == 10) ? "LOW" : ((led1_value == 127) ? "MEDIUM" : "HIGH");
//  String led2_state = (led2_value == 1) ? "ON" : "OFF";
  
  String led1_state = (led1_value == 10) ? "L" : ((led1_value == 127) ? "M" : "H");
  String led2_state = (led2_value == 1) ? "1" : "0";

  analogWrite(led1, led1_value);
  digitalWrite(led2, led2_value);




/**************Select menu start***************************/
  int menu_select_button = digitalRead(btn3);
  if (menu_select_button == LOW) {
    menu_select++;
    Serial.println(menu_select);
  }
  if (menu_select == 3) {
    menu_select = 1;
  }
  /************select menu end****************************/

  /*************select menu value start*******************/
  int button1 = digitalRead(btn1);
  if (button1 == LOW) {
    menu_select_value++;
    //    Serial.println(mode_select_value);
  }
  if (menu_select_value == 4) {
    menu_select_value = 1;
  }
  /*************select menu value start end***************/


  int back_button = digitalRead(btn2);
  if (back_button == LOW) {
    menu_select_value = 0;
    resetFunc();  //call reset
  }
  delay(150);


switch (menu_select) {
    case 0:
//      menu_select = 1;
      
//      lcd.setCursor(0,0);//(col, row)
//      lcd.print("L1:"); lcd.print(led1_state   );
//      lcd.setCursor(9,0);//(col, row)
//      lcd.print(",L2:"); lcd.println(led2_state);
//      lcd.setCursor(0,1);//(col, row)
//      lcd.print("Select 'MENU'"); 
     
      lcd.setCursor(0,0);//(col, row)
      lcd.print(" LED1:"); lcd.print(" L"); lcd.print(" M"); lcd.print(" H  |"); lcd.println(led1_state);
      lcd.setCursor(0,1);//(col, row)
      lcd.print(" LED2:"); lcd.print(" ON"); lcd.print(" OFF |");lcd.println(led2_state );
   


      break;

    case 1:    // your hand is on the sensor
      lcd.setCursor(0,0);//(col, row)
      lcd.print(">LED1:"); lcd.print(" L"); lcd.print(" M"); lcd.print(" H  |"); lcd.println(led1_state);
      lcd.setCursor(0,1);//(col, row)
      lcd.print(" LED2:"); lcd.print(" ON"); lcd.print(" OFF |");lcd.println(led2_state );


      switch (menu_select_value) {
        case 0:
//          Serial.println("please select value");
          break;
        case 1:
          EEPROM.update(led1_address, 10);
          lcd.setCursor(0,0);//(col, row)
          lcd.print(">LED1:"); lcd.print(">L"); lcd.print(" M"); lcd.print(" H  |"); lcd.println(led1_state);
          lcd.setCursor(0,1);//(col, row)
          lcd.print(" LED2:"); lcd.print(" ON"); lcd.print(" OFF |");lcd.println(led2_state );
          break;
        case 2:
          EEPROM.update(led1_address, 127);
          lcd.setCursor(0,0);//(col, row)
          lcd.print(">LED1:"); lcd.print(" L"); lcd.print(">M"); lcd.print(" H  |"); lcd.println(led1_state);
          lcd.setCursor(0,1);//(col, row)
          lcd.print(" LED2:"); lcd.print(" ON"); lcd.print(" OFF |");lcd.println(led2_state );
          break;
        case 3:
          EEPROM.update(led1_address, 255);
          lcd.setCursor(0,0);//(col, row)
          lcd.print(">LED1:"); lcd.print(" L"); lcd.print(" M"); lcd.print(">H  |"); lcd.println(led1_state);
          lcd.setCursor(0,1);//(col, row)
          lcd.print(" LED2:"); lcd.print(" ON"); lcd.print(" OFF |");lcd.println(led2_state );
          break;
      }
      break;


    case 2:    // your hand is on the sensor
      lcd.setCursor(0,0);//(col, row)
      lcd.print(" LED1:"); lcd.print(" L"); lcd.print(" M"); lcd.print(" H  |"); lcd.println(led1_state);
      lcd.setCursor(0,1);//(col, row)
      lcd.print(">LED2:"); lcd.print(" ON"); lcd.print(" OFF |");lcd.println(led2_state );



      switch (menu_select_value) {
        case 0:
//          Serial.println("please select value");
          break;
        case 1:
          EEPROM.update(led2_address, 1);
          lcd.setCursor(0,0);//(col, row)
          lcd.print(" LED1:");lcd.print(" L");lcd.print(" M"); lcd.print(" H  |"); lcd.println(led1_state);
          lcd.setCursor(0,1);//(col, row)
          lcd.print(">LED2:");lcd.print(">ON");lcd.print(" OFF |");lcd.println(led2_state );
          break;
        case 2:
          EEPROM.update(led2_address, 0);
          lcd.setCursor(0,0);//(col, row)
          lcd.print(" LED1:");lcd.print(" L");lcd.print(" M"); lcd.print(" H  |"); lcd.println(led1_state);
          lcd.setCursor(0,1);//(col, row)
          lcd.print(">LED2:");lcd.print(" ON");lcd.print(">OFF |");lcd.println(led2_state );
          break;
        case 3:
          menu_select_value = 1;
          break;
      }
      break;

  }
}
