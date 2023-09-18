#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

char ssid[] = "YourWiFiSSID"; // Replace with your Wi-Fi SSID
char pass[] = "YourWiFiPassword"; // Replace with your Wi-Fi password
char serverAddress[] = "https://api.tago.io/data"; // TagoIO API endpoint
char contentHeader[] = "application/json"; // Content type for HTTP request
char tokenHeader[] = "YourTagoIOToken"; // Your TagoIO token
HTTPClient client; // Initialize an instance of the HTTP client

// DHT Pin, analog input
#define DHT_PIN A1
DHT dht(DHT_PIN, DHT11);

// Pin definition for LDR sensor
#define LDR_PIN A2

void setup() {
  Serial.begin(9600);
  init_wifi();
  dht.begin();
}

void init_wifi() {
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int ldrValue = analogRead(LDR_PIN);

  char postData[300];
  int statusCode = 0;

  // Create a JSON payload for TagoIO
  snprintf(postData, sizeof(postData),
           "{\n\t\"temperature\": %.2f,\n\t\"humidity\": %.2f,\n\t\"light_level\": %d\n}",
           temperature, humidity, ldrValue);

  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

  delay(2000);
  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.println("End of POST to TagoIO");
  Serial.println();

  // Delay for 5 seconds before sending another reading
  delay(5000);
}
