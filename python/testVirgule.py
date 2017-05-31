with open ("TestVirgule.txt", "r") as Wrong:
    with open ("Virgule.txt", "w+") as Good :
        for line in Wrong:
            string = line.split(",", 1)
            print string[0]
            print string[1]
            print ("suite")
            
            line = line.replace(",,", ",")
            Good.write(line)
        Good.close()
    Wrong.close()