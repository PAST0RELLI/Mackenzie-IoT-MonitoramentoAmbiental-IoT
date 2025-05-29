#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>

const char* SSID = "Wokwi-GUEST";
const char* PASSWORD = "";

const char* BROKER_MQTT = "broker.hivemq.com";
const int BROKER_PORT = 1883;
const char* MQTT_CLIENT_ID = "ESP32_Wokwi_Local1";
const char* TOPICO_TEMP = "TESTMACK1870/10419046/local1/temperatura";
const char* TOPICO_UMID = "TESTMACK1870/10419046/local1/umidade";

const int DHT_PIN = 15;
DHTesp dhtSensor;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
unsigned long previousMillis = 0;
const long interval = 5000;

void conectarWiFi() {
  Serial.println();
  Serial.print("Conectando ao WiFi SSID: ");
  Serial.println(SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  int tentativas = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tentativas++;
    if (tentativas > 20) {
      Serial.println("\nFalha ao conectar ao WiFi. Reiniciando...");
      ESP.restart();
    }
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
}

void reconectarMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Tentando conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);
    Serial.print("Com Client ID: ");
    Serial.println(MQTT_CLIENT_ID);
    if (mqttClient.connect(MQTT_CLIENT_ID)) {
      Serial.println("Conectado ao Broker MQTT!");
    } else {
      Serial.print("Falha na conexão MQTT, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\n--- Iniciando ESP32 Local 1 ---");
  Serial.print("Configurando sensor DHT22 no pino ");
  Serial.println(DHT_PIN);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT22);
  Serial.print("Status do sensor DHT: ");
  Serial.println(dhtSensor.getStatusString());
  conectarWiFi();
  Serial.print("Configurando servidor MQTT: ");
  Serial.print(BROKER_MQTT);
  Serial.print(":");
  Serial.println(BROKER_PORT);
  mqttClient.setServer(BROKER_MQTT, BROKER_PORT);
  Serial.println("Setup concluído.");
}

void loop() {
  if (!mqttClient.connected()) {
    reconectarMQTT();
  }
  mqttClient.loop();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.println("\nLendo dados do sensor DHT...");
    TempAndHumidity data = dhtSensor.getTempAndHumidity();
    if (dhtSensor.getStatus() == DHTesp::ERROR_NONE) {
      char tempString[8];
      char umidString[8];
      dtostrf(data.temperature, 4, 2, tempString);
      dtostrf(data.humidity, 4, 2, umidString);
      Serial.print("Publicando no topico [");
      Serial.print(TOPICO_TEMP);
      Serial.print("]: ");
      Serial.println(tempString);
      mqttClient.publish(TOPICO_TEMP, tempString);
      Serial.print("Publicando no topico [");
      Serial.print(TOPICO_UMID);
      Serial.print("]: ");
      Serial.println(umidString);
      mqttClient.publish(TOPICO_UMID, umidString);
      Serial.printf("Local 1 -> Leitura Atual: Temp: %s°C | Umid: %s%%\n", tempString, umidString);
    } else {
      Serial.print("Falha ao ler do sensor DHT! Status: ");
      Serial.println(dhtSensor.getStatusString());
    }
  }
}