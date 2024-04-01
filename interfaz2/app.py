from flask import Flask
from flask import render_template
App = Flask(__name__)

@App.route("/")
@App.route("/<name>")
def home(name=None):
    return render_template('index.html',name=name)

if __name__ =="__main__":
    App.run(debug=True)