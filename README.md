# ♻️ Projeto IoT - Lixeiras Inteligentes

Sistema de monitoramento inteligente de resíduos utilizando conceitos de Internet das Coisas (IoT), desenvolvido na Universidade Presbiteriana Mackenzie.

O projeto simula seis lixeiras inteligentes conectadas a uma arquitetura baseada em MQTT, Node-RED, InfluxDB e Grafana, permitindo monitoramento em tempo real, geração de alertas automáticos e armazenamento histórico das informações.

---

# 📖 Sumário

- Sobre o Projeto
- Objetivos
- Arquitetura da Solução
- Tecnologias Utilizadas
- Estrutura do Repositório
- Funcionamento do Sistema
- Lixeiras Simuladas
- Comunicação MQTT
- Fluxo Node-RED
- Dashboards Grafana
- Sistema de Alertas
- Como Executar
- Funcionalidades Implementadas
- Melhorias Futuras
- Equipe
- Artigo Científico
- Demonstração
- Licença

---

# 📌 Sobre o Projeto

A gestão de resíduos sólidos é um desafio constante em ambientes urbanos e institucionais.

Este projeto propõe uma solução baseada em IoT para monitorar o nível de ocupação de lixeiras em tempo real, permitindo que equipes de manutenção atuem de forma mais eficiente e reduzindo transbordamentos e deslocamentos desnecessários.

---

# 🎯 Objetivos

✅ Monitorar o nível de ocupação das lixeiras

✅ Gerar alertas automáticos

✅ Armazenar dados históricos

✅ Disponibilizar dashboards em tempo real

✅ Demonstrar integração entre múltiplas tecnologias IoT

---

# 🏗 Arquitetura da Solução

```text
ESP32 (Wokwi)
       │
       ▼
MQTT (HiveMQ)
       │
       ▼
Node-RED
   ├── Processamento
   ├── Alertas
   └── Dashboard MQTT
       │
       ▼
InfluxDB Cloud
       │
       ▼
Grafana

       │
       ▼
Telegram
```

---

# 🛠 Tecnologias Utilizadas

- ESP32
- HC-SR04 (simulado)
- Wokwi
- MQTT
- HiveMQ
- Node-RED
- InfluxDB Cloud
- Grafana
- Telegram Bot API

---

# 📂 Estrutura do Repositório

```text
Projeto-IoT-Lixeiras-Inteligentes
│
├── README.md
├── Trabalho_IoT_LixeirasInteligentes_Final.pdf
├── nodeRedLixosIOT-2.json
└── Lixeiras_IOT
```

---

# 🗑 Lixeiras Simuladas

| ID | Localização |
|------|------|
| LX-01 | Bloco A - Entrada |
| LX-02 | Bloco B - Corredor |
| LX-03 | Biblioteca |
| LX-04 | Refeitório |
| LX-05 | Laboratório |
| LX-06 | Estacionamento |

---

# 📡 Comunicação MQTT

Broker:

```text
broker.hivemq.com
```

Porta:

```text
1883
```

Tópicos:

```text
mackenzie/lixeiras/#
mackenzie/lixeiras/alertas
mackenzie/dashboard/status
```

---

# 🔄 Fluxo Node-RED

## Estrutura Completa do Fluxo

Substitua esta seção pela imagem hospedada no GitHub:

```html
<img width="1357" height="787" alt="Fluxo Node-RED" src="https://github.com/user-attachments/assets/3ce4da23-66d7-41c1-9957-cec0e9e29f68" />
```

### 1️⃣ Recepção MQTT

Recebe mensagens das seis lixeiras e realiza o parse JSON.

### 2️⃣ Armazenamento

Measurements:

```text
nivel_lixeira
distancia_lixeira
alertas_lixeira
```

### 3️⃣ Sistema de Alertas

Quando:

```text
Nível ≥ 85%
```

o sistema:

- Publica alerta MQTT
- Registra no InfluxDB
- Envia alerta Telegram

### 4️⃣ Consolidação para Dashboard

Publicação:

```text
mackenzie/dashboard/status
```

### 5️⃣ Proteção Contra Spam

```text
1 alerta por lixeira a cada 5 minutos
```

---

# 📊 Dashboards Grafana

## Dashboard 1 - Visão Geral

Cole a imagem atual do Dashboard 1.

## Dashboard 2 - Monitoramento Individual

Cole a imagem atual do Dashboard 2.

---

# 🚨 Sistema de Alertas

Sempre que uma lixeira atingir:

```text
>= 85%
```

o sistema:

- Publica alerta MQTT
- Atualiza dashboards
- Registra evento no banco
- Envia notificação Telegram

---

# ▶ Como Executar

## 1 - Wokwi

Abrir a simulação e iniciar o ESP32.

## 2 - Node-RED

```bash
npm install -g --unsafe-perm node-red
node-red
```

Acessar:

```text
http://localhost:1880
```

Importar:

```text
nodeRedLixosIOT-2.json
```

## 3 - InfluxDB

Criar bucket:

```text
lixeiras_dados
```

## 4 - Grafana

Adicionar datasource InfluxDB e utilizar:

```text
nivel_lixeira
distancia_lixeira
alertas_lixeira
```

---

# ✅ Funcionalidades Implementadas

- Simulação de 6 lixeiras
- MQTT
- Node-RED
- InfluxDB
- Grafana
- Alertas Telegram
- Dashboards em tempo real

---

# 🚀 Melhorias Futuras

- Sensores físicos
- Aplicativo mobile
- Machine Learning
- Google Maps
- AWS IoT Core

---

# 👨‍💻 Equipe

- Antonio Pereira
- Fernando Lacava
- João Trevisol
- Matheus Fernandes
- Wallace Santana

Universidade Presbiteriana Mackenzie

---

# 📄 Artigo Científico

Trabalho_IoT_LixeirasInteligentes_Final.pdf

---

# 🎥 Demonstração

https://youtu.be/anO3y3dcS6Q

---

# 📜 Licença

Projeto acadêmico desenvolvido para fins educacionais.
