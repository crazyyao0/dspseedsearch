import subprocess
import multiprocessing
import threading
import requests
import os

FeedServer = "http://10.103.73.21:31288/"

def thread_function():
    while True:
        r = requests.get(FeedServer + "feed")
        batch = r.json()
        if not batch:
            return
        
        output = subprocess.check_output([os.getcwd() + "/DSPSeedCalc", str(batch[0]), str(batch[1]), str(batch[2])])
        if output:
            requests.post(FeedServer + "found", data=output)

threads = []
for i in range(multiprocessing.cpu_count()):
    t = threading.Thread(target=thread_function)
    t.start()
    threads.append(t)
for t in threads:
    t.join()

