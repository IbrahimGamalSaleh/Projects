import sys

v = int(sys.version[0])

root = ''
Welcome = ''
Ok = ''
Path = ''
Ways = ''
execution = ''
optionz = ['Read file', 'Binary Search', 'Merge sort', 'Quick Sort', 'Disclaimer']


def __read_file__():
    reading = ''
    if v==2:
        Fayl = file('input.in', 'r')
        reading = Fayl.read()
    elif v==3:
        with open('input.in', 'r') as F:
            for line in iter(F.readline, ''):
                reading += line

    return reading


def __write_file__(reading, name=''):
    if v==2:
        Fayl = file('output.out', 'w')
        if name != '':
            Fayl = file(name, 'w')
        Fayl.write(reading)
    elif v==3:
        if name != '':
            with open(name, 'w') as F:
                print(reading, file=F)
        else:
            with open('output.out', 'w') as F:
                print(reading, file=F)


def __read_file():
    reading = __read_file__()
    if v==2:
        msgbx.showinfo("file read", reading)
    elif v==3: tkinter.messagebox.showinfo("file read", reading)


def __binary_search(key=0):
    t1 = datetime.datetime.now()
    __manual()
    reading = __read_file__()
    nums = reading.split(' ');
    if nums.__len__() == 0:
        msgbx.showinfo('empty file', 'Input file is empty')
        return

    numms = []
    idx=0
    for n in nums:
        try :
            numms.append(int(n))
            idx += 1
        except:
            pass
            # if i!=0:
            #     nums = nums[:i]
            #     msgbx.showinfo('bad input', 'Search will be on the first ' + str(i) + ' items')
            # else:
            #     msgbx.showinfo('bad input', 'application could not parse file inputs or it is empty')
            #     return
    nums = numms

    if idx == 0:
        if v==2:
            msgbx.showinfo('bad input', 'application could not parse file inputs or it is empty')
        elif v==3:
            tkinter.messagebox.showinfo('bad input', 'application could not parse file inputs or it is empty')
    elif idx != nums.__len__():
        if v==2:
            msgbx.showinfo('incomplete input', 'application could not parse all file inputs')
        elif v==3:
            tkinter.messagebox.showinfo('incomplete input', 'application could not parse all file inputs')

    nums = __merge_sort__(nums)

    key = ''
    while key == '':
        s = ''
        if v==2:
            s = tkSimpleDialog.askstring("key", "Enter key to search for")
        elif v==3:
            s = tkinter.simpledialog.askstring("key", "Enter key to search for")
        if s == '':
            continue
        key = int(s)

    l=0
    r=nums.__len__()-1

    while l<=r:
        mid = int(l + (r-l)/2);
        if nums[mid] == key:
            if v == 2:
                msgbx.showinfo('key found! :)', 'key found at index ' + str(mid))
            elif v==3:
                tkinter.messagebox.showinfo('key found! :)', 'key found at index ' + str(mid))
            break
        elif nums[mid] < key:
            l=mid+1
        else:
            r=mid-1

    if l>r:
        if v==2:
            msgbx.showinfo('key not found! :(', 'key was not found')
        elif v==3:
            tkinter.messagebox.showinfo('key not found! :(', 'key was not found')

    t2 = datetime.datetime.now()
    execution.config(text="Execution Time: " + str((t2 - t1) / 1000))


def __merge_sort__(nums):

    if 1 == nums.__len__() or 0 == nums.__len__():
        return nums

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
    print (v)
    t1 = datetime.datetime.now()
    write = 0
    if nums.__len__() == 0:
        write = 1
        nums = __read_file__().split()

    i=0
    while i < nums.__len__():
        nums[i] = int(nums[i])
        i += 1

    nums = __merge_sort__(nums)

    if write:
        writing = ''
        for n in nums:
            writing += str(n) + ' '
        writing = writing[:-1]
        __write_file__(writing, 'merge_sort-output.txt')
    t2 = datetime.datetime.now()
    execution.config(text="Execution Time: " + str((t2 - t1) / 1000))


def __quick_sort():

    nums = __read_file__().split()

    i=0
    while i < nums.__len__():
        nums[i] = int(nums[i])
        i += 1

    writing = ''
    for n in nums:
        writing += str(n) + ' '
    writing = writing[:-1]
    __write_file__(writing, 'quick_sort-output.txt')


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
        __manual()


def main2():
    global root
    global Welcome
    global Ways
    global Ok
    global Path
    global execution
    root.title('Algorithms project')
    Welcome = Label(root, text="Welcome ..", pady=10, height=1)
    Welcome.grid(row=0)

    Ways = ttk.Combobox(root, values=optionz, width=30)
    Ways.current(1)
    Ways.grid(row=1, padx=10, sticky=W)

    execution = Label(root, text="Execution Time: ", padx=7, pady=-10)
    execution.grid(row=2, column=0, padx=0, sticky=W)

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
    Welcome = tkinter.Label(root, text="Welcome ..", pady=10, height=1)
    Welcome.grid(row=0)

    Ways = ttk.Combobox(root, values=optionz, width=30)
    Ways.current(1)
    Ways.grid(row=1, padx=10, sticky="w")

    # time declaration at start of the file
    execution = tkinter.Label(root, text="Execution Time: ", padx=7, pady=-10)
    execution.grid(row=2, column=0, padx=0, sticky="w")

    Ok = tkinter.Button(root, text="Ok", command=do_job)
    Ok.grid(row=1, column=1, pady=12, padx=12, ipady=3, ipadx=12)

    root.geometry("290x120+500+300")
    root.mainloop()

if v == 2:
    from Tkinter import *
    import ttk
    import tkMessageBox as msgbx
    import tkSimpleDialog
    import datetime
    root = Tk()
    main2()
elif v==3:
    import tkinter as tkinter
    from tkinter import ttk
    from tkinter import messagebox
    from tkinter import simpledialog
    import datetime
    root = tkinter.Tk()
    main3()