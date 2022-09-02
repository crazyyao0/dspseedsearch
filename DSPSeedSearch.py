import subprocess
import multiprocessing
import threading
import requests

def thread_function():
    while True:
        r = requests.get("http://10.103.73.21:31288/feed")
        batch = int(r.text)
        if batch <0:
            return
        output = subprocess.check_output(["/home/sysadmin/wyao/DSPSeedCalc", str(batch*65536), str(batch*65536 + 65536)])
        if output:
            requests.post("http://10.103.73.21:31288/found", data=output)

threads = []
for i in range(multiprocessing.cpu_count()):
    t = threading.Thread(target=thread_function)
    t.start()
    threads.append(t)
for t in threads:
    t.join()

