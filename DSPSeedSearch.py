import subprocess
import multiprocessing
import threading
import requests

FeedServer = "http://10.103.73.21:31288/"

def thread_function():
    while True:
        r = requests.get(FeedServer + "feed")
        batch = int(r.text)
        if batch <0:
            return
        output = subprocess.check_output(["DSPSeedCalc", str(batch*65536), str(batch*65536 + 65536)])
        if output:
            requests.post(FeedServer + "found", data=output)

threads = []
for i in range(multiprocessing.cpu_count()):
    t = threading.Thread(target=thread_function)
    t.start()
    threads.append(t)
for t in threads:
    t.join()

