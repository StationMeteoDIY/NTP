#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "SSID";          // SSID du réseau Wifi
const char* password = "xxx";  		// Mot de passe du réseau Wifi.

WiFiClient espClient;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

int test = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connexion au WiFi en cours...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connecxion au WiFi réussi");
  Serial.println(WiFi.localIP());
  
  // Démarrage du client NTP - Start NTP client
  timeClient.begin();
}

void loop() {
  // Relevé du serveur de temps via NTP, et stockage des Heures et Minutes
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  // Serial.println(timeClient.getHours());
  // Serial.println(timeClient.getMinutes());
    
  delay(5000);

  // pour test, on desactive
  if(test == 0) {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(1);
    Serial.println(WiFi.localIP());
    test = 1;
  }
}