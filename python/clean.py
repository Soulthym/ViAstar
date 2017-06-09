RER = ['A', 'B', 'C', 'D', 'E']
MET = ['1', '2', '3', '4', '5', '6', '7','8', '9', '10', '11', '12', '13', '14']

fic = open("bddArr.txt", "r+w")

def getStat(station_id):
    with open("data/bddArrets.txt", "r") as bdd:
        for line in bdd:
            string = line.split(",,")
            if string[0] == station_id:
                fic.write(line+"\n")


with open("data/voyage.txt", "r") as bdd:
    i = 0
    for i, line in enumerate(bdd, 0):
        if '"' not in line:
            continue
        line = line.replace('"','')
        line = line.replace('\n','')
        if line in RER:
            nLine = bdd.next()
            string = nLine.split(",")
            for i in range(len(string)):
                    station_id = string[i]
                    getStat(station_id)
        
        if line in MET:
            i += 1
            nLine = bdd.next()
            string = nLine.split(",")
            for i in range(len(string)):
                    station_id = string[i]
