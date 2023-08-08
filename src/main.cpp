#include <Arduino.h>
#include <WiFiEspAT.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// WiFi settings
const char ssid[] = "YourSSID";      // Replace with your WiFi network name (SSID)
const char pass[] = "YourPass";      // Replace with your WiFi password

// MQTT settings
#define MQTT_SERVER "mqtt.zig-web.com"
#define MQTT_PORT 1883

// MQTT credentials
const char MQTT_USERNAME[] = "your_mqtt_username";
const char MQTT_PASSWORD[] = "your_mqtt_password";

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD);

// MQTT topics
Adafruit_MQTT_Publish testTopic = Adafruit_MQTT_Publish(&mqtt, "test_topic");

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial2.begin(115200);

  WiFi.init(Serial2);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println();
  
  Serial.println("Connected to WiFi");
  
  mqtt.connect();
}

void loop() {
  mqtt.processPackets(10000); // Process MQTT packets every 10 seconds

  if (!mqtt.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqtt.connect()) {
      Serial.println("Connected to MQTT");
    }
  }

  // Publish a message to the MQTT topic
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    Serial.println("Publishing message...");
    testTopic.publish("Cool");
  }
}
