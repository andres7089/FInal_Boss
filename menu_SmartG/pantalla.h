#include <Arduino.h>

class Pantalla: public Stream {
  
  private:
  const char* data;

  public:

     int available() {};
     int read() {};
     int peek() {};
     void begin();

     void Borrar();
    void Refrescar();
    void setCursor(int16_t x, int16_t y);
 
    virtual size_t write(uint8_t data);
  
};
