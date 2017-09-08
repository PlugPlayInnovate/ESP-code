#include <WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "QtPi_Folks";
const char* password =  "Qtpi@314!";
const char* mqttServer = "192.168.1.28";
const int mqttPort = 1883;
//const char* mqttUser = "yourMQTTuser";
//const char* mqttPassword = "yourMQTTpassword";
 
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
 
//  Serial.print("Message arrived in topic: ");
//  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
//  Serial.println("-----------------------");
}
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
 
//  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
//    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP32Client")) {
 
//      Serial.println("connected");
 
    } else {
 
//      Serial.print("failed with state ");
//      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  client.subscribe("dht/temperature",1);
 
}

void loop() {
  client.loop();
}
