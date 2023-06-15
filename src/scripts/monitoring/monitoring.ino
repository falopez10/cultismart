#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid     = "LOPEZ_CORREDOR-ETB";
const char* password = "12MEJORAR";
const char* server = "jsonplaceholder.typicode.com";
const int httpsPort = 443;

const int flashPin = 4;
const int humidityPin = 12;
// const int lightPin = A1;
// const int temperaturePin = A2;

void setup() {
  Serial.begin(9600);

  pinMode(flashPin, OUTPUT);

  pinMode(humidityPin, INPUT);
  // pinMode(lightPin, INPUT);
  // pinMode(temperaturePin, INPUT);
}

void loop() {
  blink();
  readValues();
  digitalWrite(flashPin, LOW);
  delay(5000);
}

void wifiSetup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi " + String(ssid));
  }

  Serial.println("Connected to WiFi");
}

void sendPayload() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "https://jsonplaceholder.typicode.com/todos";

    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"title\":\"value1\",\"body\":\"value2\",\"userId\":1}";

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode == HTTP_CODE_CREATED) {
      String response = http.getString();
      Serial.print("Response body: ");
      Serial.println(response);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

void blink() {
  digitalWrite(flashPin, HIGH);
  delay(182);
  digitalWrite(flashPin, LOW);
  delay(182);
  digitalWrite(flashPin, HIGH);
  delay(182);
  digitalWrite(flashPin, LOW);
  delay(182);
}

int percentageNumber(int sensor_analog) {
  float percentage;
  percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  return percentage;
}

void readValues() {
  int rawHumidity = analogRead(humidityPin);
  int humidityValue = percentageNumber(rawHumidity);
  // int lightValue = analogRead(lightPin);
  // int temperatureValue = analogRead(temperaturePin);
  
  Serial.print("Humidity: ");
  Serial.print(humidityValue);
  Serial.print("\n Raw Humidity: ");
  Serial.print(rawHumidity);
  // Serial.print("\tLight: ");
  // Serial.print(lightValue);
  // Serial.print("\tTemperature: ");
  // Serial.println(temperatureValue);

  digitalWrite(flashPin, HIGH);
  delay(100 * humidityValue);
  digitalWrite(flashPin, LOW);
  
}


