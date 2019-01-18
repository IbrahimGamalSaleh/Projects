import os, subprocess
import threading, time
from queue import PriorityQueue


n = [x for x in input().split()]
playlist_id = ''
filz = []
exit_flag = 0


if len(n) == 1:
    s = int(n[0])
else:
    s = 5

def initialize():
    global filz
    global playlist_id
    l = 0

    if subprocess.run(['dir', '/b', '..*.bat'], shell=True, stderr=subprocess.PIPE,
                   stdout=subprocess.io.open("manager.txt", "w+")).stderr != b'':
        return 0

    with open('manager.txt', 'r') as f:
        filz = f.readlines()

    for l in range(len(filz[0])):
        if filz[0][l] == '-':
            break

    l-=3
    playlist_id = filz[0][2+l+1+1:-7-l]

    FFilz = []
    for fil in filz:
        FFilz.append(fil[2:2+l+1])
    filz = FFilz

    subprocess.run(['del', 'manager.txt'], shell=True)
    return 1

class Scheduler(threading.Thread):
    def __init__(self, q):
        threading.Thread.__init__(self)
        self.q = q
    def run(self):
        download_a_file(self.q)

def download_a_file(q):
    while not exit_flag:
        queueLock.acquire()
        fil = ''
        bat = 'noting'
        if not q.empty():
            fil = q.get()
            if subprocess.run(['dir', '/b', fil+'*mp4'], shell=True, stderr=subprocess.PIPE).stderr != b'':
                bat = '..' + fil + '-' + playlist_id + '-' + fil + '.bat'
            queueLock.release()
            time.sleep(.1)
            if bat != 'noting':
                try:
                    print('downloading file '+fil)
                    subprocess.run([bat])
                except Exception as e:
                    print('Something wrong while downloading file '+fil)
                    print(e)
            if subprocess.run(['dir', '/b', fil+'*mp4'], shell=True, stderr=subprocess.PIPE).stderr != b'':
                queueLock.acquire()
                q.put(fil)
                queueLock.release()

        else:
            queueLock.release()
            time.sleep(.1)


if initialize():
    queueLock = threading.Lock()
    downloads_queue = PriorityQueue(len(filz))
    schedulers = []

    for i in range(s):
        scheduler = Scheduler(downloads_queue)
        scheduler.start()
        schedulers.append(scheduler)

    queueLock.acquire()
    for fil in filz:
        downloads_queue.put(fil)
    queueLock.release()

    while not downloads_queue.empty():
        pass

    exit_flag = 1

    for scheduler in schedulers:
        scheduler.join()
    print('finished')