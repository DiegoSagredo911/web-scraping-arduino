/*
conection pin

LCD  arduino

GND -> GND
vcc -> 5v
RS  -> D10
R/W -> D11
E   -> D3
PSb -> GND
RST -> D8
BLA -> 3.3V
CLK -> GND




*/

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

#define U8LOG_WIDTH 20
#define U8LOG_HEIGHT 8
uint8_t u8log_buffer[U8LOG_WIDTH*U8LOG_HEIGHT];
U8G2LOG u8g2log;

void setup(void) {

  Serial.begin(2000000);				
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tr);
  loading();

  
}

void loading(){
u8g2.clearDisplay();
  u8g2.setDisplayRotation(U8G2_R2);
  u8g2.setFlipMode(0);
  u8g2.firstPage();
  
  do {
    
    u8g2.drawStr(25, 15, "Bienvenido!!");



  } while (u8g2.nextPage());
}

void data(String dataig){
String array[50];
int r=0,t=0;
  
for(int i=0;i<dataig.length();i++)
{
  if(dataig[i] == '+')
  {
    if (i-r > 1)
    {
      array[t] = dataig.substring(r,i);
      t++;
    }
    r = (i+1);
  }
}



  Serial.print(dataig);
  u8g2.clearDisplay();
  u8g2.setDisplayRotation(U8G2_R2);
  u8g2.setFlipMode(0);
  u8g2.firstPage();
  do {
    
    u8g2.drawDisc(10,15, 9);
    u8g2.setCursor(25, 15);
    u8g2.print(array[0]);
    u8g2.setCursor(25, 27);
    u8g2.print(array[1]);
    u8g2.drawFrame(0, 32, 128, 32);
    u8g2.drawStr(4, 45, "Seguidores");
    u8g2.drawStr(72, 45, "Siguendo");
    u8g2.setCursor(4, 60);
    u8g2.print(array[2]);
    u8g2.setCursor(72, 60);
    u8g2.print(array[3]);

  } while (u8g2.nextPage());
}

void loop(void) {
  

  while (Serial.available() > 0) {
    data(Serial.readString());
  
  }
}
