import sys

v = int(sys.version[0])

Main = ''
Menu = ''
Status = ''
root = ''
Welcome = ''
Ok = ''
Path = ''
InputPath = '' # 'C:\\Users\\Youssof_El-Kilaney\\Desktop\\test\\test.txt'
OutputPath = '' # 'C:\\Users\\Youssof_El-Kilaney\\Desktop\\test\\outputtest.txt'
Ways = ''
execution = ''
optionz = ['Read file', 'Binary Search', 'Merge sort', 'Quick Sort', 'Heap Sort', 'Count Sort', 'Disclaimer']

def __read_file__():
    reading = ''
    try:
        if v==2:
            if InputPath != '':
                Fayl = file(InputPath, 'r')
                reading = Fayl.read()
            else:
                Fayl = file('D:\input.txt', 'r')
                reading = Fayl.read()
        elif v==3:
            if InputPath != '':
                with open(InputPath, 'r') as F:
                    for line in iter(F.readline, ''):
                        reading += line
            else:            
                with open('D:\input.txt', 'r') as F:
                    for line in iter(F.readline, ''):
                        reading += line
        reading = reading.strip()
        if reading.__len__ == 0:
            if v==2:
                msgbx.showinfo("Empty File", "No Contents in this file")
            elif v==3:
                tkinter.messagebox.showinfo("Empty File", "No Contents in this file")
            return False
    except:
        err = "Input file not found, please select a file with a proper path"
        if v==2:
            msgbx.showinfo("File not found", err)
        elif v==3:
            tkinter.messagebox.showinfo("File not found", err)
        return False
    return reading


def __read_file():
    reading = __read_file__()
    if reading:
        print(reading)
        if v==2:
            msgbx.showinfo("input file read", reading)
        elif v==3:
            tkinter.messagebox.showinfo("input file read", reading)
    else:
        return


def __write_file__(reading, name=''):
    try:
        if v==2:
            Fayl = file('D:\output.txt', 'w')
            if name != '':
                Fayl = file(name, 'w')
            Fayl.write(reading)
        elif v==3:
            if name != '':
                with open(name, 'w') as F:
                    print(reading, file=F)
            else:
                with open('D:\output.txt', 'w') as F:
                    print(reading, file=F)
    except:
        err = "application could not create/write the output file"
        if v==2:
            msgbx.showinfo('Failed output', err)
        elif v==3:
            tkinter.messagebox.showinfo('Failed output', err)
        return False
    return True


def __parse__inputs__(nums):
    numms = []
    idx=0
    t=0
    
    for n in nums:
        t += 1
        try :
            numms.append(int(n))
            idx += 1
        except:
            pass

    if idx == 0:
        if v==2:
            msgbx.showinfo('bad input', 'application could not parse file inputs')
        elif v==3:
            tkinter.messagebox.showinfo('bad input', 'application could not parse file inputs')
        return False
    elif idx != t:
        if v==2:
            msgbx.showinfo('incomplete input', 'application could not parse all file inputs')
        elif v==3:
            tkinter.messagebox.showinfo('incomplete input', 'application could not parse all file inputs')
    return numms


def prepare():
    nums = __read_file__()
    m = []
    if nums:
        nums = nums.split(',')
        if nums.__len__() == 1:
            nums = nums[0].split()
        # for n in nums:
        #     try:
        #         n = n.split()[0]
        #     except:
        #         m += n.split()
        # for x in m:
        #     nums += x
    else:
        return False

    nums = __parse__inputs__(nums)
    return nums

def __binary_search(key=0):
    __manual()

    nums = prepare()

    if nums == False:
        return
    
    key = ''
    while key == '':
        s = ''
        if v==2:
            s = tkSimpleDialog.askstring("key", "Enter key to search for")
        elif v==3:
            s = tkinter.simpledialog.askstring("key", "Enter key to search for")
        if s == '' or s is 'NoneType':
            continue
        try:
            key = int(s)
        except:
            continue

    t1 = datetime.datetime.now()
    nums = __merge_sort__(nums)

    l=0
    r=nums.__len__()-1
    b=True

    while l<=r:
        mid = int(l + (r-l)/2);
        if nums[mid] == key:
            t2 = datetime.datetime.now()
            b=False
            if v == 2:
                msgbx.showinfo('key found! :)', 'key found at index ' + str(mid))
            elif v==3:
                tkinter.messagebox.showinfo('key found! :)', 'key found at index ' + str(mid))
            break
        elif nums[mid] < key:
            l=mid+1
        else:
            r=mid-1

    if b: t2 = datetime.datetime.now()

    if l>r:
        if v==2:
            msgbx.showinfo('key not found! :(', 'key was not found')
        elif v==3:
            tkinter.messagebox.showinfo('key not found! :(', 'key was not found')

    log = "Execution Time: " + str((t2 - t1))[2:]
    execution.config(text=log)



def __merge_sort__(nums):

    if int(nums.__len__()) == 1:
        return
        
    l1 = nums[:int(nums.__len__() / 2)]
    __merge_sort__(l1)

    l2 = nums[int(nums.__len__() / 2):]
    __merge_sort__(l2)

    idx=0
    i=0
    j=0

    while i < l1.__len__() and j < l2.__len__():
        if l1[i] < l2[j]:
            nums[idx] = l1[i]
            i += 1
        else:
            nums[idx] = l2[j]
            j += 1
        idx += 1

    while i < l1.__len__():
        nums[idx] = l1[i]
        i += 1
        idx += 1

    while j < l2.__len__():
        nums[idx] = l2[j]
        j += 1
        idx += 1

    return nums


def __merge_sort(nums=[]):

    write = 0
    
    if nums.__len__() == 0:
        write = 1
        nums = prepare()
        if nums == False:
            return

    t1 = datetime.datetime.now()

    nums = __merge_sort__(nums)

    t2 = datetime.datetime.now()

    if write:
        writing = ''
        for n in nums:
            writing += str(n) + ' '
        writing = writing[:-1]
        if not __write_file__(writing, OutputPath):
            return

    log = "Execution Time: " + str((t2 - t1))[2:]
    execution.config(text=log)
    if v==2:
        msgbx.showinfo('log', "Finished, output file containes sorted input file\n")
    elif v==3:
        tkinter.messagebox.showinfo('log', "Finished, output file containes sorted input file\n")


def __partition__(nums, l, r):

    x = nums[r]
    i=l-1
    while l < r:
        if nums[l] <= x:
            i += 1
            nums[l], nums[i] = nums[i], nums[l]
        l += 1
    nums[r], nums[i+1] = nums[i+1], nums[r]
    return i+1


def __quick_sort__(nums, l, r):

    try:
        if l>=r:
            return
        p = __partition__(nums, l, r)
        __quick_sort__(nums,l, p-1)
        __quick_sort__(nums,p+1,r)
    except:
        # msg = "Quick sort can't be applied on this data, it contains many many recurrences of the same number\n";
        # if v == 2:
        #     msgbx.showinfo('Failed', msg)
        # elif v == 3:
        #     tkinter.messagebox.showinfo('Failed', msg)
        return


def __quick_sort():

    nums = prepare()

    if nums == False:
        return

    t1 = datetime.datetime.now()

    __quick_sort__(nums, 0, nums.__len__()-1)

    t2 = datetime.datetime.now()

    writing = ''
    for n in nums:
        writing += str(n) + ' '
    writing = writing[:-1]
    if not __write_file__(writing, OutputPath):
        return False

    log = "Execution Time: " + str((t2 - t1))[2:]
    execution.config(text=log)
    if v == 2:
        msgbx.showinfo('log', "Finished, output file containes sorted input file\n")
    elif v == 3:
        tkinter.messagebox.showinfo('log', "Finished, output file containes sorted input file\n")


def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and arr[i] < arr[l]:
        largest = l

    if r < n and arr[largest] < arr[r]:
        largest = r

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)


def __heap_sort__(arr):
    n = len(arr)

    for i in range(n, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[i], arr[0] = arr[0], arr[i]
        heapify(arr, i, 0)


def __heap_sort():

    nums = prepare()

    if nums == False:
        return

    t1 = datetime.datetime.now()

    __heap_sort__(nums)

    t2 = datetime.datetime.now()

    writing = ''
    for n in nums:
        writing += str(n) + ' '
    writing = writing[:-1]
    if not __write_file__(writing, OutputPath):
        return False

    log = "Execution Time: " + str((t2 - t1))[2:]
    execution.config(text=log)
    if v == 2:
        msgbx.showinfo('log', "Finished, output file containes sorted input file\n")
    elif v == 3:
        tkinter.messagebox.showinfo('log', "Finished, output file containes sorted input file\n")


def __count_sort__(nums):
    C = [0] * (max(nums)+1)

    for n in nums:
        C[n] += 1

    CC = []

    s=0
    for c in C:
        s+=c
        CC.append(s)

    i = nums.__len__()
    numms = [0] * i

    i-=1
    while i>=0:
        numms[CC[nums[i]]-1] = nums[i]
        CC[nums[i]] -= 1
        i -= 1
    return numms
    


def __count_sort():

    nums = prepare()

    if nums == False:
        return

    t1 = datetime.datetime.now()

    nums = __count_sort__(nums)

    t2 = datetime.datetime.now()

    writing = ''
    for n in nums:
        writing += str(n) + ' '
    writing = writing[:-1]
    if not __write_file__(writing, OutputPath):
        return False

    log = "Execution Time: " + str((t2 - t1))[2:]
    execution.config(text=log)
    if v == 2:
        msgbx.showinfo('log', "Finished, output file containes sorted input file\n")
    elif v == 3:
        tkinter.messagebox.showinfo('log', "Finished, output file containes sorted input file\n")


def __manual():

    man = \
        'Disclaimer', 'File should contain only numbers separated by spaces\n\n'\
        +'numbers should not be larger than 4*10^18 (4 billions of billions)\n\n'\
        +'or smaller than -4*10^18 (-4 billions of billions)'\
        +'file should not contain more than 10^8 (a hundred million) of numbers'

    if v==2:
        msgbx.showinfo('manual', man)
    elif v==3:
        tkinter.messagebox.showinfo('manual', man)


def do_job():
    if Ways.current() == 0:
        __read_file()
    elif Ways.current() == 1:
        __binary_search()
    elif Ways.current() == 2:
        __merge_sort()
    elif Ways.current() == 3:
        __quick_sort()
    elif Ways.current() == 4:
        __heap_sort()
    elif Ways.current() == 5:
        __count_sort()
    elif Ways.current() == 6:
        __manual()


def InputFile():
    global InputPath
    global OutputPath
    if v == 2:
        InputPath = tkFileDialog.asksaveasfilename(initialdir="D:/", title="Select file",
                                                   filetypes=(("Text files", "*.txt"), ("all files", "*.*")))
    elif v == 3:
        InputPath = filedialog.askopenfilename(initialdir="D:/", title="input file",
                                               filetypes=(("Text File", "*.txt"), ("All Files", "*.*")))


def OutputFile():
    global InputPath
    global OutputPath
    if v == 2:
        InputPath = tkFileDialog.askopenfilename(initialdir="D:/", title="Select file",
                                                 filetypes=(("Text files", "*.txt"), ("all files", "*.*")))
    elif v == 3:
        OutputPath = filedialog.asksaveasfilename(initialdir="D:/", title="output file",
                                                  filetypes=(("Text File", "*.txt"), ("All Files", "*.*")))


def main2():
    global root
    global Welcome
    global Ways
    global Ok
    global Path
    global execution
    global InputPath
    global OutputPath
    global Status

    root.title('Algorithms project')
    Welcome = Label(root, text="Welcome ..", pady=10, height=1)
    Welcome.grid(row=0)

    Ways = ttk.Combobox(root, values=optionz, width=30)
    Ways.current(1)
    Ways.grid(row=1, padx=10, sticky=W)

    Status = Frame(root)
    Status.grid(sticky=(S,W))

    execution = Label(Frame, text="Execution Time: ", padx=7, pady=-10)
    execution.grid(row=2, column=0, padx=0, sticky=S)

    Ok = Button(root, text="Ok", command=do_job)
    Ok.grid(row=1, column=1, pady=12, padx=12, ipady=3, ipadx=12)

    root.geometry("290x120+500+300")
    root.mainloop()


def main3():
    global root
    global Welcome
    global Ways
    global Ok
    global Path
    global execution
    global InputPath
    global OutputPath
    global Status

    root.title('Algorithms project')
    Main = tkinter.Frame(root)
    Menu = tkinter.Frame(root)

    Welcome = tkinter.Label(Main, text="Welcome ..", pady=20, height=1)
    Welcome.grid(row=0)

    InputBtn = tkinter.Button(Menu, text="input", command=InputFile)
    OutputBtn = tkinter.Button(Menu, text="output", command=OutputFile)

    InputBtn.grid(pady=5, ipady=3, ipadx=7, sticky=("w","e"))
    OutputBtn.grid(pady=5, ipady=3, ipadx=7, sticky=("w","e"))

    Ways = ttk.Combobox(Main, values=optionz, width=25, font=("Helvetica",12), justify=tkinter.CENTER)
    Ways.grid(row=1, padx=30, sticky="w", ipadx=5, ipady=5)
    Ways.set("Select an algorithm to go")
    Ways.state(['readonly'])

    # time declaration at start of the file with in status bar
    Status = tkinter.Frame(Main, background='white')

    execution = tkinter.Label(Status, text="Execution Time: ", pady=5, padx=15, bg='white', fg='black')
    execution.grid(sticky="WESN")

    Ok = tkinter.Button(Main, text="Ok", command=do_job, bd=0, font=("Helvetica",12))
    Ok.grid(row=2, column=0, padx=12, ipadx=97)

    Main.grid(sticky="WNS", column=0, row=0)
    Menu.grid(column=0, row=0, padx=315, sticky='N', pady=35)
    Status.grid(sticky="WES", columnspan=99, ipadx=150, pady=15, row=3)

    root.geometry("400x165+450+300")
    root.mainloop()

if v == 2:
    from Tkinter import *
    import ttk
    import tkMessageBox as msgbx
    import tkSimpleDialog
    import tkFileDialog
    import datetime

    root = Tk()
    main2()

elif v==3:
    import tkinter as tkinter
    from tkinter import *
    from tkinter import ttk
    from tkinter import messagebox
    from tkinter import simpledialog
    from tkinter import filedialog
    import datetime


    root = tkinter.Tk()
    main3()