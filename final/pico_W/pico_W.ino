#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
Adafruit_SSD1306 display(128, 64);

const int buttonPin = 16; // Define the pin for the button
int buttonState = 0; 


void setup() { 

pinMode(buttonPin, INPUT); 
Serial.begin(115200);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x32
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(1);
display.setCursor(0, 0);
display.println("on standby waiting to syncrhonise");
display.display();
Serial.println("lululuul");
delay(2000);

}

void loop() {
buttonState = digitalRead(buttonPin); // Read the state of the button
Serial.println(buttonState);
delay(200);
}