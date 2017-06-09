import random 
time = ""
i = 0
fileT = open("time.txt", "r+w")
def getTime(stopID):
    with open("data/stop_times.txt", "r") as stops:
        line = stops.readline()
        for line in stops:
            string = line.split(",")
            if stopID == string[3]:
                time = string[1]
                fileT.write(time+",")


with open("bddArr.txt", "r") as time:
    for line in time:
        if line is "\n":
            continue
        line = line.split(",,")
        stopID = line[0]
        fileT.write(stopID+"\n")
        i += 1
        print float(i/24068*100),"%"
        print i, "out of 475 stations done"
        getTime(stopID)
        fileT.write("\n")
       


time.close()
