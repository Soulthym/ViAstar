listStopsNames = []

def SearchStop(stop_ID):
    found = 0
    test = 0
    with open("TestArret.txt", "r") as stops:
        while found == 0:
            line = stops.readline()
            stringInfos = line.split(',', 1)
            listStopsNames.append(stringInfos[0]+"\n")
            if stop_ID == stringInfos[0]:
                found = 1
                return line
            test+=1
            if test == 10:
                break
    stops.close()
        

with open("TestLigne.txt", "r") as trips:
    cpt = 0
    for nameLine in trips.readlines():
        if cpt == 0:
            print nameLine
            cpt+=1
        else:
            cpt = 0
            length = nameLine.count(",")
            stringStops = nameLine.split(",")
            for i in range (0, length):
                print stringStops[i]
                wanted = SearchStop(stringStops[i])
                print ("ok")
                print wanted
    trips.close

