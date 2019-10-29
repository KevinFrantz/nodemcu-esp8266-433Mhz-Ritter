//Libaries importieren
//todo: At administration scripts including cloning of DHT and Arduino sensors
// https://randomnerdtutorials.com/10-diy-wifi-rgb-led-mood-light-with-esp8266-step-by-step/
// https://community.openhab.org/t/led-strips-controlled-with-openhab2/30807
// https://bitbucket.org/fuzzillogic/433mhzforarduino/wiki/Home  think about adding it permanently
// https://randomnerdtutorials.com/decoding-and-encoding-json-with-arduino-or-esp8266/
// https://data.nasa.gov/Space-Science/Astronomy-Picture-of-the-Day-API/ez2w-t8ua
// https://flattr.com/creators/signup
// https://github.com/arduino/Arduino/blob/master/build/shared/manpage.adoc

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <NewRemoteTransmitter.h>
#include <DHT.h>
#include "domain/field_device/actuator/transmitter/rev_ritter/RevRitterRemoteControl.h"
#include "config/wifi.h"
#include "config/devices.h"
#include "config/template.h"
#include "domain/user_interface/web/html/Html.h"

//Ritter Einstellungen
const unsigned long address = 13043702;         //433Mhz

//Pinbelegung
const int tmpPin  = 12; //Temperatur
const int sendPin = 13; //433mhz
const int pirPin  = 14;  //Motion

//Allgemeine Variablen initialisieren
String income = "";
int switch_status[9];

//Klassen initialisieren
DHT dht(tmpPin, DHT11);
ESP8266WebServer server ( 80 );
NewRemoteTransmitter transmitter(address, sendPin);
Html html(titel,subtitel,&dht,switch_status,switchs,pirPin);

//Arduino-Setup
void setup(void)
{
  //Standart-Values auf ubekannt setzen
  for(int i=0;i<=switch_length-1;i++){
    switch_status[i]=3;
  }

  //Pin auf Input setzen
  pinMode(pirPin, INPUT);

  Serial.begin(115200);
  Serial.println("Gestartet");
  Serial.println("----------");
  //WiFi.softAPdisconnect(true);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }
  Serial.println("Connected to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.onNotFound(handleRequest);
  server.begin();
  Serial.println("HTTP server started");
  Serial.println("Setup fertig");
  Serial.println("");
  delay(1000);
}

//Arduino-Loop
void loop()
{
  server.handleClient();
}

void handleRequest(){
  if(server.arg("switch") && server.arg("value")){
    if(server.arg("switch")=="group"){
      gruppe(server.arg("value").toInt());
    }else{
      schalter(server.arg("switch").toInt(),server.arg("value").toInt());
    }
  }

  if(server.arg("mode")=="json"){
    server.send ( 200, "text/html", json());
  }else{
    server.send ( 200, "text/html", html.printOutput());
  }
  delay(100);
}
//Liefert den JSON_Werte Value-String zurück
String json(){
  return "{\"temperature\":\""+String(dht.readTemperature())+"\",\"humidity\":\""+String(dht.readHumidity())+"\",\"motion\":\""+String(digitalRead(pirPin))+"\"}";
}

//Schaltet einen Steckdose
void schalter(int unit, int state)
{
  transmitter.sendUnit(unit, state);
  Serial.print(state);
  Serial.print(" zu ");
  Serial.print(unit);
  Serial.println(" gesendet");
  Serial.println("----------");
  switch_status[unit-1]=state;
  delay(100);
}

//Schaltet alle Steckdosen
void gruppe(int state)
{
  transmitter.sendGroup(state);
  Serial.print(state);
  Serial.println(" zur Gruppe gesendet");
  Serial.println("----------");
  for(int i=0;i<=switch_length-1;i++){
    switch_status[i]=state;
  }
  delay(100);
}
