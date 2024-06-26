//TUGAS SIC
//IKRAM UNGGUL ATMAJA
//MAN 10 JAKARTA

#include <WiFi.h>
#include <HTTPClient.h>
#include "MQ135.h"

#define MQ135_PIN 35

MQ135 gasSensor = MQ135(MQ135_PIN);

const char* ssid = "Vitiarium"; 
const char* password = "Allium Sativa21"; 
const char* serverName = "http://192.168.99.22:5000/sensor/data";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Menyambung :D");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Menyambung ke ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(5000);
}

void loop() {
  int gasLevel = analogRead(33);

  if (isnan(gasLevel)) {
    Serial.println("gagal membaca MQ135 sensor!");
    return;
  }

  if (WiFi.status() == WL_TERHUBUNG) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Tipe Konten", "application/x-www-form-urlencoded");
    String Data_Post = "gas_level=" + String(gasLevel);
    int httpResponseCode = http.POST(Data_Post);
    Serial.println(http.POST(Data_Post));
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Error in WiFi connection");
  }

  delay(500); // Kirim data setiap 0,5 detik
}
