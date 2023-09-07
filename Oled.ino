#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
//#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
//#define SCREEN_ADDRESS 0x3C
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define IR_1 5
#define IR_2 6
#define IR_3 4
#define LED 8
// Declaration for SSD1306 display connected using software SPI:
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()
{
  pinMode (IR_1 , INPUT);
  pinMode (IR_2 , INPUT);
  pinMode (IR_3 , INPUT);
  pinMode (LED , OUTPUT);
  Serial.begin(9600);
  
  // initialize the OLED object
  //if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
   // Serial.println(F("SSD1306 allocation failed"));
   // for(;;); // Don't proceed, loop forever
 // }

  // Uncomment this if you are using SPI
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
  }

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Hello world!");
  display.display();
  delay(2000);
  display.clearDisplay();

}

void loop() {

    int sensorStatus_1 = digitalRead(IR_1);
    int sensorStatus_2 = digitalRead(IR_2);
    int sensorStatus_3 = digitalRead(IR_3);
    if (sensorStatus_1 == 1 || sensorStatus_2 == 1 || sensorStatus_3 == 1) // Check if the pin high or not
    {
      /*// if the pin is high turn off the onboard Led
      digitalWrite(LED, LOW); // LED LOW
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,28);
      display.println("Avilable Parking!");
      display.display();
      delay(500);
      display.clearDisplay();
      // print Motion Detected! on the serial monitor window
      */
      if (rf95.available())
    {
      // Should be a message for us now   
      uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf);
      if (rf95.recv(buf, &len))
      {
        digitalWrite(led, HIGH);
  //      RH_RF95::printBuffer("request: ", buf, len);
        Serial.print("got request: ");
        Serial.println((char*)buf);
//        Serial.print("RSSI: ");
//        Serial.println(rf95.lastRssi(), DEC);
      
        // Send a reply
        uint8_t data[] = "And hello back to you";
        rf95.send(data, sizeof(data));
        rf95.waitPacketSent();
        Serial.println("Sent a reply");
        digitalWrite(led, LOW);
      }
      else
      {
        Serial.println("recv failed");
      }
    }
        }
      else {
        digitalWrite(LED, HIGH);
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,28);
        display.println("No Parking!");
        display.display();
        delay(500);
        display.clearDisplay();

      if (rf95.available())
      {
      // Should be a message for us now   
      uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
      uint8_t len = sizeof(buf);
      if (rf95.recv(buf, &len))
      {
        digitalWrite(led, HIGH);
//        RH_RF95::printBuffer("request: ", buf, len);
        Serial.print("got request: ");
        Serial.println((char*)buf);
//        Serial.print("RSSI: ");
//        Serial.println(rf95.lastRssi(), DEC);
      
        // Send a reply
        uint8_t data[] = "And hello back to you";
        rf95.send(data, sizeof(data));
        rf95.waitPacketSent();
        Serial.println("Sent a reply");
        digitalWrite(led, LOW);
      }
      else
      {
        Serial.println("recv failed");
      }
    }
  }
}