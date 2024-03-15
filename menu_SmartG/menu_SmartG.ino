#include "Menu.h"
#include "pantalla.h"

Menu menu;
Pantalla pantalla; 
  volatile unsigned long b ;
  volatile unsigned long lastTime = 0;
  volatile boolean bUp,bDown,bEnter;
  volatile boolean enter_esc;
  volatile boolean bOption0= true;
  volatile boolean bOption1 = true;
  volatile boolean bOption2 = true;
  volatile boolean bTime, bTemp,bHora    = false;
  unsigned long startTime   = 0;
 
  hw_timer_t *timer = NULL;
  hw_timer_t *timer1 = NULL;
  hw_timer_t *timer2 = NULL;

void setup() {


   Serial.begin(115200);

  pantalla.begin();
  
  menu.begin(pantalla);

  menu.addItem("option0",option0);// put your setup code here, to run once:
  menu.addItem("option1",option1);
  menu.addItem("option2",option2);

  pinMode(15,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);

  pinMode(14,INPUT_PULLUP);
  pinMode(27,INPUT_PULLUP);
  pinMode(26,INPUT_PULLUP);

  attachInterrupt(14,enter,FALLING);
  attachInterrupt(27,up,FALLING);
  attachInterrupt(26,down,FALLING);
   
  bUp = bDown=bEnter=false;

  timer = timerBegin(0,80,true);
  timerAttachInterrupt(timer,blink,true);
  timerAlarmWrite(timer,1000000,true);
  timerAlarmEnable(timer);

  timerRestart(timer);
  timerStart(timer);
  timerStop(timer);

  timer1 = timerBegin(1,80,true);
  timerAttachInterrupt(timer1,temp,true);
  timerAlarmWrite(timer1,100000,true);
  timerAlarmEnable(timer1);

  timerRestart(timer1);
  timerStart(timer1);
  timerStop(timer1);

  timer2 = timerBegin(2,80,true);
  timerAttachInterrupt(timer2,hours,true);
  timerAlarmWrite(timer2,10000,true);
  timerAlarmEnable(timer2);

  timerRestart(timer2);
  timerStart(timer2);
  timerStop(timer2);

 }


void ARDUINO_ISR_ATTR blink ()
{
  bTime = true;
}

void ARDUINO_ISR_ATTR temp ()
{
  bTemp = true;
}

void ARDUINO_ISR_ATTR hours ()
{
  bHora = true;
}


void loop() {
   

  if(bTime){

    pantalla.Refrescar();
    runStopwatchOnOLED();
    
    bTime = false;
  }

  if(bTemp){
    
    temperatura();
    pantalla.Refrescar();
    
      
    bTemp = false;
  }

  if(bHora){

    pantalla.Refrescar();
    mostrarHoraAleatoria();  

    bHora= false;
  }

  if(bUp){
  pantalla.Borrar();
  pantalla.Refrescar();
    menu.up();
    bUp = false;
   }

   if(bDown){ 
   pantalla.Borrar();
   pantalla.Refrescar();
    menu.down();
    bDown = false;
   }

   if(bEnter){
    menu.enter();
    bEnter = false;
   }

}

void ARDUINO_ISR_ATTR enter(){
 
  if((millis()-lastTime)>300){
  bEnter = true;
  lastTime = millis();   
   }
  }
  
void ARDUINO_ISR_ATTR  up(){
if((millis()-lastTime)>300){
  bUp = true;
  lastTime = millis();
   }
  }

void ARDUINO_ISR_ATTR  down(){
if((millis()-lastTime)>300){
  bDown = true;
  lastTime = millis();
    }
  }

void option0()
{

  if(bOption0){
  timerRestart(timer);
  timerStart(timer);
  blink();
  pantalla.Borrar(); 
  pantalla.setCursor(0, 0);
  pantalla.print("crono:");
  }else{
  timerStop(timer);
  }
  bOption0 = !bOption0;
  

}

void option1()
{
  if(bOption1){
  timerRestart(timer1);
  timerStart(timer1);
  temp();
  pantalla.Borrar(); 
  pantalla.setCursor(0, 0);
  pantalla.print("temp:");
  }else{
  timerStop(timer1);
  }
  bOption1 = !bOption1;
  
}


void option2(){

  if(bOption2){
  timerRestart(timer2);
  timerStart(timer2);
  hours();
  pantalla.Borrar(); 
  pantalla.setCursor(0, 0);
  pantalla.print("Hora:");
  }else{
  timerStop(timer2);
  }
  bOption2 = !bOption2;

}

void mostrarHoraAleatoria() 
{
  uint8_t horas = random(0, 24);
  uint8_t minutos = random(0, 60);
  uint8_t segundos = random(0, 60);

  pantalla.setCursor(50, 0);
  pantalla.print("       ");
  (horas < 10) ? pantalla.print("0") : 0;
  pantalla.setCursor(55, 0);
  pantalla.print(horas);
  pantalla.print(":");
  (minutos < 10) ? pantalla.print("0") : 0;
  pantalla.print(minutos);

  pantalla.Borrar(); 
}

void temperatura() 
{
  uint8_t grados  = random(0, 240);
  
  pantalla.setCursor(50, 0);
  pantalla.print("       ");
  pantalla.setCursor(55, 0);
  pantalla.print(grados);
  pantalla.print("C");
  //pantalla.Refrescar(); 
  
}



void runStopwatchOnOLED() {
    

  unsigned long elapsedTime = millis() - startTime;
  unsigned long minutes = elapsedTime / (60 * 1000);
  unsigned long seconds = (elapsedTime / 1000) % 60;
  unsigned long milliseconds = elapsedTime % 1000;

  pantalla.setCursor(0, 15); 
  pantalla.print(minutes);
  pantalla.print(":");
  if (seconds < 10) pantalla.print("0");
  pantalla.print(seconds);
  pantalla.print(".");
  if (milliseconds < 100) pantalla.print("0");
  if (milliseconds < 10) pantalla.print("0");
  pantalla.print(milliseconds);
  pantalla.Borrar();
}

void startTimer() {
  startTime = millis();
}

void stopTimer() {
  startTime = 0;
}
