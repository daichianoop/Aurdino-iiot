// Example testing sketch for various DHT humidity/temperature sensors  
// Written by ladyada, public domain  

// REQUIRES the following Arduino libraries:  
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library  
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor  

#include "DHT.h"  

#define DHTPIN 14     // Digital pin connected to the DHT sensor  
#define LEDPIN 12     // Digital pin connected to the LED  

// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --  
// Pin 15 can work but DHT must be disconnected during program upload.  

// Uncomment whatever type you're using!  
#define DHTTYPE DHT11   // DHT 11  
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321  
//#define DHTTYPE DHT21   // DHT 21 (AM2301)  

// Connect pin 1 (on the left) of the sensor to +5V  
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1  
// to 3.3V instead of 5V!  
// Connect pin 2 of the sensor to whatever your DHTPIN is  
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)  
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)  
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor  

// Initialize DHT sensor.  
DHT dht(DHTPIN, DHTTYPE);  

void setup() {  
  Serial.begin(9600);  
  Serial.println(F("DHTxx test!"));  

  dht.begin();  
  
  // Initialize the LED pin as an output  
  pinMode(12, OUTPUT);  
}  

void loop() {  
  // Wait a few seconds between measurements.  
  delay(2000);  

  // Reading temperature or humidity takes about 250 milliseconds!  
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)  
  float h = dht.readHumidity();  
  // Read temperature as Celsius (the default)  
  float t = dht.readTemperature();  
  // Read temperature as Fahrenheit (isFahrenheit = true)  
  float f = dht.readTemperature(true);  

  // Check if any reads failed and exit early (to try again).  
  if (isnan(h) || isnan(t) || isnan(f)) {  
    Serial.println(F("Failed to read from DHT sensor!"));  
    return;  
  }  

  // Compute heat index in Fahrenheit (the default)  
  float hif = dht.computeHeatIndex(f, h);  
  // Compute heat index in Celsius (isFahrenheit = false)  
  float hic = dht.computeHeatIndex(t, h, false);  

  Serial.print(F("Humidity: "));  
  Serial.print(h);  
  Serial.print(F("%  Temperature: "));  
  Serial.print(t);  
  Serial.print(F("°C "));  
  Serial.print(f);  
  Serial.print(F("°F  Heat index: "));  
  Serial.print(hic);  
  Serial.print(F("°C "));  
  Serial.print(hif);  
  Serial.println(F("°F"));  

  // Control the LED based on humidity  
  if (h > 60) {  
    digitalWrite(12, HIGH);  // Turn the LED on  
  } else {  
    digitalWrite(12, LOW);   // Turn the LED off  
  }  
}
