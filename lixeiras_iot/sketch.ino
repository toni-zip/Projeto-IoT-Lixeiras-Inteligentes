#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Wokwi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Broker MQTT público
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "mackenzie/lixeiras/nivel";
const char* client_id = "esp32-lixeira-01";

// Pinos HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 18

// Altura interna da lixeira em cm
#define ALTURA_LIXEIRA 30

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    if (client.connect(client_id)) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.println(client.state());
      delay(3000);
    }
  }
}

float medirDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duracao = pulseIn(ECHO_PIN, HIGH);
  float distancia = duracao * 0.034 / 2;
  return distancia;
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  float distancia = medirDistancia();
  
  // Calcula percentual de preenchimento
  float nivel = ((ALTURA_LIXEIRA - distancia) / ALTURA_LIXEIRA) * 100;
  if (nivel < 0) nivel = 0;
  if (nivel > 100) nivel = 100;

  // Monta payload JSON
  char payload[80];
  snprintf(payload, sizeof(payload),
    "{\"distancia\":%.1f,\"nivel\":%.1f}",
    distancia, nivel);

  client.publish(mqtt_topic, payload);
  
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.print(" cm | Nível: ");
  Serial.print(nivel);
  Serial.println("%");

  delay(15000); // envia a cada 15 segundos
}