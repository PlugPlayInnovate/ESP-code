#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define DHTPIN 2
DHT dht(DHTPIN, DHT11);
 
void setup() {
 
//  Serial.begin(115200);                                  //Serial connection
  delay(10);
  dht.begin();
  WiFi.begin("Its not for you babes", "ongc1234");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
//    Serial.print(".");
// 
  }
//  Serial.println("WiFi connected");
//  Serial.print("IP:");
//  Serial.println(WiFi.localIp());
 
}
 
void loop() {
  float temperature = dht.readTemperature();
//  Serial.println(String(temperature));
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://192.168.1.100/temp");      //Specify request destination
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
   int httpCode = http.POST(String(temperature));   //Send the request
   String payload = http.getString();                  //Get the response payload
 
//   Serial.println(httpCode);   //Print HTTP return code
//   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
//    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(500);  //Send a request every 30 seconds
 
}
