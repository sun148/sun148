
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>



ESP8266WiFiMulti WiFiMulti;


// DHT config.
#define DHTPIN            2         // Pin which is connected to the DHT sensor.
// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int status = WL_IDLE_STATUS;
float myTemperature = 0, myHumidity = 0; 


void setup() {

Serial.begin(115200);
for (uint8_t t = 4; t > 0; t--) {
Serial.printf("[SETUP] WAIT %d...\n", t);
Serial.flush();
delay(1000);
}

WiFiMulti.addAP("wifi_2_4ghz", "password"); // ssid , password <================= change
randomSeed(50);

dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
if ((WiFiMulti.run() == WL_CONNECTED)) {

// Read data from DHT------------------------------------------------------------
// Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    // Update temperature and humidity
    myTemperature = (float)event.temperature;
    Serial.print("Temperature: ");
    Serial.print(myTemperature);
    Serial.println(" C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
     myHumidity = (float)event.relative_humidity;
    Serial.print("Humidity: ");
    Serial.print(myHumidity);
    Serial.println("%");
  }
//----------------------------------------------------------------------------------------------------------------
//int temp = random(25,35);
String url = "http://192.168.0.22/ESP2022/esp8266/nodemcu/nodemcu/esp8266mysql/add.php?temp="+String(myTemperature)+"&"+"hum="+String(myHumidity);
            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ change ip address to your HOST computer ^^^^^^ and PAHT of PHP Web site 
Serial.println(url);
WiFiClient client;
HTTPClient http;
http.begin(client,url); //HTTP


int httpCode = http.GET();
if (httpCode > 0) {
Serial.printf("[HTTP] GET... code: %d\n", httpCode);
if (httpCode == HTTP_CODE_OK) {
String payload = http.getString();
Serial.println(payload);
}
} else {
Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
}
http.end();
}


delay(360000); // <============== change Delay function for rate of data to your Mysql server throughput
}
