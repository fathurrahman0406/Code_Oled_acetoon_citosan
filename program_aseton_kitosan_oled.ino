
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
#define buz 13
Adafruit_ADS1115 ads;
#define push A2
float ase;
 int state=0;
 int counter;
 float rs;
 float y;

 #include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


float volt;
float aseton;

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
  
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(45,0);
    display.println("Wellcome");
    display.setCursor(25,10);
    display.println("Diabetes Sensor");
    display.setCursor(38,25);
    display.println("Fisika USU");
    display.display();
    delay(4000);
    display.clearDisplay();


    testdrawline();
    display.display();
    delay(2000);
    display.clearDisplay();

    
    pinMode(push,INPUT);
    digitalWrite(push, HIGH);
    Serial.begin(9600);
    mySerial.begin(9600);
    ads.setGain(GAIN_FOUR);
    ads.begin();
    pinMode(buz,OUTPUT);
   }

void loop() {
   while(state==0){           //recoveri
      int16_t results;
      float multiplier = 0.03125;
      results = ads.readADC_Differential_2_3();
      volt = results*multiplier;
      aseton = ((analogRead(A1)*0.004887*1000)/2);
     //aseton = (analogRead(A1)*0.004887);
     // rs=((5/aseton)-1)*1000;
     // ase=rs;
      
      
      
      if (volt>70){digitalWrite(buz,HIGH); delay(10);digitalWrite(buz,LOW);delay(400);}
      if(digitalRead(push)==0){state=1;delay(200);}
   
        Serial.print("DATA");
        Serial.print(",");
        Serial.print("TIME");
        Serial.print(",");
        Serial.print(volt);
        Serial.print(",");
        Serial.println(aseton);
//        Serial.print(",");
//        Serial.println(ase);

        mySerial.print("Citosan = ");
        mySerial.print(volt);
        mySerial.print("        Asetoon = ");
        mySerial.println(aseton);

        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(0,0);
        display.print("Aseton  = ");
        display.print(aseton);
        display.println(" mV");
        display.setCursor(0,10);
        display.print("Citosan = ");
        display.print(volt);
        display.println(" mV");
        display.setTextSize(1.7);
        display.setCursor(38,23);
        display.println("Recovery");
        display.display();
        delay(100);
        display.clearDisplay();


while (state==1){             //tiup
    display.setTextColor(WHITE);
    display.setTextSize(3);
    display.setCursor(35,10);
    display.println("TIUP");
    display.display();
    digitalWrite(buz,HIGH);
    delay(4000);
    digitalWrite(buz,LOW);
    display.clearDisplay();
    state=2;
 }

while (state==2){             //ambil data
    int16_t results;
    float multiplier = 0.03125;
    results = ads.readADC_Differential_2_3();
    volt = results*multiplier;
    aseton = ((analogRead(A1)*0.004887*1000)/2);
    //aseton = (analogRead(A1)*0.004887*1000);
  
        Serial.print("DATA");
        Serial.print(",");
        Serial.print("TIME");
        Serial.print(",");
        Serial.print(volt);
        Serial.print(",");
        Serial.println(aseton);

        mySerial.print("E");
        mySerial.print(volt);
        mySerial.print(",");
        mySerial.println(aseton);


        display.setTextColor(WHITE);
        display.setTextSize(1);
        display.setCursor(0,0);
        display.print("Aseton  = ");
        display.print(aseton);
        display.println(" mV");
        display.setCursor(0,10);
        display.print("Citosan = ");
        display.print(volt);
        display.println(" mV");
        display.setTextSize(1.7);
        display.setCursor(38,23);
        display.println("Results");
        display.display();
        delay(500);
        display.clearDisplay();

        
        if(digitalRead(push)==0)
        {
          display.setTextColor(WHITE);
          display.setTextSize(2);
          display.setCursor(0,0);
          display.println("Recovery");
          display.println("Mode");
          display.display();
          digitalWrite(buz,HIGH);
          delay(100);
          digitalWrite(buz,LOW);
          delay(3000);
          display.clearDisplay();
          state=0;
          
          } 
  }
 }
}

















void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random(display.width());
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random(5) + 1;
    
    Serial.print("x: ");
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(" y: ");
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(" dy: ");
    Serial.println(icons[f][DELTAY], DEC);
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }
    display.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, BLACK);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > display.height()) {
        icons[f][XPOS] = random(display.width());
        icons[f][YPOS] = 0;
        icons[f][DELTAY] = random(5) + 1;
      }
    }
   }
}


void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    if ((i > 0) && (i % 21 == 0))
      display.println();
  }    
  display.display();
  delay(1);
}

void testdrawcircle(void) {
  for (int16_t i=0; i<display.height(); i+=2) {
    display.drawCircle(display.width()/2, display.height()/2, i, WHITE);
    display.display();
    delay(1);
  }
}

void testfillrect(void) {
  uint8_t color = 1;
  for (int16_t i=0; i<display.height()/2; i+=3) {
    // alternate colors
    display.fillRect(i, i, display.width()-i*2, display.height()-i*2, color%2);
    display.display();
    delay(1);
    color++;
  }
}

void testdrawtriangle(void) {
  for (int16_t i=0; i<min(display.width(),display.height())/2; i+=5) {
    display.drawTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    display.display();
    delay(1);
  }
}

void testfilltriangle(void) {
  uint8_t color = WHITE;
  for (int16_t i=min(display.width(),display.height())/2; i>0; i-=5) {
    display.fillTriangle(display.width()/2, display.height()/2-i,
                     display.width()/2-i, display.height()/2+i,
                     display.width()/2+i, display.height()/2+i, WHITE);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}

void testdrawroundrect(void) {
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, WHITE);
    display.display();
    delay(1);
  }
}

void testfillroundrect(void) {
  uint8_t color = WHITE;
  for (int16_t i=0; i<display.height()/2-2; i+=2) {
    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i, display.height()/4, color);
    if (color == WHITE) color = BLACK;
    else color = WHITE;
    display.display();
    delay(1);
  }
}
   
void testdrawrect(void) {
  for (int16_t i=0; i<display.height()/2; i+=2) {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display();
    delay(1);
  }
}

void testdrawline() {  
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(0, 0, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(0, display.height()-1, display.width()-1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);
  
  display.clearDisplay();
  for (int16_t i=display.width()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, i, 0, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=display.height()-1; i>=0; i-=4) {
    display.drawLine(display.width()-1, display.height()-1, 0, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);

  display.clearDisplay();
  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, WHITE);
    display.display();
    delay(1);
  }
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(display.width()-1, 0, i, display.height()-1, WHITE); 
    display.display();
    delay(1);
  }
  delay(250);
}


void testscrolltext(void) {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.clearDisplay();
  display.println("scroll");
  display.display();
  delay(1);
 
  display.startscrollright(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
}
    


