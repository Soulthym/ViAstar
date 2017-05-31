listStopsAndLines = []

def SearchStop(stop_ID):
    found = 0
    with open("bddArretsVirgule.txt", "r") as stops:
        while found == 0:
            line = stops.readline()
            stringInfos = line.split(',', 1)
            if stop_ID == stringInfos[0]:
                found = 1
                return line
            else:
                continue
    stops.close()        

with open("voyage.txt", "r") as trips:
    cpt = 0
    for nameLine in trips.readlines():
        if cpt == 0:
            cpt+=1
            print nameLine
            listStopsAndLines.append(nameLine)
        else:
            cpt = 0
            length = nameLine.count(",")
            stringStops = nameLine.split(",")
            for i in range (0, length):
                wanted = SearchStop(stringStops[i])
                listStopsAndLines.append(wanted)
    trips.close

with open ("Graph.txt", "w+") as G: 
    G.writelines(listStopsAndLines)
    print ("ok")
    G.close()
    
with open ("Graph.txt", "r") as G:
    with open ("Final.txt", "w+") as F:
        cpt = 0
        for line in G:
            if cpt==0:
                line = line.replace('"', '')
                F.write('_'+ line)
                cpt+=1
                print ("done")
            else:
                line = line.replace('\n', '')
                line = line.replace(',', '\n')
                F.write(line)
                cpt =0
        F.close()
    G.close()

      