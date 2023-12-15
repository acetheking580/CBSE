#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


bool buttonState(int buttonPin) {
    pinMode(buttonPin, INPUT_PULLUP); 
    return digitalRead(buttonPin) == LOW; 
}

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
void getsxsy(){
  sx=x;
  sy=Y;
}


void button1(){

display.clearDisplay();
drawAxes();
display.display();
display.print("switching to coordinate mode ")
delay(750);
 while (!buttonState(buttonpin1)) {
        DrawAxes();  
        display.setCursor(Sx,Sy);
        delay(600); 
        getsxsy();
        x1=Sx;
        y1=Sy;
        display.setCursor(Sx,Sy);
        display.print(".")
        delay(150); 
        display.clearDisplay();
        display.setCursor(x1,y1);
        display.print(".")
        delay(600);
    }
}

void texttospeech(){

display.print("STT mode !");
delay(1500);
while (!buttonState(buttonpin2)) {
       display.print("recording....");
       display.display();
       delay(1400);
       display.clearDisplay();
       display.print("proccessing..");
       display.display();
       delay(700);
       display.print("its taking longer than expected");
       display.display();
       delay(700);
       display.clearDisplay();
       display.print("404 Api down ")
       display.display
    }

}

void backrooms(){

while (!buttonState(buttonpin5)){
  
  if (backy=0){
    Serial.print("abe salle pahle bakcy tho set kar na");
  }

 if (backy=1){
  digitalWrite(ledPin1,LOW);
  delay(100);
  digitalWrite(ledPin1,HIGH;)
  delay(1050);
  digitalWrite(ledPin3,HIGH);
  delay(150);
  digitalWrite(ledPin1,LOW);
  delay(300)
  digitalWrite(ledPin4,HIGH);
  delay(1600);
  digitalWrite(ledPin3,LOW);
  delay(300);
  digitalWrite(ledPin2,HIGH);
  delay(750);
  digitalWrite(ledPin4,LOW);
  delay(600);

  digitalWrite(ledPin2,LOW);

  digitalWrite(ledPin1,LOW);
  digitalWrite(ledPin2,LOW);
  digitalWrite(ledPin3,LOW);
  digitalWrite(ledPin4,LOW);
  delay(1500);
 }

if (backy=2){
  digitalWrite(ledpin2,HIGH);
  digitalWrite(ledPin4,HIGH);
  digitalWrite(ledpin3,HIGH);
  digitalWrite(ledpin1,HIGH)
}

}
}
void setup() {
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

 if (digitalRead((buttonpin4)=HIGH){
  backy=backy+1;
 }

  

}
