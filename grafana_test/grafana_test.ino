#if defined(ESP32)
  #include <WiFiMulti.h>
  WiFiMulti wifiMulti;
  #define DEVICE "ESP32"
#elif defined(ESP8266)
  #include <ESP8266WiFiMulti.h>
  ESP8266WiFiMulti wifiMulti;
  #define DEVICE "ESP8266"
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// WiFi AP SSID
#define WIFI_SSID "AKATSUKI"
// WiFi password
#define WIFI_PASSWORD "Ifreshcola"

#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "Zna9uBMs0ZD4_zby13mWVHTPb_79Zu3QUgZVvw3gosZLMAuDCaYXMwjcpuMyHc8S-mExXh1ajvxxPZnNf4FTgQ=="
#define INFLUXDB_ORG "24cb7443e95f7425"
#define INFLUXDB_BUCKET "random_numbers"

#define TZ_INFO "UTC3"

// InfluxDB client
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

Point randomPoint("random_data");

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\nWiFi connected!");

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  randomSeed(analogRead(0));
}

void loop() {
  int randomNumber = random(0, 100);

  Serial.print("Generated random number: ");
  Serial.println(randomNumber);

  Point randomPoint("random_data");

  randomPoint.addField("value", randomNumber);
  randomPoint.addTag("device", DEVICE);

  if (!client.writePoint(randomPoint)) {
    Serial.print("Write failed: ");
    Serial.println(client.getLastErrorMessage());
  } else {
    Serial.println("Random number written to InfluxDB.");
  }

  delay(5000);
}
