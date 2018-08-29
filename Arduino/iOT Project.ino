#include <MakestroCloudClient32.h>
#include "WiFi.h"

#define use_ESPectro32 1

#if use_ESPectro32
   #include <ESPectro32_Board.h>
#endif

 //initialize the mqttClient library
WiFiClient wifiConnection;

const int ledPin = 15;
const int sendPeriod = 1000;
unsigned long oldTime = 0;

const char* SSID = ".";
const char* Password = "ezydev123";
const char* username = "moryku";
const char* subsTopic = "moryku/Android";

//initialize the mqtt library
PubSubClient mqttClient(wifiConnection);

//mqtt settings
const char* mqttHost = "192.168.43.213";
const int mqttPort = 1883;

MakestroCloudClient32 makestro;


 void callback(char *topic, byte *payload, unsigned int length) {
    Serial.println("Masuk Pak Eko");
    char message_buff[3];
    int i = 0;

    //for loop that loops through the playload array
    for(i = 0; i < length; i++) {
      message_buff[i] = payload[i];
    }

    //\0 is null, this makes it that the String typecast understands where to stop
    message_buff[i] = *"\0";

    Serial.println(String(message_buff));
  }
     

void setup(){
    Serial.begin(115200);
    
    #if use_ESPectro32
        ESPectro32.begin();
    #endif
    
    delay(100);
    
    pinMode(ledPin, OUTPUT);
    
    WiFi.begin(SSID, Password);
   
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(3000);   


     //connect to the wifiConnection with mqtt
     mqttClient.setServer(mqttHost, mqttPort);
     mqttClient.subscribe(subsTopic);
     //set the callback when the programme recieves a callback
     mqttClient.setCallback(callback);
    
        while (!mqttClient.connected()) {
          Serial.print("Attempting MQTT connection...");
          if (mqttClient.connect("device1")) {
            Serial.println("connected");
          } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in one second");
            // Wait a second before retrying
            delay(1000);
          }
        }
}

void loop(){

    mqttClient.loop();
    if(millis() - oldTime > sendPeriod){
        oldTime = millis();
        int phototr = ESPectro32.readPhotoTransistorValue();
        Serial.print("phototr: ");
        Serial.println(phototr);
        
        String myString = String(phototr);

        char str[5];
        sprintf(str, "%d", phototr);
        
        mqttClient.publish("messageAndroid", str);
        Serial.println("publish to cloud");
    }
}
