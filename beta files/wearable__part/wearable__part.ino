// importing librarys
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <cmath>
#include <WiFi.h>

const char* ssid = "Aneesh 5G";
const char* password = "praganchi@509";
WiFiUDP udp;

// defining i2c
#define I2C_SDA 15
#define I2C_SCL 14
// defining buttons
#define BUTTON_PIN_1 8
#define BUTTON_PIN_2 9
#define BUTTON_PIN_3 10
// display constants
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
// button states
byte lastButton1State = LOW;
byte lastButton2State = LOW;
byte lastButton3State = LOW;
// values for vibration
float direction_angletheta = 0;
float Sx = 0;
float Sy = 0;
float numbre = 1;
String direction;
String vibration_status;
// i2c defining for emulation
TwoWire I2Cbus = TwoWire(0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2Cbus, OLED_RESET);

#define Vibrationmotor1 4
#define Vibrationmotor2 5
#define Vibrationmotor3 6
#define Vibrationmotor4 7

void drawAxes()
{
  // Draw the axes and labels
  display.drawLine(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, SSD1306_WHITE); // X-axis
  display.drawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, SSD1306_WHITE);  // Y-axis
  display.setTextSize(1);                                                                 // Set text size
  display.setTextColor(SSD1306_WHITE);                                                    // Set text color
  display.setCursor(SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 - 10);                           // Adjust the position of X-axis label
  display.println("X");
  display.setCursor(SCREEN_WIDTH / 2 + 10, 5); // Adjust the position of Y-axis label
  display.println("Y");
}
 

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}




void setup()
{
    Serial.begin(115200);
    connectToWiFi();
    // i2c starting
    I2Cbus.begin(I2C_SDA, I2C_SCL, 100000);
    Serial.println("Initialize display");
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
      Serial.printf("SSD1306 OLED display failed to initalize.\nCheck that display SDA is connected to pin %d and SCL connected to pin %d\n", I2C_SDA, I2C_SCL);
      while (true)
        ;
    }
    // declaring pinmodes for buttons
    pinMode(BUTTON_PIN_1, INPUT);
    pinMode(BUTTON_PIN_1, INPUT);
    pinMode(BUTTON_PIN_1, INPUT);

    pinMode(Vibrationmotor1, OUTPUT);
    pinMode(Vibrationmotor2, OUTPUT);
    pinMode(Vibrationmotor3, OUTPUT);
    pinMode(Vibrationmotor4, OUTPUT);

    // testing display
    Serial.println("Hello World!");
    display.clearDisplay();

    drawAxes();
    display.display();
}
void loop()
{
    int packetSize = udp.parsePacket();
    if (packetSize) {
    char packetData[packetSize];
    udp.read(packetData, packetSize);
    packetData[packetSize] = 0; // Null-terminate the data
    
    // Parse received data and assign to variables
    sscanf(packetData, "Sx=%f,Sy=%f,direction_angletheta=%f", &Sx, &Sy, &direction_angletheta);
    }
    Determine(direction_angletheta);

    byte lastButton1State = digitalRead(BUTTON_PIN_1);
    byte lastButton2State = digitalRead(BUTTON_PIN_2);
    byte lastButton3State = digitalRead(BUTTON_PIN_3);

    if (digitalRead(BUTTON_PIN_1) == HIGH)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.print("Switching to Coordinate mode ");
      delay(1000);
      display.clearDisplay();
      
      while (digitalRead(BUTTON_PIN_1) != HIGH)
      {
        drawAxes();
        while (numbre < 5)
        {
          display.setCursor(Sx, Sy);
          display.print("·");
          delay(5);
          int packetSize = udp.parsePacket();
          if (packetSize) {
          char packetData[packetSize];
          udp.read(packetData, packetSize);
          packetData[packetSize] = 0; // Null-terminate the data
          scanf(packetData, "Sx=%f,Sy=%f,direction_angletheta=%f", &Sx, &Sy, &direction_angletheta);
          drawAxes();
          display.display();
          numbre = numbre + 1;
        }
        while (numbre == 6)
        {
          delay(2000);
          display.clearDisplay();
        }
      }
    }
    }

    if (digitalRead(BUTTON_PIN_2) == HIGH)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.print("Switching to S2T mode ");
      delay(1000);
      display.clearDisplay();
      while (digitalRead(BUTTON_PIN_1) != HIGH)
      {
        display.setCursor(0, 0);
        display.setTextSize(1);
        display.print("work in progress");
        display.display();
      }
    }

    if (digitalRead(BUTTON_PIN_3) == HIGH)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.print("Mode Switcher");
      delay(1000);
      display.display();
      display.clearDisplay();

      while (digitalRead(BUTTON_PIN_1) != LOW)
      {
        vibration_status = "Disabled";
      }

      while (digitalRead(BUTTON_PIN_2) != LOW)
      {
        vibration_status = "Enabled";
      }
    }

    if (direction == "NORTH")
    {
      digitalWrite(Vibrationmotor1, HIGH);
    }
    if (direction == "SOUTH")
    {
      digitalWrite(Vibrationmotor4, HIGH);
    }
    if (direction == "EAST")
    {
      digitalWrite(Vibrationmotor3, HIGH);
    }

    if (direction == "WEST")
    {
      digitalWrite(Vibrationmotor2, HIGH);
    }

    if (direction == "NORTHEAST")
    {
      if (Sx > Sy)
      {
        digitalWrite(Vibrationmotor3, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor1, HIGH);
      }
      if (Sy > Sx)
      {
        digitalWrite(Vibrationmotor1, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor3, HIGH);
      }
      if (Sx == Sy)
      {
        digitalWrite(Vibrationmotor3, HIGH);
        digitalWrite(Vibrationmotor1, HIGH);
      }
    }
    if (direction == "NORTHWEST")
    {
      if (Sx > Sy)
      {
        digitalWrite(Vibrationmotor2, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor1, HIGH);
      }
      if (Sy > Sx)
      {
        digitalWrite(Vibrationmotor1, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor2, HIGH);
      }
      if (Sx == Sy)
      {
        digitalWrite(Vibrationmotor2, HIGH);
        digitalWrite(Vibrationmotor1, HIGH);
      }
    }
    if (direction == "SOUTHEAST")
    {
      if (Sx > Sy)
      {
        digitalWrite(Vibrationmotor3, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor4, HIGH);
      }
      if (Sy > Sx)
      {
        digitalWrite(Vibrationmotor4, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor3, HIGH);
      }
      if (Sx == Sy)
      {
        digitalWrite(Vibrationmotor3, HIGH);
        digitalWrite(Vibrationmotor4, HIGH);
      }
    }
    if (direction == "SOUTHWEST")
    {
      if (Sx > Sy)
      {
        digitalWrite(Vibrationmotor2, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor4, HIGH);
      }
      if (Sy > Sx)
      {
        digitalWrit e(Vibrationmotor4, HIGH);
        delay(10);
        digitalWrite(Vibrationmotor2, HIGH);
      }
      if (Sx == Sy)
      {
        digitalWrite(Vibrationmotor2, HIGH);
        digitalWrite(Vibrationmotor4, HIGH);
      }
    }

    delay(50);
    
}
