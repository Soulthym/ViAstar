from Tkinter import *
import time
import math

master = Tk()

w = Canvas(master, height=350, width=500)
w.pack()

coorlist = []
phi0 = math.cos(48.86108)

def findStation(ligne, station1, station2):
    with open("data/Final.txt", "r") as bdd:
        for line in bdd:
            if "_"+ligne in line.strip("\n"):
                bdd.next()
                line = bdd.next()
                while station1.strip("\n")  not in line.strip("\n"):
                    line = bdd.next()
                    print line
                    if "_" in line:
                        break
                if station1.strip("\n") in line.strip("\n"):
                    print "STATION 1", line
                    while station2.strip("\n") not in line.strip("\n"):
                        lat = bdd.next()
                        lon = bdd.next()
                        bdd.next()
                        line= bdd.next()
                        try:
                            x = 6300*float(lon)*phi0
                            y = 6300*float(lat)
                            x/=2
                            y/=6.57142
                            x-=1036
                            y-=46693
                            x = int (x)
                            y = int (y)
                            coorlist.append(str(x)+","+str(y))
                            print x,y
                        except ValueError:
                            print "Fucked"
                            return
                    print "station2", line
                    print bdd.next()
                    print bdd.next()
                    return


with open("data/exemple.end", "r") as output:
    output.readline()
    output.readline()
    output.readline()

    for i in output:
        line = i.strip('\n')
        station1 = output.next()
        station2 = output.next()
        print line, station1, station2
   
        findStation(line, station1, station2)
        for i in range(len(coorlist)):
            x = int(coorlist[i].split(',')[0])
            y = int(coorlist[i].split(',')[1])
            w.create_oval(x,y, x+5, y+5, fill="blue")
            print int(x), int(y)
        coorlist[:] = []
        try:
            output.next()
        except StopIteration:
            break
    
mainloop()
