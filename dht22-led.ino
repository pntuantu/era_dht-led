/* Define MQTT host */
#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"

// You should get Auth Token in the ERa App or ERa Dashboard
#define ERA_AUTH_TOKEN "acd2a2c4-a272-46f9-9c9c-d6cc48dc591d"

#include <ERa.hpp>
#include <DHT.h>

// WiFi credentials
const char ssid[] = "IoT Lab";
const char pass[] = "IoT@123456";

// DHT configuration
#define DHTPIN 4        // Pin connected to DHT22
#define DHTTYPE DHT22   // Define DHT22 type
DHT dht(DHTPIN, DHTTYPE);

ERaTimer timer;

void timerEvent() {
    // Read DHT values
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if reading is successful
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error reading DHT22");
        return;
    }

    // Send DHT data to virtual pins
    ERa.virtualWrite(V0, temperature);
    ERa.virtualWrite(V1, humidity);
}

void setup() {
    Serial.begin(115200);
    ERa.begin(ssid, pass);
    dht.begin();

    timer.setInterval(5000L, timerEvent);
}

void loop() {
    ERa.run();
    timer.run();
}