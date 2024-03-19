from machine import Pin, I2C, Timer
from time import sleep, ticks_ms
from Menu import Menu
import ssd1306
import random
import time


i2c = I2C(0, scl=Pin(22), sda=Pin(21))

oled_width = 128
oled_height = 64
oled = ssd1306.SSD1306_I2C(oled_width, oled_height, i2c)


bOption0 = True


def opcion0():
    global bOption0
   
    if bOption0:
        temperatura()
        oled.fill(0)  
        oled.text("crono:", 0, 0)  
        oled.show() 
    else:
        bOption0 = not bOption0
    

def opcion1():
    led1.value(not led1.value())  
    cronometro()
    print("opcion_1")

def opcion2():
    led2.value(not led2.value())  
    print("opcion_2")


menu = Menu()


menu.add_item("opcion 0", opcion0)
menu.add_item("opcion 1", opcion1)
menu.add_item("opcion 2", opcion2)

led0 = Pin(2, Pin.OUT)
led1 = Pin(5, Pin.OUT)
led2 = Pin(15, Pin.OUT)

btnUp = Pin(27, Pin.IN, Pin.PULL_UP)
btndown = Pin(14, Pin.IN, Pin.PULL_UP)
btnenter = Pin(26, Pin.IN, Pin.PULL_UP)

last_time = 0

def up(pin):
    global last_time
    if ticks_ms() - last_time > 500:
        menu.Up()
        last_time = ticks_ms()

def down(pin):
    global last_time
    if ticks_ms() - last_time > 500:
        menu.down()
        last_time = ticks_ms()

def enter(pin):
    global last_time
    if ticks_ms() - last_time > 500:
        menu.enter()
        last_time = ticks_ms()

btnUp.irq(up, Pin.IRQ_FALLING)
btndown.irq(down, Pin.IRQ_FALLING)
btnenter.irq(enter, Pin.IRQ_FALLING)

tim0 = Timer(0)

def blinkLed0():
    #temperatura()
    pass

tim0.init(mode=Timer.PERIODIC,period=100,callback=lambda t: temperatura())
tim0.deinit()

def temperatura():
    grados = random.randint(0, 240)  
    texto = f"{grados}C"
    oled.text('temp:', 0, 0) 
    oled.text(texto, 33, 0)  
    oled.show()  
    oled.fill(0)

def cronometro():
    tiempo_inicio = time.time()

    while True:
        tiempo_transcurrido = time.time() - tiempo_inicio
        horas = int(tiempo_transcurrido // 3600)
        minutos = int((tiempo_transcurrido % 3600) // 60)
        segundos = int(tiempo_transcurrido % 60)

        tiempo_formateado = "{:02d}:{:02d}.{:02d}".format(horas, minutos, segundos)

        oled.text('crono:',0,0)
        oled.text(tiempo_formateado,45,0)
        oled.show()  
        oled.fill(0)



