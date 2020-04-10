/*********
Liam Plybon
PinA0 -> AOut
PinA4 -> SDA
PinA5 -> SCL
PinGND -> GND
Pin5v -> Screen VCC
Pin3.3v -> Probe VCC
Serial Output as backup
*********/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h >
#include <Fonts/FreeSans12pt7b.h >

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int AirValue = 566;   //you need to replace this value with Value_1
const int WaterValue = 400;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.setFont(&FreeSans12pt7b);
  //display.println("Hello, world!");
  display.setFont(&FreeSans9pt7b);
  //display.println("Howdy, partner!");
  
  display.display(); 
}

void loop() {
soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
display.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent > 100)
{
  display.println("100 %");
}
else if(soilmoisturepercent <0)
{
  display.println("0 %");
}
else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
{
  display.print(soilmoisturepercent);
  display.println("%");
}
  delay(250);
  display.setCursor(40,18);
  display.print("Soil Hydr");
  display.display();
  delay(250);
  display.setCursor(0,18);
  display.clearDisplay();
}
