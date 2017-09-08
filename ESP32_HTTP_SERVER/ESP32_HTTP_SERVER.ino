#include <WiFiClient.h>
#include <ESP32WebServer.h>
#include <WiFi.h>

/* thay doi ssid va password */
const char* ssid = "Its not for you babes";
const char* password = "ongc1234";
String DHT_Temperature = "";

ESP32WebServer server(80);

/* day la phan code giao dien, dung jquery va boostrap */
char res[1200] =
"<!DOCTYPE html>\n\
<html>\n\
<head>\n\
<meta name='viewport' content='width=device-width, initial-scale=1'>\n\
<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>\n\
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>\n\
<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>\n\
<script src='https://ajax.googleapis.com/ajax/libs/angularjs/1.6.6/angular.min.js'></script>\n\
<script>var app=angular.module('starter',[]);\n\
app.controller('myctrl',function($scope,$interval,$http){\n\
$scope.count=0;\n\
$scope.temperature='0';;\n\
var fun = function(){\n\
       $scope.count=$scope.count+1;\n\
$http.get('http://192.168.1.100/temp1').then(function(data){\n\
console.log(data);\n\
$scope.temperature=data.data;\n\
})\n\
    };\n\
    fun();\n\
    $interval(fun, 500);\n\
})\n\
</script>\n\
</head>\n\
<body>\n\
<div ng-app='starter' ng-controller='myctrl'>\n\
<table>\n\
<tr>\n\
<td>\n\
<h2>Temperature : </h2>\n\
</td>\n\
<td>\n\
<h2>{{temperature}}</h2>\n\
</td>\n\
</tr>\n\
</table>\n\
</div>\n\
</body>\n\
</html>";

void handleRoot() {
    server.send(200, "text/html", res);
}

void handleRoot_temp(){
  
//  Serial.println("Incoming text on temp");
  if(server.args()>0){
    String temp_input = server.argName(0);
    server.send(200, "text/plain", "OK");
    //Serial.println(temp_input);
    String param = server.arg(0);
//    Serial.println(param);
    DHT_Temperature = param;
    
  }
}
void handleRoot_temp1(){
 server.send(200,"text/html",DHT_Temperature);
}
/* ham nay de xu lu yeu cau cua nguoi dung
req?out=0o1 -> user request GPIO0 output gia tri HIGH 
req?in=0i -> user request GPIO0 input */
//void handleGPIO() {
//  Serial.println("got request");
//  if(server.args() > 0){
//    String req = server.argName(0);
//    if(req == "out"){
//      server.send(200, "text/plain", "OK");
//      /* parse req */
//      String param = server.arg(0);
//      int p = param.indexOf('o');
//      int pin = param.substring(0,p).toInt();
//      int value = param.substring(p+1).toInt();
//      /* cai dat pin va ghi gia tri */
//      pinMode(pin, OUTPUT);
//      digitalWrite(pin, value);
//    }else if(req == "in"){
//      String param = server.arg(0);
//      /* parse req */
//      int p = param.indexOf('i');
//      int pin = param.substring(0,p).toInt();
//      /* cai dat pin va doc input */
//      pinMode(pin, INPUT);
//      int value = digitalRead(pin);
//      char str[3] = {0,0,0};
//      sprintf(str, "%d", value);
//      /* respond cho nguoi dung */
//      server.send(200, "text/plain", str);
//    }
//  }
//}
/* cannot handle request so return 404 */
void handleNotFound(){
  String message = "File Not Found\n\n\n\n";
  server.send(404, "text/plain", message);
}

void setup(void){
//  Serial.begin(115200);
  WiFi.begin(ssid, password);
//  Serial.println("");

  /*cho wifi ket not */
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("");
//  Serial.print("Connected to ");
//  Serial.println(ssid);
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());

  /* nhung ham nay se duoc goi khi co user request va respond */
  server.on("/", handleRoot);
  /* this callback handle GPIO request and respond*/
//  server.on("/req", handleGPIO);
  server.on("/temp",handleRoot_temp);
  server.on("/temp1",handleRoot_temp1);

  server.onNotFound(handleNotFound);
  server.begin();

//  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
