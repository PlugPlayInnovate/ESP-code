/*
ESP-COAP Client TO SENSE DHT TEMPERATURE AND SEND DATA TO ESP32 COAP SENSOR
*/
#include <DHT.h>
#include <ESP8266WiFi.h>
#include "coap_client.h"

#define DHTPIN 2
DHT dht(DHTPIN, DHT11);

//instance for coapclient
coapClient coap;

//WiFi connection info
const char* ssid = "Its not for you babes";
const char* password = "ongc1234";


//ip address and default port of coap server in which your interested in
IPAddress ip(192,168,1,100);//take ETH Zurich or coap.me server to run and check client 
int port =5683;

// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port);

// coap client response callback
void callback_response(coapPacket &packet, IPAddress ip, int port) {
  delay(20);
}

void setup() {
   

    delay(20);
    dht.begin();

    WiFi.begin(ssid, password);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    }
    // client response callback.
    // this endpoint is single callback.
    coap.response(callback_response);

    // start coap client
    coap.start();
}
//int i=0;

void loop() {
  float temperature = dht.readTemperature();
  String str_temperature = String(temperature);
  int str_len = str_temperature.length();
  char char_temperature[str_len];
  for(int i=0;i<str_len;i++){
    char_temperature[i] = (char)str_temperature[i];
  }
  
    bool state;

    if(WiFi.status() == WL_CONNECTED){
      state = coap.loop();
      int msgid = coap.post(ip,port,"dht/write",char_temperature,str_len);
    }
    delay(500);
}
