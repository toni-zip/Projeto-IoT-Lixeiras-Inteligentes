# ♻️ Lixeiras Inteligentes IoT

Projeto acadêmico desenvolvido para monitoramento inteligente de lixeiras utilizando **ESP32, MQTT, Node-RED e InfluxDB**.

## 📌 Sobre o projeto

Este projeto simula um sistema de lixeiras inteligentes capaz de monitorar o nível de ocupação de diferentes lixeiras em tempo real.

Cada lixeira envia informações simuladas para um broker MQTT, que são processadas pelo Node-RED, armazenadas no InfluxDB e utilizadas para geração de alertas e visualização em dashboard.

A proposta é aplicar conceitos de **Internet das Coisas (IoT)** em um cenário de automação urbana.

---

## 🎯 Objetivo

Desenvolver uma solução que permita:

- Monitorar o nível de ocupação de lixeiras
- Gerar alertas automáticos quando estiverem cheias
- Armazenar dados históricos
- Disponibilizar informações para visualização em dashboard
- Simular uma aplicação prática de IoT

---

## 🛠 Tecnologias utilizadas

### Hardware / Simulação
- ESP32
- Sensor ultrassônico HC-SR04 (simulado)
- Wokwi

### Comunicação
- MQTT
- Broker HiveMQ

### Processamento
- Node-RED

### Banco de dados
- InfluxDB

---

## 🏗 Arquitetura do sistema

```text
ESP32 (simulação)
   ↓
MQTT
   ↓
Broker HiveMQ
   ↓
Node-RED
   ↓
InfluxDB
   ↓
Dashboard / Alertas
```

---

## 📂 Estrutura do fluxo

<img width="1357" height="787" alt="image" src="https://github.com/user-attachments/assets/3ce4da23-66d7-41c1-9957-cec0e9e29f68" />

O fluxo no Node-RED foi dividido em 3 partes principais:

### 1. Recepção MQTT
Responsável por:

- Receber mensagens das 6 lixeiras
- Fazer o parse dos dados JSON

---

### 2. Armazenamento no InfluxDB
Os dados são separados em:

- Nível de ocupação
- Distância medida
- Alertas críticos

---

### 3. Dashboard e alertas
O sistema:

- Identifica lixeiras críticas
- Publica alertas MQTT
- Consolida dados para dashboard

---

## 🗑 Lixeiras simuladas

| ID | Local |
|----|------|
| LX-01 | Bloco A - Entrada |
| LX-02 | Bloco B - Corredor |
| LX-03 | Biblioteca |
| LX-04 | Refeitório |
| LX-05 | Bloco C - Laboratório |
| LX-06 | Estacionamento |

---

## ⚙ Funcionamento

Cada lixeira possui:

- Um nível inicial
- Uma taxa de enchimento simulada
- Um tópico MQTT específico

Exemplo de payload enviado:

```json
{
  "id": "LX-01",
  "local": "Bloco A - Entrada",
  "distancia": 4.5,
  "nivel": 85.0
}
```

---
## Dashboards gerados pelo Grafana
# Dashboard 1
<img width="1492" height="693" alt="image" src="https://github.com/user-attachments/assets/871873d8-f9dc-4f4d-bb0e-da9de0f0bd8b" />

# Dashboard 2
<img width="1522" height="820" alt="image" src="https://github.com/user-attachments/assets/6d0f2d62-7f10-44ca-8d0d-40859fc45633" />



## 🚨 Sistema de alerta

Quando o nível da lixeira ultrapassa **85%**, o sistema:

- Detecta condição crítica
- Publica alerta via MQTT
- Registra evento no InfluxDB
- Alerta é enviado por uma API do Telegram

---

## Link da Apresentação
https://youtu.be/anO3y3dcS6Q

---

## ▶ Como executar

### 1. Executar a simulação no Wokwi
Iniciar o código ESP32.

### 2. Executar o Node-RED

```bash
node-red
```

Importar o fluxo do projeto.

### 3. Executar o InfluxDB

```bash
docker run -p 8086:8086 influxdb
```

---

## ✅ Funcionalidades implementadas

- Simulação de 6 lixeiras
- Envio de dados via MQTT
- Processamento em tempo real
- Persistência de dados
- Geração automática de alertas
- Consolidação para dashboard

---
