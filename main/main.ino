//Libaries importieren

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <NewRemoteTransmitter.h>
#include "DHT.h"
#include "config/wifi.h"
#include "config/devices.h"
#include "config/template.h"

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
    server.send ( 404, "text/html", json()); //todo
  }else{
    server.send ( 200, "text/html", html_template());
  }
  delay(100);
}
//Liefert den JSON_Werte Value-String zurück
String json(){
  return "{\"temperature\":\""+String(dht.readTemperature())+"\",\"humidity\":\""+String(dht.readHumidity())+"\",\"motion\":\""+String(digitalRead(pirPin))+"\"}";
}

//Liefert das Template zurück
String html_template(){
String html="<html>";
  html+="<head><title>"+titel+"</title><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\"></head>";
    html+="<body>";
      html+="<div class=\"container\">";
      html+="<h1>"+titel+"</h1>";
      html+="<h2>"+subtitel+"</h2>";
      html+=switch_template();
      html+=temperatur();
      html+="</div>";
      html+=footer();
    html+="</body>";
  html+="</html>";
  return html;
}
//Liefert das Switch-Template zurück
String switch_template(){
  String html="<table class=\"table\" >";
    html+="<caption>Switchs</caption>";
    html+="<tr><th>name</th><th>status</th><th>on</th><th>off</th></tr>";
      for(int i=0;i<=switch_length-1;i++){
        html+=switch_button(String(i+1),switchs[i],switch_status[i]);
      }
      html+=switch_button("group","Group",3);
  html+="</table>";
  return html;
}

//Liefert einen Button zurück
String switch_button(String number, String name,int status){
  String html="<tr>";
      html+="<td>";
        html+=name;
      html+="</td>";
      html+="<td>";
        String status_picture;
        switch(status){
          case 1:
            status_picture = "glyphicon-play";
            break;
          case 0:
            status_picture = "glyphicon-pause";
            break;
          default:
            status_picture   = "glyphicon-question-sign";
        }
        html+="<i class=\"glyphicon " + status_picture + "\" aria-hidden=\"true\"></i>";
      html+="</td>";
      html+="<td>";
        html+="<a class=\"btn btn-success btn-block\" style=\"text-align:left;\" href=\"?switch="+ number + "&value=1\"><i class=\"glyphicon glyphicon-play\" aria-hidden=\"true\"></i> on</a>";
      html+="</td>";
      html+="<td>";
        html+="<a class=\"btn btn-danger btn-block\" style=\"text-align:left;\" href=\"?switch="+ number + "&value=0\"><i class=\"glyphicon glyphicon-pause\" aria-hidden=\"true\"></i> off</a>";
      html+="</td>";
    html+="</tr>";
    return html;
}

//Gibt den Seitenfooter zurück
String footer(){
  String html = "<footer>";
    html+="<div class=\"container\">";
      html +="<a href=\"?&mode=json\">JSON-Values</a> | ";
      html +="2017 developed by <a href=\"http://kevin-frantz.de\">Kevin</a> with <a href=\"https://www.arduino.cc/\">Arduino</a>,<a href=\"https://en.wikipedia.org/wiki/C%2B%2B\">C++</a> ";
    html+="</div>";
  html += "</ footer>";
  return html;
}

//Liefert die Temperatursensortabelle zurück
String temperatur(){
  String html="<table class=\"table\">";
    html+="<caption>Sensors</caption>";
    html+="<tbody>";
        html+="<tr><td>Temperature:</td><td>" + String(dht.readTemperature()) + "&deg;C </td>";
        html+="<tr><td>Humity:</td><td>" + String(dht.readHumidity()) + "% </td>";
        html+="<tr><td>Motion:</td><td>" + String(digitalRead(pirPin)) + " </td>";
    html+="</tbody>";
  html+="</table>";
  return html;
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
