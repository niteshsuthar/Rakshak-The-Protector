
#include <ESP8266WiFi.h>
#include <espnow.h>

int help;
uint8_t broadcastAddress[] = {0xE8, 0xDB, 0x84, 0xA8, 0xC5, 0x63};

typedef struct struct_message {
int help;
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  
  Serial.begin(115200);
  pinMode(2,INPUT);
  WiFi.mode(WIFI_STA);


  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
  
void loop() { 
    int help = digitalRead(2);
    if(help == 1){
    myData.help = 1;
    Serial.println("Send a new message 1");
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    }
    if(help == 0){ 
    myData.help = 0;
    Serial.println("Send a new message 2");
    esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    }
}
