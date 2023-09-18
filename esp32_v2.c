#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 4 // DHT11 data pin
#define DHTTYPE DHT11 // DHT sensor type
#define LDRPIN 34 // LDR sensor pin

DHT dht(DHTPIN, DHTTYPE);
float temperature, humidity;
int lightLevel;

char ssid[] = "YourWiFiSSID"; // Replace with your Wi-Fi SSID
char pass[] = "YourWiFiPassword"; // Replace with your Wi-Fi password
char serverAddress[] = "https://api.tago.io/data"; // TagoIO API endpoint
char contentHeader[] = "application/json"; // Content type for HTTP request
char tokenHeader[] = "YourTagoIOToken"; // Your TagoIO token
HTTPClient client; // Initialize an instance of the HTTP client

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize DHT sensor
  dht.begin();

  // Set LDR pin as an input
  pinMode(LDRPIN, INPUT);
}

void loop() {
  // Read temperature and humidity from DHT sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  // Read light level from LDR sensor
  lightLevel = analogRead(LDRPIN);

  // Create a JSON payload with the sensor data
  String jsonPayload = "{\"temperature\":" + String(temperature) +
                       ",\"humidity\":" + String(humidity) +
                       ",\"light\":" + String(lightLevel) + "}";

  // Send data to TagoIO
  if (sendDataToTagoIO(jsonPayload)) {
    Serial.println("Data sent to TagoIO successfully");
  } else {
    Serial.println("Failed to send data to TagoIO");
  }

  // Wait for 5 seconds before sending the next data
  delay(5000);
}

bool sendDataToTagoIO(String data) {
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Token", tokenHeader);

  int httpResponseCode = client.POST(data);

  if (httpResponseCode > 0) {
    String response = client.getString();
    Serial.print("HTTP Response Code: ");
    Serial.println(httpResponseCode);
    Serial.println(response);
    client.end();
    return true;
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(httpResponseCode);
    client.end();
    return false;
  }
}
