import os
import Tkinter as t
import tkMessageBox as mb
import time
from Autocomplementation import AutocompleteEntry

#######################-DEFINITION_LISTE-#################################
station_list=[]
FIC = open("nomsArrets.txt", "r")
contenu=FIC.read()
contenu = contenu.lower()
station_list = contenu.split('\n')
FIC.close()

########################-DEFINITION_FONCTION-#############################
#--Chargement_Logo
#def Logo():

#-- Fonction qui place des zones de saisies et recupere le point de depart et
#-- d'arrivee de l'utilisateur
def Saisie_Arrets(Saisie, depart, arrivee) :
    #--Nom des Entry
    dep = t.Label(Saisie, text="Depart :", font="arial 10 bold")
    dep.grid(column=0,row=2, padx=80)

    arr = t.Label(Saisie, text="Arrivee :", font="arial 10 bold")
    arr.grid(column=0,row=3, padx=5)
    #--Creation et placement de la zone de saisie de la stration de depart
    entree_d=AutocompleteEntry(Saisie, textvariable=depart, width=30)
    entree_d.set_completion_list(station_list)
    entree_d.grid(column=1,row=2, padx=5, columnspan=2)
    entree_d.focus_set()

    #--Creation et placement de la zone de saisie de la station d'arrivee
    entree_a=AutocompleteEntry(Saisie, textvariable=arrivee, width=30)
    entree_a.set_completion_list(station_list)
    entree_a.grid(column=1,row=3, padx=5, columnspan=2)
    entree_a.focus_set()


#-- Fonction qui place des cases a cocher et recupere la condition emise par
#-- l'utilisateur.
def Saisie_Conditions(Saisie, condition, station, heure, minute, h_dep) :
    #--Initialisation de la case cochee par defaut
    condition.set(1)
    h_dep.set(0)

    #--Definicion des trois cases a cocher
    rapide=t.Radiobutton(Saisie, variable = condition, text="Le plus rapide", value=1)
    rapide.grid(column=4,row=1)

    m_corr=t.Radiobutton(Saisie, variable = condition, text="En evitant les travaux",
                         value = 2)
    m_corr.grid(column=4, row=2, padx=5)

    s_corr=t.Radiobutton(Saisie, variable = condition, text="En evitant une correspondance",
                         value=3)
    s_corr.grid(column=4, row=3, padx=5)

    #--Definition de la zone de texte pour saisir la correspondance a eviter
    corr_evite=AutocompleteEntry(Saisie, textvariable=station, width=30)
    corr_evite.set_completion_list(station_list)
    corr_evite.grid(column=4, row=4, padx=30)
    corr_evite.focus_set()

    #-- Definition de l'heure de depart
    dep_a=t.Radiobutton(Saisie, variable=h_dep, text="Depart a :", value =1)
    dep_a.grid(row=1,column=0)

    h=t.Spinbox(Saisie, from_= 0, to=23, increment=1, width=4)
    h.config(textvariable=heure)
    h.grid(row=1, column=1)

    m=t.Spinbox(Saisie, from_= 0, to=59, increment=1, width=4)
    m.config(textvariable=minute)
    m.grid(row=1, column=2, sticky=t.W)


#--Fonction qui ecrit les donnees saisies par l'utilisateur dans un fichier
def Envoie_Infos(depart, arrivee, corr, cond, h_dep, heure, minute) :
    if (h_dep.get()==1):
        Heure = heure.get()
        Heure=int(Heure)
        Minute = minute.get()
        Minute=int(Minute)

        UnixT = 1495584000 + (Heure*3600)+(Minute*60)
        UnixT=str(UnixT)
    else :
       Heure = time.clock()
       UnixT = 1495584000 + Heure
       UnixT=str(UnixT)

    #--Recuperation des donnees contenues dans depart, arrivee et corr
    Depart=depart.get()
    Arrivee=arrivee.get()
    Correspondance=corr.get()

    #Ecriture des donnees dans le fichier
    FIC = open("Demande_user.txt", "w")

    FIC.write(UnixT)
    FIC.write("\n")
    FIC.write(Depart)
    FIC.write("\n")
    FIC.write(Arrivee)
    FIC.write("\n")

    Condition = str(Cond.get())
    if (Cond.get()==3) :
        FIC.write(Condition)
        FIC.write("\n")
        FIC.write(Correspondance)
    else :
        FIC.write(Condition)

    FIC.close()

def Verification(depart, arrivee, corr, cond, h_dep, heure, minute):
    if (depart.get() == ''):
        mb.showerror(title="Erreur", message="Vous devez saisir une station de depart")
    elif (arrivee.get() == ''):
        mb.showerror(title="Erreur", message="Vous devez saisir une station d'arrivee")
    elif (depart.get()==arrivee.get()):
        mb.showerror(title="Erreur", message="Vos stations de depart et d'arrivee doivent etre differentes")
    elif ((corr.get()==depart.get())or(corr.get()==arrivee.get())):
        mb.showerror(title="Erreur", message="Vous ne pouvez pas eviter une station choisie pour partir ou arriver")
    elif ((cond.get()==3)and(corr.get()=='')):
        mb.showerror(title="Erreur", message="Saisissez la correspondance a eviter")
    elif ((h_dep.get()==1)and((heure.get()=='')or(minute.get()==''))):
        mb.showerror(title="Erreur", message="Saisissez un horaire de depart")
    else:
        mb.showinfo(title="Merci", message="Votre demande a ete prise en compte")
        Envoie_Infos(depart, arrivee, corr, cond, h_dep, heure, minute)
        system("./EXE")
        

def Verif() : Verification(Depart, Arrivee, Correspondance, Cond, H_Dep, H, M)

#-- Fonction qui cree des butons pour valider et quitter la page.
#-- Le bouton valider appelle la fonction des verification de la saisie
def Boutons(Saisie):
    #--Creation et placement des butons pour valider la saisie et quitter la fenetre
    valider=t.Button(Saisie, text="Valider", command=Verif)
    valider.grid(column=6, row=2)

    quitter=t.Button(Saisie, text="Quitter", command=fenetre.destroy)
    quitter.grid(column=6, row=3)

#--Fonction qui represente le trajet sur un graph
def Affichage_du_trajet(frame, trajet, hd, ha) :

    HDT=t.Label(frame, text="Heure de depart : ")
    HDT.grid(row=0, column=0, pady=(5,0))
    HD = t.Label(frame, text=hd)
    HD.grid(row=0, column=1)

    HAT=t.Label(frame, text="Heure d'arrivee :")
    HAT.grid(row=1, column=0, pady=(0,5))
    HA = t.Label(frame, text=ha)
    HA.grid(row=1, column = 1)

    Trajet=t.Label(frame, text=trajet)
    Trajet.grid(row=3, column=0, columnspan=2, pady=5, padx=20)

#--Fonction qui lit les infos sur le trajet contenues dans le fichier et les
#--affiche
def Recup_Infos(frame) :
    with open("feuille_route.txt", "r") as R :

        h_dep = R.readline().rstrip('\n')
        h_arr = R.readline().rstrip('\n')

        Info = R.read().rstrip('\n')

    Affichage_du_trajet(frame, Info, h_dep, h_arr)

#############################-MAIN-#######################################
fenetre=t.Tk()
fenetre.title("ViAstar")
fenetre.geometry("900x600")

            #############-INITIALISATION-##############
#--Valeur contenant la station de depart, d'arrivee et de correspondance a eviter
Depart=t.StringVar()
Arrivee=t.StringVar()
Correspondance=t.StringVar()
H = t.StringVar()
M = t.StringVar()
#--Valeur contenant l'etat des cases de condition du trajet
Cond=t.IntVar()
H_Dep = t.IntVar()

            ###########################################
Titre = t.Label(fenetre, text="ViA*")
Titre.config(font="sans 24")
Titre.grid(row=0, column=0, columnspan=2)

#--Frame de saisie
Saisie = t.LabelFrame(fenetre, text="Saisissez votre trajet", border=3, relief=t.GROOVE,
                      font="arial 16 bold")

Saisie_Arrets(Saisie, Depart, Arrivee)
Saisie_Conditions(Saisie, Cond, Correspondance, H, M, H_Dep)
Boutons(Saisie)

Saisie.grid(row=1, column=0, columnspan=2, sticky='ew', padx=70, ipady=5)

#-- Canvas pour affichage trajet sur plan
fond=t.Canvas(fenetre, width=500, height=350, background="darkgray")
fond.grid(row=2, column=0, padx=(70,0), pady=(5,0))

#-- Frame d'affichage du trajet
Affich = t.LabelFrame(fenetre, text="Voici le trajet a suivre", border=3,
                      relief=t.GROOVE, width=200, height=350, font="arial 16 bold")
Recup_Infos(Affich)

Affich.grid(row=2, column=1, padx=(20,70), pady=(5,0), sticky='nesw', ipadx=5)

fenetre.mainloop()
