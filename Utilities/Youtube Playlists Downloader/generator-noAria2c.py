import os

def manager():
    return '''import os, subprocess
import threading, time
from queue import PriorityQueue


n = [x for x in input().split()]
playlist_id = os.path.basename(__file__)
playlist_id = playlist_id[8:-4]
filz = []
exit_flag = 0


if len(n) == 1:
    s = int(n[0])
else:
    s = 5

def initialize():
    global filz

    l = 0
    os.chdir(playlist_id)
    if subprocess.run(['dir', '/b', '..*.bat'], shell=True, stderr=subprocess.PIPE,
                   stdout=subprocess.io.open("manager.txt", "w+")).stderr != b'':
        return 0
    with open('manager.txt', 'r') as f:
        filz = f.readlines()

    for l in range(len(filz[0])):
        if filz[0][l] == '-':
            break

    FFilz = []
    for fil in filz:
        FFilz.append(fil[2:l])
    filz = FFilz

    subprocess.run(['del', 'manager.txt'], shell=True)
    os.chdir('..')
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
                bat = playlist_id + '\\..' + fil + '-' + playlist_id + '-' + fil + '.bat'
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
    print('finished')'''

def ceil(x):
    if x-int(x)>0.000001:
        return int(x)+1
    return x

i = [x for x in input().split()]

def z(num):
    if num < 10:
        return 1
    return 1 + z(num/10)

def makeup(link):
    for c in range(len(link)):
        if c+4 < len(link) and link[c]=='l' and link[c+1]=='i' and link[c+2]=='s' and link[c+3]=='t' and link[c+4]=='=':
            link = link[c+5:]
            break

    for c in range(len(link)):
        if c+3 < len(link) and link[c]=='&' and link[c+1]=='i' and link[c+2]=='n' and link[c+3]=='d':
            link = link[:c]
            break
    return link


link=i[0]
num=1
quality=720

if len(i)==2:
    num=int(i[1])

l = z(num)

if len(i)==3:
    quality=int(i[2])

link = makeup(link)
# itr=1

if not os.path.exists(link):
    os.makedirs(link)
os.chdir(link)
if not os.path.exists(link):
	os.makedirs(link)
os.chdir(link)

for itr in range(1,1+num):
    with open('..'+str(itr).zfill(l)+'-'+link+'-'+str(itr).zfill(l)+'.bat',mode='w+') as f:
        f.write('youtube-dl.exe www.youtube.com/playlist?list='+link+' --playlist-items '+str(itr)+' -o '+str(itr).zfill(l)+'-%'+'%'+'(title)s.'+'%'+'%'+'(ext)s -f "best[ext=mp4][height<='+str(quality)+']"')
    if itr%10==0:
        with open('.'+link+'--'+str(int(ceil(itr/10))).zfill(l)+'.bat',mode='w+') as f:
            f.write('@ECHO OFF\n')
            for itritr in range(itr-10,itr):
                f.write('start /b '+'..'+str(itritr+1).zfill(l)+'-'+link+'-'+str(itritr+1).zfill(l)+'.bat\n')
    elif itr==num:
        with open('.'+link+'--'+str(int(ceil(itr/10))).zfill(l)+'.bat',mode='w+') as f:
            f.write('@ECHO OFF\n')
            for itritr in range(itr-itr%10,itr):
                f.write('start /b '+'..'+str(itritr+1).zfill(l)+'-'+link+'-'+str(itritr+1).zfill(l)+'.bat\n')

with open('.'+link+'--LIST.txt',mode='w+') as f:
    f.write('\n');

with open('.'+link+'..LIST.bat',mode='w+') as f:
    f.write('''youtube-dl --get-filename https://www.youtube.com/playlist?list=''' + link + ''' >> ''' + '.'+link+'--LIST.txt')

os.chdir('..')
with open('manager' + '-' + link + '-.py', 'w+') as f:
    f.write(manager())

with open('manager' + '-' + str(num) + '-' + link + '-' + '.mp44', 'w+') as f:
	f.write('')
