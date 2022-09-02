from flask import Flask, Response, request, make_response
import datetime
import logging
import threading
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

lock = threading.Lock()
target = 32768
current = 0
app = Flask(__name__)

@app.route('/feed')
def feed():
    global target
    global current
    print(datetime.datetime.now(), "Request:", request.remote_addr, current)
    if current >= target:
        response = make_response("-1")
    else:
        response = make_response("%d"%(current))
        current += 1
    return response
        
@app.route('/found', methods=["POST"])
def found():
    data = request.data
    with lock:
        with open('result.txt', 'a') as file:
            file.write(data.decode("utf-8"))
    print(data.decode("utf-8"))
    return make_response("OK")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=31288)
