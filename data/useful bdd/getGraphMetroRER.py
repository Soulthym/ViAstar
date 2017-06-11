def findID(F = "",value = ""):
    if F and value:
        with open (F, "r") as File:
            ret = ""
            for line in File:
                # print line
                line = line.replace('\n', '')
                if line.startswith(value):
                    ret = line
                    break
            File.close()
            return ret

with open ("bddArrets.txt", "r") as A:
    with open ("bddArretsClean.txt", "w+") as V:
        for line in A:
            line = line.replace(',,', ',')
            line = line.replace(',', ' ')
            V.write(line)
        V.close()
    A.close()

with open ("voyage.txt", "r") as A:
    with open ("voyageClean.txt", "w+") as V:
        for line in A:
            line = line.replace('\n', '')
            line = line.replace(',', '\n',line.count(',')-1)
            line = line.replace(',', '')
            line = line.replace('\r', '\n')
            V.write(line)
        V.close()
    A.close()

with open ("voyage.txt", "r") as A:
    with open ("voyageMetroRER.txt", "w+") as V:
        # print A.readlines()
        line = "Start"
        while(line):
            line = A.readline()
            line = line.replace('\n', '')
            if line.replace('\r', '') in {'"A"','"B"','"C"','"D"','"E"',
                                          '"1"','"2"','"3"','"4"','"5"',
                                          '"6"','"7"','"8"','"9"','"10"',
                                          '"11"','"12"','"13"','"14"'}:
                V.write(line.replace('\r', '\n'))
                line = A.readline()
                line = line.replace(',', '\n',line.count(',')-1)
                line = line.replace(',', '')
                line = line.replace('\r', '')
                V.write(line)
            else:
                A.readline()
                # print line
        V.close()
    A.close()

with open ("voyageMetroRER.txt", "r") as Trips:
    with open ("GraphMetroRER.txt", "w+") as Graph:
        for line in Trips:
            line = line.replace('\r', '')
            if line.startswith('"'):
                Graph.write(line)
                print line
            else:
                station = findID("bddArretsClean.txt",line.replace('\n',''))
                print station.replace('\n','')
                Graph.write(station)
        Graph.close()
    Trips.close()

with open ("voyageClean.txt", "r") as Trips:
    with open ("GraphTotal.txt", "w+") as Graph:
        for line in Trips:
            line = line.replace('\r', '')
            if line.startswith('"'):
                Graph.write(line)
                print line
            else:
                station = findID("bddArretsClean.txt",line.replace('\n',''))
                print station.replace('\n','')
                Graph.write(station)
        Graph.close()
    Trips.close()
