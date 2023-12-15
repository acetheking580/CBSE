#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


const int buttonPin = 23; // The pin where your button is connected
bool buttonState = LOW; // The current state of the button
bool lastButtonState = LOW; // The previous state of the button
unsigned long startTime = 0; 

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

void setup() {

pinMode(buttonPin, INPUT_PULLUP);
Serial.begin(9600);

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);

  display.println("Hello, world!");
  display.display();
  delay(10000);
  display.clearDisplay();
  display.display();

}

void loop() {

buttonState = digitalRead(buttonPin); // Read the state of the button

display.print("main menu");

  // Check if the button state has changed
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) { // Button is pressed
      startTime = millis(); // Record the start time of the button press
    } else { // Button is released
      unsigned long pressDuration = millis() - startTime; // Calculate the duration of the button press
      if (pressDuration > 400) { // If button was held for more than 0.4 seconds
        // Perform the action you want here
        Serial.println("Button held for more than 0.4 seconds");
      }
    }
  }

  lastButtonState = buttonState;

}


