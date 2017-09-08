#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap.h>

char* ssid     = "Its not for you babes";
char* password = "ongc1234";
String DHT_Temperature = "";

// CoAP client response callback
//void callback_response(CoapPacket &packet, IPAddress ip, int port);

// CoAP server endpoint url callback
void callback_dht_write(CoapPacket &packet, IPAddress ip, int port);

// UDP and CoAP class
WiFiUDP udp;
Coap coap(udp);

// CoAP server endpoint URL
void callback_dht_write(CoapPacket &packet, IPAddress ip, int port) {
 
  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  String message(p);

  DHT_Temperature = message;

  int str_len = DHT_Temperature.length();
  char char_temperature[str_len];
  for(int i=0;i<str_len;i++){
    char_temperature[i] = (char)DHT_Temperature[i];
  }

  coap.sendResponse(ip,port,packet.messageid,char_temperature);
}

void callback_dht_read(CoapPacket &packet, IPAddress ip, int port) {
  
  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  String message(p);

  int str_len = DHT_Temperature.length();

  char char_temperature[str_len];
  for(int i=0;i<str_len;i++){
    char_temperature[i] = (char)DHT_Temperature[i];
  }

  coap.sendResponse(ip,port,packet.messageid,char_temperature);
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println(WiFi.localIP());

  coap.server(callback_dht_write,"dht/write");
  coap.server(callback_dht_read,"dht/read");
  
  // start coap server/client
  coap.start();
}

void loop() {
  delay(200);
  coap.loop();
}
/*
if you change LED, req/res test with coap-client(libcoap), run following.
coap-client -m get coap://(arduino ip addr)/light
coap-client -e "1" -m put coap://(arduino ip addr)/light
coap-client -e "0" -m put coap://(arduino ip addr)/light
*/
