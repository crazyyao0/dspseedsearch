from flask import Flask, Response, request, make_response
import datetime
import logging
import threading
log = logging.getLogger('werkzeug')
log.setLevel(logging.ERROR)

lock = threading.Lock()
app = Flask(__name__)
tasks = [[j*100000, j*100000+100000, i] for i in range(32,65) for j in range(1000)]
current = 0
target = 33000

@app.route('/feed')
def feed():
    global current
    if current >= target:
        response = make_response("false")
    else:
        response = make_response(str(tasks[current]))
        print(datetime.datetime.now(), "Request:", request.remote_addr, str(tasks[current]))
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
