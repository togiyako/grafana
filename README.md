
### ESP32 → InfluxDB → Grafana: Visualising random data ###

This project demonstrates how ESP32 (TTGO LoRa32 T3 V1.6.1) generates random numbers and sends them to InfluxDB Cloud 2.0, after which the data is visualised in Grafana.

## Requirements

ESP32 board (TTGO LoRa32 T3 V1.6.1)

Arduino IDE

Libraries:
 -InfluxDB Client for Arduino

 -WiFi.h

InfluxDB Cloud 2.0 account

Grafana account

How ot create DB and grafana account and connect both of them watch here: https://www.the-diy-life.com/grafana-weather-dashboard-using-influxdb-and-an-esp32-in-depth-tutorial/

## Upload to ESP32

Connect the board to the computer via USB.

In the Arduino IDE, open the main.ino file.

Replace the following lines with your data:
    #define WIFI_SSID "Your_SSID"
    #define WIFI_PASSWORD "Your_Password"
    #define INFLUXDB_URL "Your_InfluxDB_URL"
    #define INFLUXDB_TOKEN "Your_InfluxDB_Token"
    #define INFLUXDB_ORG "Your_Organization"
    #define INFLUXDB_BUCKET "random_numbers"

Select the correct board and port from the Tools menu.

Click ‘Upload’ to upload the code to the board

After successful download open SerialMonitor with 115200 baud you will see something like that:
    
    14:27:47.370 -> Random number written to InfluxDB.
    14:27:52.377 -> Generated random number: 92
    14:27:52.905 -> Random number written to InfluxDB.
    14:27:57.912 -> Generated random number: 35
    14:27:58.437 -> Random number written to InfluxDB.

If you see it, it's all good. Then go to grafana dashboards and create new Dashboard with a request for this guide:

from(bucket: "random_numbers")
  |> range(start: -5m)
  |> filter(fn: (r) => r._measurement == "random_data")
  |> filter(fn: (r) => r._field == "value")
  |> filter(fn: (r) => r.device == "ESP32")

