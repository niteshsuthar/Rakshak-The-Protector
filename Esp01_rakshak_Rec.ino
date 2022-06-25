
#include <ESP8266WiFi.h>
#include <espnow.h>


typedef struct struct_message {
    
    int help;
    
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Int: ");
  Serial.println(myData.help);
  Serial.println();
  if(myData.help==1){
    digitalWrite(2,HIGH);
    Serial.println("ON");
    }
    if(myData.help==0){ 
    digitalWrite(2,LOW);
    Serial.println("OFF");
  } 
}
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
 if(myData.help==0){ 
    digitalWrite(2,LOW);
    Serial.println("OFF");
    }
}
