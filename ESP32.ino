void setup() {
  Serial.begin(115200);
}

#include "DHTesp.h"
const int DHT = 15;
DHTesp dhtSensor;
void PrintTemp(){
  pinMode(5, OUTPUT);
  dhtSensor.setup(DHT, DHTesp::DHT22);
  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "%C");
  Serial.println("Humnidity: " + String(data.humidity, 1) + "%");
  Serial.println("----");
}


//add breadboard
//{"type": "wokwi-breadboard__alpha", "id": "bb1", "top": 0, "left": 0, "attrs": {} }

#include <DHTesp.h>
#include <WiFi.h>
#include "PubSubClient.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "test.mosquitto.org";
int port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void wifiConnect(){
  Serial.print("Wifi conection")
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}

void mqttReconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    if (client.connect("20127333")){
      Serial.println(" connected");
      client.subscribe("20127333/led");
    }
    else{
      Serial.println(" try again in 0.5 seconds");
      delay(500);
    }
  }
}

void callback(char* topic, byte* message, unsigned int length){
  Serial.print(topic);
  Serial.print(". Message: ");
  String stMessage = "";

  for (int i=0; i<length; i++){
    stMessage += (char)message[i];
  }
  Serial.println(stMessage);
}

void setup() {
  Serial.begin(9600);
  wifiConnect();
  client.setServer(mqttServer, port);
  client.setCallback(callback);
}

void loop() {
  if(!client.connected()){
    mqttReconnect();
  }
  client.loop();

  char buffer[50];
  sprintf(buffer, "{\"Temper\": %d, \"Humidity\": %d}", 50, 20);
  client.publish("20127333/temp", buffer);
  delay(5000);
}
