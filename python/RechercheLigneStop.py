listStopsNames = []

with open("bddArrets.txt", "r") as stops:
    line = stops.readline()
    for line in stops:
        string = line.split("\"")
        if  string[1]+'\n' not in listStopsNames:
            listStopsNames.append(string[1] + '\n')
        else:
            continue
    stops.close

with open ("stopsUnic.txt", "w+") as stopsUnic: 
    stopsUnic.writelines(listStopsNames)
    stopsUnic.close()
    
            