#include <WiFi.h>
#include <PubSubClient.h>

// WiFi Wokwi
const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// Broker MQTT público
const char* mqtt_server = "broker.hivemq.com";
const int   mqtt_port   = 1883;

// Altura interna de cada lixeira (cm) — pode variar por modelo
#define ALTURA_LIXEIRA 30

// ─── Definição das 6 lixeiras ────────────────────────────────────────────────
struct Lixeira {
  const char* id;           // identificador único
  const char* local;        // descrição do local
  const char* topic;        // tópico MQTT
  float       nivelBase;    // nível inicial simulado (%)
  float       variacao;     // quanto varia a cada ciclo (%)
};

Lixeira lixeiras[6] = {
  { "LX-01", "Bloco A - Entrada",    "mackenzie/lixeiras/LX-01", 85.0, 2.0  },
  { "LX-02", "Bloco B - Corredor",   "mackenzie/lixeiras/LX-02", 65.0, 3.5  },
  { "LX-03", "Biblioteca",           "mackenzie/lixeiras/LX-03", 50.0, 1.5  },
  { "LX-04", "Refeitorio",           "mackenzie/lixeiras/LX-04", 30.0, 4.0  },
  { "LX-05", "Bloco C - Lab",        "mackenzie/lixeiras/LX-05", 10.0, 2.5  },
  { "LX-06", "Estacionamento",       "mackenzie/lixeiras/LX-06",  5.0, 1.0  },
};

// Níveis atuais de cada lixeira (simulados em memória)
float niveisAtuais[6];

WiFiClient   espClient;
PubSubClient client(espClient);

// ─── WiFi ────────────────────────────────────────────────────────────────────
void setup_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado! IP: " + WiFi.localIP().toString());
}

// ─── MQTT reconnect ──────────────────────────────────────────────────────────
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando MQTT...");
    String clientId = "esp32-lixeiras-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado!");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" — tentando em 3s");
      delay(3000);
    }
  }
}

// ─── Simulação de distância ──────────────────────────────────────────────────
// Converte nível (%) → distância livre (cm), com pequeno ruído
float simularDistancia(float nivel) {
  float distancia = ALTURA_LIXEIRA * (1.0 - nivel / 100.0);
  // ruído de ±0.3 cm para simular leitura real do HC-SR04
  distancia += (random(-30, 30) / 100.0);
  if (distancia < 0)              distancia = 0;
  if (distancia > ALTURA_LIXEIRA) distancia = ALTURA_LIXEIRA;
  return distancia;
}

// ─── Setup ───────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  // Inicializa níveis com valores base de cada lixeira
  for (int i = 0; i < 6; i++) {
    niveisAtuais[i] = lixeiras[i].nivelBase;
  }

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

// ─── Loop ────────────────────────────────────────────────────────────────────
void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  Serial.println("─────────────────────────────────");

  for (int i = 0; i < 6; i++) {
    // Simula aumento gradual do nível (lixeira enchendo)
    // Quando atinge 100%, "esvazia" (simula coleta)
    niveisAtuais[i] += lixeiras[i].variacao;
    if (niveisAtuais[i] >= 100.0) niveisAtuais[i] = 2.0; // coleta simulada

    float nivel     = niveisAtuais[i];
    float distancia = simularDistancia(nivel);

    // Monta payload JSON
    char payload[120];
    snprintf(payload, sizeof(payload),
      "{\"id\":\"%s\",\"local\":\"%s\",\"distancia\":%.1f,\"nivel\":%.1f}",
      lixeiras[i].id, lixeiras[i].local, distancia, nivel);

    client.publish(lixeiras[i].topic, payload);

    Serial.printf("[%s] %s | Nível: %.1f%% | Distância: %.1f cm\n",
      lixeiras[i].id, lixeiras[i].local, nivel, distancia);

    delay(300); // pequena pausa entre publicações
  }

  Serial.println();
  delay(15000); // ciclo completo a cada 15 segundos
}
