#==============================================================================
# with open ("TestVirgule.txt", "r") as V: 
#     with open ("TestConvention.txt","w") as C:
#         cpt = 0
#         for line in V:
#             if cpt == 0:
#                 line = line.replace('"', '')
#                 C.write('_'+ line)
#                 cpt+=1
#             else:
#                 line = line.replace('\n', '')
#                 print line
#                 line = line.replace('  ', '\n')
#                 line = line.replace(' ', '\n')
#                 C.write(line)
#                 cpt =0
#         C.close()
#     V.close()
#==============================================================================

with open ("Graph.txt", "r") as G:
    with open ("Final.txt", "w+") as F:
        for line in G:
            if line[0]=='"':
                line = line.replace('"', '')
                F.write('_'+ line)
                print ("done")
            else:
                line = line.replace('\n', '')
                line = line.replace ('"', '')
                line = line.replace(',', '\n')
                F.write(line)
        F.close()
    G.close()