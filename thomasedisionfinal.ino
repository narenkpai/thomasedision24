// Include the Servo library 
#include <Servo.h> 
#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

// Declare the Servo pin 
int servoPin1 = 3;
int servoPin2 = 5;
int servoPin3 = 6;
int servoPin4 = 9;
Servo Servo1; 
Servo Servo2; 
Servo Servo3; 
Servo Servo4; 
const int inter_time = 1000;

const int TRIGGER_PIN = A0;
const int ECHO_PIN = A1;

int button1 = 2;
int button2 = 4;

int bottleTotal = 0;
int i = 0;
int timeLeft = 10;
// Define variables for timing
unsigned long previousMillis = 0;
const long interval = 1000; // 1 second interval
// Create a servo object 
void setup() { 
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Turn builtin LED off
  digitalWrite(LED_BUILTIN, LOW);
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2); 
  Servo3.attach(servoPin3); 
  Servo4.attach(servoPin4); 
  pinMode (TRIGGER_PIN, OUTPUT);
  pinMode (ECHO_PIN, INPUT);

  

     Config_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  LCD_SetBacklight(1000);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_SetRotate(180);
  //Paint_DrawPoint(2,2, BLACK, DOT_PIXEL_1X1,  DOT_FILL_RIGHTUP);//240 240
  //Paint_DrawLine( 95,   5,  95, 35, CYAN, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
  //Paint_DrawRectangle(40, 0, 0, 100, GREEN, DOT_PIXEL_4X4,DRAW_FILL_FULL);
  //Paint_DrawCircle(130, 20, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(1, 1, "Current number of bottles:", &Font16, 0xFFFF, 0x0000);
  Paint_DrawNum  (60, 37 ,bottleTotal,  &Font16,    0xFFFF,   0x000f);
  Paint_DrawString_EN(1, 50, "Load Water Bottle?", &Font20, 0xFFFF, 0x0000);
 // Paint_DrawImage(gImage_40X40, 50, 50, 40, 40); 
  Paint_DrawCircle(20, 110, 15, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(15, 106, "NO", &Font8, 0xFFFF, 0x0000);
  Paint_DrawCircle(118, 110, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
  Paint_DrawString_EN(110, 105, "YES", &Font8, 0xFFFF, 0x0000);
}
void loop(){ 
  unsigned long duration;
  float distance;
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn (ECHO_PIN, HIGH);
  Serial.println(duration);
  distance = (duration / 2.0) / 29.0;
  Serial.print(distance);
  Serial.println(" cm");
  delay(inter_time);

  if(distance - 2000 < 50 && distance - 2000 > -2050 ){
    bottleTotal++;
    Serial.println(bottleTotal);
    Paint_DrawCircle(69, 43, 12, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawNum  (60, 37 ,bottleTotal,  &Font16,    0xFFFF,   0x000f);
  }
    if(digitalRead(2) == HIGH) {
      moveServo();
      Serial.println("Move Servo");
      delay(10000);

    } else {
      digitalWrite(LED_BUILTIN, LOW);
            Serial.println("not Move Servo");
    }


  }
 
 void moveServo(){
    LCD_Clear(WHITE);
    Paint_DrawString_EN(1, 1, "Please Input Water Bottle", &Font16, 0xFFFF, 0x0000);
    Paint_DrawString_EN(1, 50, "Time Left:", &Font20, 0xFFFF, 0x0000);
    while(timeLeft > 0){
    unsigned long currentMillis = millis();

  // Check if 1 second has passed
     if (currentMillis - previousMillis >= interval) {
    // Save the last time you blinked the LED
    previousMillis = currentMillis;

    // Decrease the variable by 1
    timeLeft--;
    Serial.println(timeLeft);

    Paint_DrawCircle(60, 37, 12, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawNum  (60, 37 ,timeLeft,  &Font16,    0xFFFF,   0x000f);
     }
    }
    Servo1.write(0);
    delay(1000);
    Servo2.write(90); 
    delay(1000);
    Servo3.write(180); 
    delay(1000);
    Servo4.write(0);  
    delay(1000);
    Servo1.write(90);
    delay(1000);
    Servo2.write(180); 
    delay(1000);
    Servo3.write(90); 
    delay(1000);
    Servo4.write(120);  
    delay(1000);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(1, 1, "Current number of bottles:", &Font16, 0xFFFF, 0x0000);
    Paint_DrawNum  (60, 37 ,bottleTotal,  &Font16,    0xFFFF,   0x000f);
    Paint_DrawString_EN(1, 50, "Load Water Bottle?", &Font20, 0xFFFF, 0x0000);
    Paint_DrawCircle(20, 110, 15, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(15, 106, "NO", &Font8, 0xFFFF, 0x0000);
    Paint_DrawCircle(118, 110, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(110, 105, "YES", &Font8, 0xFFFF, 0x0000);
    timeLeft = 10;
 }
 
