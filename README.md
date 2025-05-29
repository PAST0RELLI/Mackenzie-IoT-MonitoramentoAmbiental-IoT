# Projeto de Objetos Inteligentes Conectados  - UPM
## Monitoramento Automatizado de Temperatura e Umidade com IoT

Este repositório contém os artefatos do projeto desenvolvido para a disciplina de Projeto de Objetos Inteligentes Conectados da Universidade Presbiteriana Mackenzie. O objetivo foi construir um protótipo de sistema IoT para monitoramento automatizado de temperatura e umidade em múltiplos ambientes, com integração de dados climáticos externos e visualização em dashboards.

### Motivação e Objetivos

O projeto visa explorar as capacidades da Internet das Coisas para:
- Melhorar o conforto e o bem-estar em ambientes internos.
- Promover a eficiência energética através do monitoramento preciso.
- Fornecer uma plataforma para coleta e análise de dados ambientais.
- Alinhar-se com os Objetivos de Desenvolvimento Sustentável (ODS) da ONU, especificamente o ODS 3 (Saúde e Bem-Estar) e o ODS 11 (Cidades e Comunidades Sustentáveis).

### Arquitetura da Solução

O sistema é composto por:
1.  **Dispositivos Sensores (Simulados no Wokwi):** Dois ESP32, cada um com um sensor DHT22, monitorando "Local 1 - Sala" e "Local 2 - Quarto".
2.  **Comunicação:** Os dados são enviados via protocolo MQTT para um broker público (HiveMQ).
3.  **Processamento (Low Code):** Uma instância do Node-RED subscreve aos tópicos MQTT, processa os dados, integra com a API OpenWeatherMap (para dados climáticos de São Paulo) e formata as informações.
4.  **Armazenamento:** Os dados formatados são enviados para um banco de dados de série temporal InfluxDB Cloud.
5.  **Visualização:** Dashboards customizados são criados no Grafana Cloud para exibir os dados em tempo real e históricos.

### Conteúdo do Repositório

-   **/firmware_esp32**: Contém os sketches Arduino (.ino) para os microcontroladores ESP32 simulados (Local 1 e Local 2).
-   **/node_red_flow**: Contém o arquivo JSON do fluxo exportado do Node-RED.
-   **/diagramas_e_mockups (Opcional)**: Imagens de diagramas e mockups utilizados no artigo do projeto.
-   **README.md**: Esta descrição.

### Componentes Utilizados

**Hardware (Simulado):**
-   ESP32 (x2)
-   Sensor DHT22 (x2)

**Software e Plataformas:**
-   Wokwi (Simulador online para ESP32)
-   Arduino IDE (para desenvolvimento do firmware)
-   MQTT (Broker: HiveMQ)
-   Node-RED
-   API OpenWeatherMap
-   InfluxDB Cloud
-   Grafana Cloud

### Como Utilizar / Replicar

**1. Firmware ESP32:**
   - Os códigos em `/firmware_esp32/` podem ser carregados em projetos ESP32 no Wokwi ou em dispositivos físicos (com as devidas adaptações de pinagem, se necessário).
   - Certifique-se de que os ESP32 tenham acesso à rede Wi-Fi configurada no código (`Wokwi-GUEST` para simulação).

**2. Fluxo Node-RED:**
   - Importe o arquivo `flow_monitoramento_ambiental.json` (localizado em `/node_red_flow/`) para sua instância do Node-RED.
   - **Configurações Necessárias Após Importação:**
     - **Nós MQTT In:** Configure o servidor Broker MQTT para `broker.hivemq.com` (porta 1883) ou seu broker preferido. Ajuste os tópicos se você utilizou um prefixo MQTT diferente de `TESTMACK1870/10419046`.
     - **Nó "Build OWM URL" (Function):** Insira sua própria API Key do OpenWeatherMap.
     - **Nó "InfluxDB: Dados Ambientais" (influxdb out):** Configure com os detalhes da sua instância InfluxDB Cloud (URL, Organização, Bucket e Token de API com permissão de escrita).

**3. InfluxDB e Grafana:**
   - Configure um bucket no InfluxDB Cloud para receber os dados.
   - No Grafana Cloud, adicione sua instância InfluxDB Cloud como Data Source.
   - Crie dashboards para visualizar os dados do measurement `monitoramento_ambiental`, utilizando os campos e tags conforme descrito no artigo do projeto.

### Autores

-   GABRIEL PASTORELLI DE ALMEIDA - 10419046
-   GABRIEL NEMAN SILVA - 10403348
-   RODRIGO GRAZIANI ROMARIS - 10418111
-   Prof. Wallace Rodrigues de Santana


---
**https://youtu.be/biyavQbOidU
---
