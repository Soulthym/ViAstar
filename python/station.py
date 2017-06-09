voyage = open("voyage.txt", "w+") 
listRoutes = []
listRoutes1 = []
listTrips = []

stringS = ""
stringF = ""

def tripName(stringF):
    with open("data/trips.txt", "r") as trips:
        line = trips.readline()
        for line in trips:
            string = line.split(",")
            if stringF == string[2]:
                routeID = string[0]
                break
        trips.close()
    with open("data/routes.txt", "r") as routes:
        line = routes.readline()
        for line in routes:
            string = line.split(",")
            if routeID == string[0]:
                return string[2]

with open("data/trips.txt", "r") as trips:
    line = trips.readline()
    print "Iterating through trips..."
    for line in trips:
        lastL = stringS
        string = line.split(",")
        stringT = string[2]
        stringS = string[0]
        if stringS == lastL:
            continue
        listTrips.append(stringT)

with open("data/stop_times.txt", "r") as stops:
    line = stops.readline()
    print "Iterating through stops..."
    for line in stops:
        string = line.split(",")
        stringT = string[3]
        stringS = string[0]
        if stringS in listTrips:
            stringF += stringT +","
        else:
            if stringF:
                stringS = tripName(stringS)
                print stringS
                print stringF
            stringF = ""
            continue
