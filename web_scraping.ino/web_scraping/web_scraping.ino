#include <ESP8266WiFi.h>
#define D4 15
const char* ssid = "casa5G";
const char* password = "Dhiego2362";
int cambio = 1;

void setup() {
  Serial.begin(115200);
  pinMode(D4, OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password);
}

void activarPorton(){
    digitalWrite(D4, HIGH);
    delay(1000);
    digitalWrite(D4, LOW);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Desconectado");
   if(cambio==2){
      activarPorton();
      cambio=1;
    }
  } else {    
    if(cambio==1){
      activarPorton();
      cambio=2;
    }
   
    Serial.println("Conectado");
  }
  
}
