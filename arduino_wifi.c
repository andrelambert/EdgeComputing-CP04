// Código para placa Wi-fi ESP32, para simular envio de dados para TagIO.

#include "Arduino.h"
#include "WiFi.h"
#include "HTTPClient.h"

char ssid[] = "Nome da Rede Wifi";    // Substitua pelo SSID da sua rede Wi-Fi
char pass[] = "12345";                // Substitua pela senha da sua rede Wi-Fi
char serverAddress[] = "https://api.tago.io/data";  // Endpoint da API do TagoIO
char contentHeader[] = "application/json"; // Tipo de conteúdo para a requisição HTTP
char tokenHeader[] = "c4123b90-822d-45a0-bf0d-8c77662f09a6"; // Token do TagoIO
HTTPClient client; // Inicialize uma instância do cliente HTTP

void setup() {
  Serial.begin(9600);
  init_wifi();
}

void init_wifi() {
  Serial.println("Conectando WiFi");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Conectado");
  Serial.print("Meu IP é: ");
  Serial.println(WiFi.localIP());
}

float pesoEmGramas = 0; // Altere o nome da variável para representar o peso

void loop() {
  char anyData[30];
  char postData[300];
  char anyData1[30];
  int statusCode = 0;
  
  // Substitua o código relacionado à temperatura pelo código relacionado ao peso
  strcpy(postData, "{\n\t\"variavel\": \"peso\",\n\t\"valor\": ");
  dtostrf(pesoEmGramas, 6, 2, anyData);
  strncat(postData, anyData, 100);
  strcpy(anyData1, ",\n\t\"unidade\": \"g\"\n\t}\n");
  strncat(postData, anyData1, 100);
  
  Serial.println(postData);
  client.begin(serverAddress);
  client.addHeader("Content-Type", contentHeader);
  client.addHeader("Device-Token", tokenHeader);
  statusCode = client.POST(postData);
  
  delay(2000);
  Serial.print("Código de status: ");
  Serial.println(statusCode);
  Serial.println("Fim do POST para o TagoIO");
  Serial.println();
  
  // Simule a mudança de peso
  pesoEmGramas += 10; // Você pode alterar isso para simular mudanças de peso
  delay(5000);
}