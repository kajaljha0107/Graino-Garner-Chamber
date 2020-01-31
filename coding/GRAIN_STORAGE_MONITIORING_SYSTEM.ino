/*
* Project Name: 	Graino Garner Chamber
* Author List: 	Kajal Jha, Swati Rawat, Ankita Surendra Tembhurne
* Filename: 		GRAIN_STORAGE_MONITIORING_SYSTEM.ino
* Functions: 		blinkLedWidget(),sendSensor(),setup(),loop()
* Global Variables:	SCREEN_WIDTH,SCREEN_HEIGHT
* 
* This file is for Node MCU 2
*/
#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Servo.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const uint8_t scl = D6;
const uint8_t sda = D7;
float h,t;
char auth[] = "hnRsRLaGBvFA17K1caipzYYxvrjtGU_J"; 
char ssid[] = "OnePlus 7";  
char pass[] = "ankita@123";  
#define DHTPIN 2                                                 // Digital pin 4
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
WidgetLED fan12(D1);
WidgetLED pump(D3);
WidgetLED hoper(D5);
WidgetLED fan34h(D2);
WidgetLED servo1(D8);
WidgetLED servo2(D8);
Servo servo;

//BlynkTimer timer;

void blinkLedWidget()  
{
if (fan12.getValue())
  {
    fan12.off();
    Serial.println("fan12 on D1: off");
  }
else 
  {
    fan12.on();
    Serial.println("fan12 on D1: on");
  }
  
  if (pump.getValue())
  {
    pump.off();
    Serial.println("pump on D3: off");
  }
else 
  {
    pump.on();
    Serial.println("pump on D3: on");
  }
  
if (hoper.getValue())
  {
    hoper.off();
    Serial.println("hoper on D5: off");
  }
else 
  {
    hoper.on();
    Serial.println("hoper on D5: on");
  }
if (fan34h.getValue())
  {
    fan34h.off();
    Serial.println("fan34h on D2: off");
  }
else 
  {
    fan34h.on();
    Serial.println("fan34h on D2: on");
  }
if (servo1.getValue())
  {
    servo1.off();
    Serial.println("servo1 on D8: off");
  }
else 
  {
    servo1.on();
    Serial.println("servo1 on D8: on");
  }
  if (servo2.getValue())
  {
    servo2.off();
    Serial.println("servo2 on D8: off");
  }
else 
  {
    servo2.on();
    Serial.println("servo2 on D8: on");
  }
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  Wire.begin(sda, scl);
  servo.attach(15);                                                 // NodeMCU D8 pin
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, blinkLedWidget);
}
void loop()
{
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);
  }
   display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("TEMP = ");
  display.print(dht.readTemperature());
  display.print(" *C");
  display.print("\n\n");
  display.print("HUMIDITY = ");
  display.print(h);
  display.display();
  Blynk.run(); 
  timer.run(); 
}
BLYNK_WRITE(V2)
{
  servo.write(0);
  
}

BLYNK_WRITE(V3)
{
  servo.write(90);
  
}
void sendSensor()
{
   h = dht.readHumidity(); 
  t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}
