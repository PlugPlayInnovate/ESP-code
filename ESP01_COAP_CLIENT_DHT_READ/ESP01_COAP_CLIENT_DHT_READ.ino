/*
ESP-COAP Client to read temperature data from DHT data on ESP32 COAP server
*/
#include <ESP8266WiFi.h>
#include "coap_client.h"

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
    char p[packet.payloadlen + 1];
    memcpy(p, packet.payload, packet.payloadlen);
    p[packet.payloadlen] = NULL;
    int pos;
    char et = 230;
    byte b[packet.payloadlen + 1];
    for(int i=0;i<packet.payloadlen+1;i++){
      b[i] = (byte)p[i];
      if(b[i]==et || b[i]==229){ // check why specific characters are present
        pos=i;
        break;
      }
    }

    char temp[pos];
    for(int i=0;i<pos;i++){
      temp[i]=p[i];
    }
    temp[pos]='\0';
    Serial.println(temp);

}

void setup() {
   
    Serial.begin(115200);

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

void loop() {
    bool state;
    if(WiFi.status() == WL_CONNECTED){
      state = coap.loop();
      int msgid = coap.get(ip,port,"dht/read");
    }
    delay(500);
}
