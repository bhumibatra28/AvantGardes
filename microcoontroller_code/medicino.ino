#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "HOME_WIFI"
#define WIFI_PASSWORD "5zju8x9ki"
#define API_KEY "AIzaSyDOsTW1CmsWLEe1uZDuXuSDEaFUOAU8tdc"
#define DATABASE_URL "medocino-19c8f-default-rtdb.firebaseio.com" 
#define USER_EMAIL "sourcetech83@gmail.com"
#define USER_PASSWORD "123456789"
FirebaseData fbdo, fbdo1;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int C1=0, C2=0;
int red=33, green=25, m1f=26, m2f=27, m1r=34, m2r=35;
time_t rawtime;
struct tm timeinfo;
char timeStringBuff[50];
void setup()
{
  Serial.begin(115200);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(m1f,OUTPUT);
  pinMode(m2f,OUTPUT);
  pinMode(m1r,OUTPUT);
  pinMode(m2r,OUTPUT);
  digitalWrite(red,HIGH);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  digitalWrite(red,LOW);
  delay(200);
  digitalWrite(green,HIGH);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  Firebase.begin(&config, &auth);
}

void loop()
{
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    Firebase.getInt(fbdo, "/C1");
    C1=fbdo.intData();
    for(int i=0; i<C1; i++){
      digitalWrite(m1f, HIGH);
      delay(3000);
      digitalWrite(m1f, LOW);
      digitalWrite(m1r, HIGH);
      delay(3000);
      digitalWrite(m1r, LOW);
      Serial.print("Medicine delivered");
    }
  }
}
