#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define WIFI_AP "xxxxxxx"
#define WIFI_PASSWORD "xxxxxxx"

char mqttServer[] = "xxx.xxx.xxx.xxx";
#define userName "xxxxxx"
#define passWord "xxxxxx"
// Para conectar a thingsBoard poner el TOKEN en el userName y NULL en passWord 

// PINs
int BuzzerPIN = 2;
unsigned long lastRead;

WiFiClient wifiClient;

PubSubClient client(wifiClient);

int status = WL_IDLE_STATUS;

void setup()
{
//  Serial.begin(115200);
  InitWiFi();
  client.setServer( mqttServer, 1883 );
  
  // MQTT callback
  client.setCallback(callback);

//Define el GPIO0 y GPIO2 como salida
pinMode(BuzzerPIN, OUTPUT);
digitalWrite(BuzzerPIN, HIGH);
 



//Busca el estado de los switches al momento del apagado

  lastRead = 0;
}

void loop()
{
  if ( !client.connected() ) {
    reconnect();
  }

/*
 if ( millis() - lastRead > 200 ) { // Update and send only after 1/4 de segundo
    
//Algo
    
    lastRead = millis();
  }
*/
 
  client.loop();
} 




void InitWiFi()
{
//  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }
//  Serial.println("Connected to AP");
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
 //       Serial.print(".");
      }
 //     Serial.println("Connected to AP");
    }
//    Serial.print("Connecting to mqtt broker ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("caja002", userName, passWord) ) {
//      Serial.println( "[DONE]" );
      client.subscribe("caja002/buzzer/buzzerCmd");
    } else {
//      Serial.print( "[FAILED] [ rc = " );
//      Serial.print( client.state() ); 
//      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}


//void callback(const MQTT::Publish& pub) {
void callback(char* topic, byte* payload, unsigned int length ) {

String sTopic = String(topic);
String sPayload = (String((char*)payload)).substring(0, length);

    if (sTopic == "caja002/buzzer/buzzerCmd"){
      
      playMelody(sPayload);
    }

}

 void playMelody(String meLody) {

        for (int i=0; i < meLody.toInt(); i++){   // esto lo uso solo para repetir pero aca podría venie toda la melodia
        digitalWrite(BuzzerPIN, LOW);
        delay(100);
        digitalWrite(BuzzerPIN, HIGH);
        delay(10);
        digitalWrite(BuzzerPIN, LOW);
        delay(100);
        digitalWrite(BuzzerPIN, HIGH);
        delay(10);
        digitalWrite(BuzzerPIN, LOW);
        delay(100);
        digitalWrite(BuzzerPIN, HIGH);
        delay(10);
        digitalWrite(BuzzerPIN, LOW);
        delay(100);
        digitalWrite(BuzzerPIN, HIGH);
        delay(10);
      }
 }
