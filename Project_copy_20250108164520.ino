#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
const char* ssid = "ESP8266";
const char* password = "12345678";
int RXPin = D7;
int TXPin = D8;
int GPSBaud = 9600;
const int nanoSignalRX = D5;
String latc = "23.155809";
String longc = "72.664947";
TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);
const int alcSensor = D0;
String alcStatus = "";
String accidentStatus = "";
void setup() {
  Serial.begin(9600);
  pinMode(alcSensor, INPUT);
  pinMode(nanoSignalRX, INPUT);
  gpsSerial.begin(GPSBaud);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi");
    delay(2000);
  }
  Serial.println("Connected!!");
}
void loop() {
    if (gps.encode(gpsSerial.read()))
    {
      displayInfo();
    }
    else
    {
      displayInfo();
    }
}
void displayInfo() {
  Serial.println("Inside Display Info");
  // Accident Signal
  if (digitalRead(nanoSignalRX) == HIGH) {
    accidentStatus = "Emergency! Accident Detected";
    sms("accident");
  } else if (digitalRead(nanoSignalRX) == LOW) {
    accidentStatus = "No Accident Detected";
  }
  //Alcohol
  if (digitalRead(alcSensor) == HIGH) {
    Serial.println(digitalRead(alcSensor));
    alcStatus = "No Alcohol Detected";
  } else if (digitalRead(alcSensor) == LOW) {
    Serial.println(digitalRead(alcSensor));
    alcStatus = "Warning!! Alcohol Detected";
    
  }

  if (gps.location.isValid()) {
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    latc = String(latitude, 6);
    longc = String(longitude, 6);
    Serial.println("Latitude: " + latc);
    Serial.println("Longitude: " + longc);
    Serial.println("Accident Status: " + accidentStatus);
    Serial.println("Alcohol Status: " + alcStatus);
    delay(2000);
  } else {
    Serial.println("Latitude: " + latc);
    Serial.println("Longitude: " + longc);
    Serial.println("Accident Status: " + accidentStatus);
    Serial.println("Alcohol Status: " + alcStatus);
    delay(2000);
  }
}
void sms(String KEY) {
  HTTPClient http;
  http.begin("http://www.techvegan.in/ishan-sms/ishan-sms-api.php?latc="+latc+"&longc="+longc+"&key="+KEY);
  int httpCode = http.GET();
  if (httpCode > 0) {
    String value = http.getString();
    http.end();
     delay(10000);
  }