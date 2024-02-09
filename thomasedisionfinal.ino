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

const int TRIGGER_PIN = A0;
const int ECHO_PIN = A1;

int button1 = 2;
int button2 = 4;

int bottleTotal = 0;
int i = 0;
// Create a servo object 
Servo Servo1; 
void setup() { 
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(4, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Turn builtin LED off
  digitalWrite(LED_BUILTIN, LOW);
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin1); 

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
  Paint_DrawCircle(120, 110, 15, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
}
void loop(){ 
   // Make servo go to 0 degrees 
   if(digitalRead(4) == HIGH) {
    digitalWrite(LED_BUILTIN, HIGH);
    
    i = 1;
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    i = 0;
  }

  if(i = 1){
    delay(100);
    Servo1.write(0); 
    delay(1000); 
    Servo1.write(90); 
    delay(1000); 
    Servo1.write(180); 
    delay(1000); 
    Serial.write("on");
    i = 0;
  }

 
}