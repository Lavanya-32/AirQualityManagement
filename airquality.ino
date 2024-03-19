#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADS1X15.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include<WiFi.h>
#include<ThingSpeak.h>
#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define MQ6_PIN 39    // MQ6 analog pin connected to ESP32 ADC pin A0
#define MQ2_PIN  32     // MQ2 analog pin connected to ESP32 ADC pin A1
#define LCD_ADDR 0x27
#define D1 13 

const char* ssid="Redmi";
const char* password="Lavanya123";
unsigned long channelID = 2476735;
const char* writeAPIKey = "8C3DLPJPGGU7JYND";
//const int potPin=A0;
float Value=0;
int IR_sensor=D1;

WiFiClient client;


DHT dht(DHTPIN, DHT11);
LiquidCrystal lcd(19,23,18,17,16,15);
//DFRobot_PH ph_sensor;

void setup() {
  Serial.begin(9600);
  dht.begin();
  delay(2000);
  Wire.begin();
   lcd.begin(16,2);
  //lcd.backlight();
  //ph_sensor.begin();
  //pinMode(potPin,INPUT);
  WiFi.begin("Redmi","Lavanya123");
  pinMode(IR_sensor,INPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float humidity = dht.readHumidity();
  float Temperature = dht.readTemperature();
  float mq6Value = analogRead(MQ6_PIN);
  float mq2Value = analogRead(MQ2_PIN);

  // Print readings to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(Temperature);
  Serial.println(" *C");
  Serial.print("MQ-6");
  Serial.println(mq6Value);
  Serial.print(" MQ-2");
  Serial.println( mq2Value);

  delay(2000);  // Delay between readings
  ThingSpeak.writeField(2476735, 1, humidity, "8C3DLPJPGGU7JYND");
  ThingSpeak.writeField(2476735, 2, Temperature, "8C3DLPJPGGU7JYND");
  ThingSpeak.writeField(2476735, 3, mq6Value, "8C3DLPJPGGU7JYND");
  ThingSpeak.writeField(2476735, 4, mq2Value, "8C3DLPJPGGU7JYND");
  //ThingSpeak.writeField(2476735, 4, mq2Value, "8C3DLPJPGGU7JYND");
  
 if(IR_sensor==0)
 Serial.println("0");
 else
 Serial.println("1");
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("h:");
  Serial.print(humidity);
  lcd.print(humidity);

  lcd.setCursor(8, 0);
  lcd.print("t:");
  Serial.print(Temperature);
  lcd.print(Temperature);

  lcd.setCursor(0, 1);
  lcd.print("6:");
  Serial.print(mq6Value);
  lcd.print(mq6Value);

 lcd.setCursor(8, 1);
  lcd.print("2:");
  Serial.print(mq2Value);
  lcd.print(mq2Value);
}