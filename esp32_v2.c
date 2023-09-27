#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"
#include <DHT.h>

char ssid[] = "Maia"; // Replace with your Wi-Fi SSID
char pass[] = "Azul Amarelo"; // Replace with your Wi-Fi password
char serverAddress[] = "https://api.tago.io/data"; // TagoIO API endpoint
char contentHeader[] = "application/json"; // Content type for HTTP request
char tokenHeader[] = "b7bcc0a5-7114-4035-abbe-261e3891275a"; // Your TagoIO token
HTTPClient client; // Initialize an instance of the HTTP client

// DHT Pin, analog input
#define DHT_PIN 27
DHT dht(DHT_PIN, DHT11);

// Pin definition for LDR sensor
#define LDR_PIN 14

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

  Serial.println(ldrValue);

// Temperatura
  char anyData[30];
  char postData[300];
  char anyData1[30];
  char bAny[30];
  int statusCode = 0;
  strcpy(postData, "{\n\t\"variable\": \"temperature\",\n\t\"value\": ");
  dtostrf(temperature, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

// Umidade
  strcpy(postData, "{\n\t\"variable\": \"humidity\",\n\t\"value\": ");
  dtostrf(humidity, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);

// Luz
  strcpy(postData, "{\n\t\"variable\": \"light\",\n\t\"value\": ");
  dtostrf(ldrValue, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unit\": \"C\"\n\t}\n");
  strncat (postData, anyData1, 100);
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
