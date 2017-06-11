#donnee de melanie
DataMel = '"14"\nstation de depart : "Saint-Lazare"\nstation d arrivee : "Olympiades"\n6\nstation de depart : "Tolbiac"\nstation d arrivee : "Jussieu"\n'
location = []

def SearchLocation (name):
    with open("bddArretsVirgule.txt", "r") as BDD :
        for line in BDD:
            string = line.split(',', 2)
            if name == string[1]:
                return string[2] #changer print en return et si besoin je peux mettre dans 2 var sans les virgules
                break
        BDD.close()

def GiveLocation (data):
    lenght = data.count('\n')        
    string = data.split('\n')
    for i in range (0,lenght):
        cpt = i%3
        if cpt==1 or cpt==2:
            name = string[i].split(': ')
            loc = SearchLocation(name[1])
            location.append(loc)
        
GiveLocation(DataMel)
print location
#pour recuperer les lat et long separement, t as juste a ecrire test = location[0].split(',') et test[0] sera ta lat, test[1] ta long, tu mets ca dans une boucle est le tour est joue