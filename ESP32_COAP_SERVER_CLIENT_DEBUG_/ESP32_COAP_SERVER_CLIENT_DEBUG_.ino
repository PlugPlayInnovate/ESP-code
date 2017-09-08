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

// LED STATE
bool LEDSTATE;

// CoAP server endpoint URL
void callback_dht_write(CoapPacket &packet, IPAddress ip, int port) {
  //Serial.println("DHT_Write");
  
  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  String message(p);

  DHT_Temperature = message;

//  int str_len = strlen(DHT_Temperature);
  int str_len = DHT_Temperature.length();
  //Serial.println(str_len);
//  Serial.println(str_len1);
  char char_temperature[str_len];
  for(int i=0;i<str_len;i++){
    char_temperature[i] = (char)DHT_Temperature[i];
  }
  /*byte Buffer[message.length()]; //For debugging (Converts message to bytes)
  //strcpy(Buffer,message.c_str());

  for(int i=0;i<message.length();i++){
    Buffer[i]=(byte)message[i];
    Serial.print(Buffer[i]);
  }
  Serial.println(message.length());
  //Buffer[message.length()]=NULL;*/

  //Serial.println(DHT_Temperature);
  //Serial.println(char_temperature);

  /*if (message.equals("0"))
    LEDSTATE = false;
  else if(message.equals("1"))
    LEDSTATE = true;*/
      
  /*if (LEDSTATE) {
    digitalWrite(9, HIGH) ; 
    coap.sendResponse(ip, port, packet.messageid, "1");
  } else { 
    digitalWrite(9, LOW) ; 
    coap.sendResponse(ip, port, packet.messageid, "0");
  }*/
  coap.sendResponse(ip,port,packet.messageid,char_temperature);
}

void callback_dht_read(CoapPacket &packet, IPAddress ip, int port) {
  //Serial.println("DHT_Read");
  
  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  String message(p);

  //DHT_Temperature = message;

  //int str_len = strlen(DHT_Temperature);
  int str_len = DHT_Temperature.length();
  //Serial.println(str_len);
  //Serial.println(str_len1);
  char char_temperature[str_len];
  for(int i=0;i<str_len;i++){
    char_temperature[i] = (char)DHT_Temperature[i];
  }

  //Serial.println(DHT_Temperature);
  //Serial.println(char_temperature);

  coap.sendResponse(ip,port,packet.messageid,char_temperature);
}

// CoAP client response callback
/*void callback_response(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("[Coap Response got]");
  
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = NULL;
  
  Serial.println(p);
}*/

void setup() {
  //Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());

  // LED State
//  pinMode(9, OUTPUT);
//  digitalWrite(9, HIGH);
//  LEDSTATE = true;
  
  // add server url endpoints.
  // can add multiple endpoint urls.
  // exp) coap.server(callback_switch, "switch");
  //      coap.server(callback_env, "env/temp");
  //      coap.server(callback_env, "env/humidity");
//  Serial.println("Setup Callback Light");
  coap.server(callback_dht_write,"dht/write");
  coap.server(callback_dht_read,"dht/read");
  

  // client response callback.
  // this endpoint is single callback.
  //Serial.println("Setup Response Callback");
  //coap.response(callback_response);

  // start coap server/client
  coap.start();
}

void loop() {
  //delay(10);
  coap.loop();
}
/*
if you change LED, req/res test with coap-client(libcoap), run following.
coap-client -m get coap://(arduino ip addr)/light
coap-client -e "1" -m put coap://(arduino ip addr)/light
coap-client -e "0" -m put coap://(arduino ip addr)/light
*/
