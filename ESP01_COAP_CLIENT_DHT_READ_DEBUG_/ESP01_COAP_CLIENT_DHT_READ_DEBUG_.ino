/*
ESP-COAP Client
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
    //Serial.println(et);
    byte b[packet.payloadlen + 1];

    for(int i=0;i<packet.payloadlen+1;i++){
      b[i] = (byte)p[i];
      //Serial.println(b[i]);
      if(b[i]==et){
        pos=i;
        //Serial.println(pos);
        break;
      }
//      if (p[i]==et){
//        pos = i;
//        Serial.println(i);
//        Serial.println(pos);
//        break;        
//      }
    }
    //Serial.println(pos);
    //Serial.println(p);
    char temp[pos];
    for(int i=0;i<pos;i++){
      temp[i]=p[i];
    }
    temp[pos]='\0';
    //Serial.println(p[0-(pos-1)]);
    Serial.println(temp);
    //char temp[pos-1];
    //memcpy(temp,p,pos-1);


//    char* etb;
//    etb = strchr(p,et);
//    int i =(etb-p)/sizeof(char*) -1;
//    char temp[i];
    
//    Serial.println(etb);
//    memcpy(temp,p,i);
    /*for(int i=0;i<etb-1;i++){
      Serial.print(p[i]);
    }*/
    //Serial.println(temp);
    /*While(etb!=NULL){
      etb=strchr(
    }*/
    //String temp = p.readStringUntil('ETB');
//    Serial.println(p[0-(etb-1)]);
    /*byte b[packet.payloadlen +1];
    for(int i=0;i<p.readStringUntil('ETB');i++){
      b[i] = (byte)p[i];
      Serial.print(b[i]);
    }*/
    //Serial.println();

    //response from coap server
 if(packet.type==3 && packet.code==0){
      Serial.println("ping ok");
    }

    //Serial.println(p);
//    Serial.println(b);
}

void setup() {
   
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    //Serial.println("");

    // Connection info to WiFi network
    //Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //yield();
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    // Print the IP address of client
    Serial.println(WiFi.localIP());

    // client response callback.
    // this endpoint is single callback.
    coap.response(callback_response);

    // start coap client
    coap.start();

    //get request to server (arguments ip adrress of server,default port,resource(uri))
    //int msgid = coap.get(ip,port,"dht");

    //observe request (arguments ip adrress of server,deafult port,resource name,interger(0) ) 
    //int msgid= coap.observe(ip,port,"light",0);

    //reset observe cancel
    //int msgid=coap.observecancel(ip,port,"resoucename");
    
}
//int i=0;

void loop() {
    bool state;
    if(WiFi.status() == WL_CONNECTED){
      state = coap.loop();
      int msgid = coap.get(ip,port,"dht/read");
    }
    else
      Serial.println("Error in WiFi connection");
 
 
    // Requests

    //get request
    //int msgid = coap.get(ip,port,"hello");

    //put request 
    //arguments server ip address,default port,resource name, payload,payloadlength
    //int msgid =coap.put(ip,port,"resourcename","0",strlen("0"));

    //post request
    //arguments server ip address,default port,resource name, payload,payloadlength
    //int msgid =coap.post(ip,port,"resourcename","0",strlen("0"));

    //delete request
    //int msgid = coap.delet(ip,port,"resourcename");

    //ping
    //int msgid=coap.ping(ip,port);
    
    // int msgid=coap.observe(ip,port,"obs",0);
  
    //state= coap.loop();
    // Serial.print("state=");
    //Serial.println(state);
    //if(state==true)
          //i=i+1;
  
    //Serial.print("i=");
    //Serial.println(i);
      //if(i==3)
    //{
        //Serial.println("cancel observe");
        //coap.observeCancel(ip,port,"resourcename");
    //}
  
    //Serial.println(msgid);
    delay(500);
}
