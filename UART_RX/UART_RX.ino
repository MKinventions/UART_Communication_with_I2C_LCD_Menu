
#include <ArduinoJson.h>
#include <EEPROM.h>


int led1 = 23;
int led2 = 13;

int led1_address = 2;
int led2_address = 3;
int led1_value;
int led2_value;

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void setup() {
  // Initialize serial port
  Serial.begin(9600);
  EEPROM.begin(255);
  while (!Serial) continue;

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  led1_value = EEPROM.read(led1_address);//EEPROM.read(ADDRESS 0-255);
  led2_value = EEPROM.read(led2_address);//EEPROM.read(ADDRESS 0-255);
  Serial.println("Device restarted");
  Serial.println("Reading memory");
  Serial.print("LED1 value:"); Serial.println(led1_value);
  Serial.print("LED2 value:"); Serial.println(led2_value);

}

void loop() {

  analogWrite(led1, led1_value);
  digitalWrite(led2, led2_value);


  if(Serial.available() > 0){
      StaticJsonDocument<200> doc; 
      String json = Serial.readString();
      deserializeJson(doc, json);
    
    //Serial.print("received data: ");
    //Serial.println(json);
      int btn1 = doc["btn1"];
      int btn2 = doc["btn2"];
      Serial.print("BTN1:");Serial.print(btn1);
      Serial.print(" , BTN2:");Serial.println(btn2);  
      
      EEPROM.write(led1_address, btn1);
      EEPROM.write(led2_address, btn2);
      EEPROM.commit();      
      delay(1000);
     resetFunc();  //call reset 

}


}
