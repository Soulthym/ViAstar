with open ("bddArrets.txt", "r") as A:
    with open ("bddArretsVirgule.txt", "w+") as V: 
        for line in A:
            line = line.replace(',,', ',')
            V.write(line)
        V.close()
    A.close()