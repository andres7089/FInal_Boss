import network
import config
import socket
import camera
import ubinascii
from time import sleep
from machine import Pin

led = Pin(2, Pin.OUT)


wifi = network.WLAN(network.STA_IF)
wifi.active(True)
wifi.connect(config.WIFI_SSID,config.WIFI_PASSWORD)

while not wifi.isconnected():
    pass

print("wifi connected")
    
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.1.4',65431))
#s.send(b'Hello')
sleep(0.1)

camera.init(0, format=camera.JPEG)
print('Camera init')
while True:
    try:    
        data = s.recv(1024)
        print(data)
        
        
        if data == b'ok':
            
            photo= camera.capture()
            encoded_photo = ubinascii.b2a_base64(photo)
            
            print(len(encoded_photo))
            s.send(encoded_photo)
    except:
        
        camera.deinit()