/*
* Project Name: 	Graino Garner Chamber
* Author List: 	Kajal Jha, Swati Rawat, Ankita Surendra Tembhurne
* Filename: 		nodemcu1er.ino
* Functions: 		setup(),irSensor(),loop(),
* Global Variables:	.
* 
* This file is for Node MCU 1
*/
#define BLYNK_PRINT Serial   
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
int irPin = 14;       //D5 PIN
int relayPin = 5;    // D1 PIN
int irValue;

char auth[] = ""; 
char ssid[] = "";  
char pass[] = "";  

Servo servo;

void setup()
{
  Serial.begin(115200); 
  Blynk.begin(auth, ssid, pass);
  servo.attach(15);                                                 // NodeMCU D8 pin
  pinMode(irPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void irSensor()
{
  irValue = digitalRead(irPin);
  Blynk.virtualWrite(V0, irValue);
}
  
void loop()
{  
  Blynk.run(); 
  irSensor();
  if (irValue == HIGH  )
  {
    digitalWrite(relayPin, LOW);
  }
  
  else
  digitalWrite(relayPin, HIGH);
}

BLYNK_WRITE(V2)
{
  servo.write(0);  
}

BLYNK_WRITE(V3)
{
  servo.write(90);
}
