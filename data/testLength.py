
with open("bddArrets.txt", "r") as stops:
    line = stops.readline()
    i=0
    #for i in enumerate (line):
        #print i
    a = line.count(" ")
    #print line
    #print a
    stops.close
    
with open("voyage.txt", "r") as trips:
    line0 = trips.readline()
    line = trips.readline()
    i=0
    for i in enumerate (line):
        print i
    a = line.count(",")
    print line
    print a
    for i in range (0, a):
        print ("coucou")
    trips.close