#include "pantalla.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define ANCHO_PANTALLA 128 
#define ALTO_PANTALLA 64 
#define OLED_RESET     -1

 Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, OLED_RESET);

void Pantalla::begin(){
      
      
       if(!display.begin(SSD1306_SWITCHCAPVCC,0X3C)) {
       Serial.println(F("No se pudo iniciar la pantalla OLED"));
      return; 
     }

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  
  display.clearDisplay();
  display.display();       

   
    }

    size_t Pantalla::write(uint8_t data){
      display.write(data); 
      display.display(); 
   
      return 1;
    }

    void Pantalla::Borrar()
    {
        display.clearDisplay();
    }

    void Pantalla::Refrescar()
    {
        display.setCursor(0, 0);
        display.display();
    } 


    void Pantalla::setCursor(int16_t x, int16_t y)
    {
      display.fillRect(x, y, ANCHO_PANTALLA, ALTO_PANTALLA , SSD1306_BLACK);
      display.setCursor(x,y);
    }


