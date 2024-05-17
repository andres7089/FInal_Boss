from flask import Flask, request
from flask import render_template,jsonify
import serial
import socket
import base64
import json

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(('0.0.0.0',65431))
s.listen()

client, address = s.accept()    
    
app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')


@app.post('/pedirImagen')
def pedirImagen():
    
        #data = request.get_json()
        #print(data)
        #client.send(data.encode())
        client.send(b'ok')
        data = client.recv(32000)
        
        return{'response':data.decode()}
    
        

    

if __name__ == "__main__":
    app.run(debug=False,host='0.0.0.0')

    
    


