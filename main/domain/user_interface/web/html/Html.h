#include "Html.cpp"

//Liefert das Template zurück

Html::Html(String titel, String subtitel, DHT* dht,int *switch_status,String *switchs, int pirPin){
  this->titel = titel;
  this->subtitel = subtitel;
  this->dht = dht;
  this->switch_status = switch_status;
  this->switchs = switchs;
  this->pirPin = pirPin;
}

String Html::printOutput(void){
  return this->html_template();
}

//Liefert das Switch-Template zurück
String Html::switch_template(void){
  String html="<table class=\"table\" >";
    html+="<caption>Switchs</caption>";
    html+="<tr><th>name</th><th>status</th><th>on</th><th>off</th></tr>";
      for(int i=0;i<=switch_length-1;i++){
        html+=this->switch_button(String(i+1),this->switchs[i],this->switch_status[i]);
      }
      html+=this->switch_button("group","Group",3);
  html+="</table>";
  return html;
}
String Html::html_template(void){
String html="<html>";
  html+="<head><title>"+titel+"</title><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\"><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\" integrity=\"sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp\" crossorigin=\"anonymous\"></head>";
    html+="<body>";
      html+="<div class=\"container\">";
      html+="<h1>"+titel+"</h1>";
      html+="<h2>"+subtitel+"</h2>";
      html+=this->switch_template();
      html+=this->temperatur();
      html+="</div>";
      html+=this->footer();
    html+="</body>";
  html+="</html>";
  return html;
}

//Liefert einen Button zurück
String Html::switch_button(String number, String name,int status){
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
String Html::footer(void){
  String html = "<footer>";
    html+="<div class=\"container\">";
      html +="<a href=\"?&mode=json\">JSON-Values</a> | ";
      html +="2017 developed by <a href=\"http://kevin-frantz.de\">Kevin</a> with <a href=\"https://www.arduino.cc/\">Arduino</a>,<a href=\"https://en.wikipedia.org/wiki/C%2B%2B\">C++</a> ";
    html+="</div>";
  html += "</ footer>";
  return html;
}

//Liefert die Temperatursensortabelle zurück
String Html::temperatur(void){
  String html="<table class=\"table\">";
    html+="<caption>Sensors</caption>";
    html+="<tbody>";
        html+="<tr><td>Temperature:</td><td>" + String(this->dht->readTemperature()) + "&deg;C </td>";
        html+="<tr><td>Humity:</td><td>" + String(this->dht->readHumidity()) + "% </td>";
        //html+="<tr><td>Motion:</td><td>" + String(digitalRead(this->pirPin)) + " </td>";
    html+="</tbody>";
  html+="</table>";
  return html;
}
