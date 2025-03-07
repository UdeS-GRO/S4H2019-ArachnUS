# Python Interface v.1.0

# Listes des importations
from tkinter import *
import threading
import Communication as com
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg



# -------------------------------------------------------------------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------- #
class application(threading.Thread):
    CurrentValue1 = None
    CurrentValue2 = None
    CurrentValue3 = None
    CurrentValue4 = None
    CurrentValue5 = None
    CurrentValue6 = None
    CurrentValue7 = None
    CurrentValue8 = None
    CurrentValue9 = None
    eM1 = None
    eM2 = None
    eM3 = None
    eM4 = None
    eM5 = None
    eM6 = None
    eM7 = None
    eM8 = None
    eM9 = None
    CurrentAngleX = None
    CurrentAngleY = None
    CurrentEtat = None
    CurrentHauteur = None
    isrunning = True


    def __init__(self):
        self.isrunning = True
        threading.Thread.__init__(self)
        self.start()

    # Fonction pour changer l'état du robot
    def Change_etat(self, numero):
        com.etat = numero

    # Fonction pour augmenter la hauteur du robot lorsque celui-ci est en mode stabilisation
    def btnHauteurUp(self):
        com.hauteur += 1

    # Fonction pour diminuer la hauteur du robot lorsque celui-ci est en mode stabilisation
    def btnHauteurDown(self):
        com.hauteur -= 1

    # Fonction pour update les moteurs en mode manuel
    def btnUpdate(self):
        com.moteur = com.buf_moteur.copy()
        com.Arduino.envoieVersArduino(com.moteur)

    # Fonction pour quitter le programme et arrêter le thread du Main.py
    def exxit(self):
        self.isrunning = False
        exit()


    # Fonction principale du UI
    def run(self):
        self.fenetre = Tk() # Créé la fenêtre
        self.fenetre.wm_title("Interface ArachnUS") # Titre de la fenêtre
        self.fenetre.config(bg = "gray35")
        self.fenetre.protocol("WM_DELETE_WINDOW", self.exxit)   # Le bouton X de la fenêtre appelle la fonction exxit()

        # Frame Moteur // Permet de segmenter le frame fenetre avec d'autres sous frames (colonne = 0)
        frameMoteur = Frame(self.fenetre)
        frameMoteur.grid(sticky="NS", row=0, column=0, padx=10, pady=10)
        Label(frameMoteur, text="Mode manuel moteurs:", fg="lawn green", bg="gray55", font=("Helvetica", 12, "bold")).grid(row=0, column=0, padx=10, pady=2)
        frameMoteur.config(bg="gray55")

        # Patte 1
        framePatte = Frame(frameMoteur)
        framePatte.grid(sticky="WE", row=1, column=0, padx=10, pady=2)
        framePatte.config(bg="gray75")
        Label(framePatte, text="Patte 1", bg="gray75", font=("Helvetica", 11, "bold")).grid(sticky=N, row=1, column=0, padx=10, pady=2, rowspan=2)
        Label(framePatte, text="Moteur 1").grid(row=1, column=1, padx=10, pady=2)
        Label(framePatte, text="Moteur 2").grid(row=2, column=1, padx=10, pady=2)
        Label(framePatte, text="Moteur 3").grid(row=3, column=1, padx=10, pady=2)

        # Ajoute un label à l'écran avec la valeur du moteur. Le label est updaté périodiquement dans Refresher()
        self.CurrentValue1 = Label(framePatte, text=com.buf_moteur[0], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue1.grid(row=1, column=5, padx=10, pady=2)

        self.CurrentValue2 = Label(framePatte, text=com.buf_moteur[1], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue2.grid(row=2, column=5, padx=10, pady=2)

        self.CurrentValue3 = Label(framePatte, text=com.buf_moteur[2], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue3.grid(row=3, column=5, padx=10, pady=2)

        # Créer une boîte pour entrer la valeur du moteur souhaité //La valeur par défault est déjà écrite dans la boîte
        self.eM1 = Entry(framePatte, width=4)
        self.eM1.grid(row=1, column=4)
        self.eM1.insert(3, com.buf_moteur[0])

        self.eM2 = Entry(framePatte, width=4)
        self.eM2.grid(row=2, column=4)
        self.eM2.insert(3, com.buf_moteur[1])

        self.eM3 = Entry(framePatte, width=4)
        self.eM3.grid(row=3, column=4)
        self.eM3.insert(3, com.buf_moteur[2])
        # -------------------------------------------------------------------------------------------------------------------- #

        # Patte 2

        Label(framePatte, text="Patte 2", bg="gray75", font=("Helvetica", 11, "bold")).grid(sticky=N, row=4, column=0, padx=10, pady=2, rowspan=2)
        Label(framePatte, text="Moteur 4").grid(row=4, column=1, padx=10, pady=2)
        Label(framePatte, text="Moteur 5").grid(row=5, column=1, padx=10, pady=2)
        Label(framePatte, text="Moteur 6").grid(row=6, column=1, padx=10, pady=2)

        self.eM4 = Entry(framePatte, width=4)
        self.eM4.grid(row=4, column=4)
        self.eM4.insert(3, com.buf_moteur[3])

        self.eM5 = Entry(framePatte, width=4)
        self.eM5.grid(row=5, column=4)
        self.eM5.insert(3, com.buf_moteur[4])

        self.eM6 = Entry(framePatte, width=4)
        self.eM6.grid(row=6, column=4)
        self.eM6.insert(3, com.buf_moteur[5])

        self.CurrentValue4 = Label(framePatte, text=com.buf_moteur[3], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue4.grid(row=4, column=5, padx=10, pady=2)

        self.CurrentValue5 = Label(framePatte, text=com.buf_moteur[4], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue5.grid(row=5, column=5, padx=10, pady=2)

        self.CurrentValue6 = Label(framePatte, text=com.buf_moteur[5], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue6.grid(row=6, column=5, padx=10, pady=2)

        # -------------------------------------------------------------------------------------------------------------------- #

        # Patte 3

        Label(framePatte, text="Patte 3", bg="gray75", font=("Helvetica", 11, "bold")).grid(sticky=N, row=7, column=0, padx=10, pady=2, rowspan=2)
        Label(framePatte, text="Moteur 7").grid(row=7, column=1, padx=10, pady=2)
        Label(framePatte, text="Moteur 8").grid(row=8, column=1, padx=10, pady=2)
        Label(framePatte, text="Moteur 9").grid(row=9, column=1, padx=10, pady=2)

        self.eM7 = Entry(framePatte, width=4)
        self.eM7.grid(row=7, column=4)
        self.eM7.insert(3, com.buf_moteur[6])

        self.eM8 = Entry(framePatte, width=4)
        self.eM8.grid(row=8, column=4)
        self.eM8.insert(3, com.buf_moteur[7])

        self.eM9 = Entry(framePatte, width=4)
        self.eM9.grid(row=9, column=4)
        self.eM9.insert(3, com.buf_moteur[8])

        self.CurrentValue7 = Label(framePatte, text=com.buf_moteur[6], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue7.grid(row=7, column=5, padx=10, pady=2)

        self.CurrentValue8 = Label(framePatte, text=com.buf_moteur[7], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue8.grid(row=8, column=5, padx=10, pady=2)

        self.CurrentValue9 = Label(framePatte, text=com.buf_moteur[8], font=("Helvetica", 10, "bold"), bg="DarkSeaGreen1")
        self.CurrentValue9.grid(row=9, column=5, padx=10, pady=2)

        # Bouton qui appel la fonction btnUpdate dans Communication.py
        BoutonUpdate = Button(frameMoteur, text="Update", font=("Helvetica", 12, "bold"), fg="blue", bg="gray75", command=self.btnUpdate)
        BoutonUpdate.grid(row=0, column=2, padx=10, pady=2)


        # ---------------------------------------------------------
        # Frame Angle robot // Placer à droite du frameMoteur (colonne = 1)
        frameAngleTitre = Frame(self.fenetre)
        frameAngleTitre.grid(sticky="NS", row=0, column=1, padx=10, pady=10)
        frameAngleTitre.config(bg="gray55")
        Label(frameAngleTitre, text = "Angle du robot:", fg="lawn green", bg="gray55", font=("Helvetica", 12, "bold")).grid(row=0, column=0, padx=10, pady=2)

        # Frame pour afficher les valeur d'angle du robot
        frameAngle = Frame(frameAngleTitre, width=100, height=150)
        frameAngle.grid(row=1, column=0, padx=10, pady=2)
        frameAngle.config(bg="gray55")
        # Ajoute 2 label à l'écran avec la valeur d'angle moteur. Le label est updaté périodiquement dans Refresher()
        self.CurrentAngleX = Label(frameAngle, text=com.angle[0], bg="DarkSeaGreen1", font=("Helvetica", 10, "bold"))
        self.CurrentAngleX.grid(row=0, column=0, padx=10, pady=2)
        self.CurrentAngleY = Label(frameAngle, text=com.angle[0], bg="DarkSeaGreen1", font=("Helvetica", 10, "bold"))
        self.CurrentAngleY.grid(row=1, column=0, padx=10, pady=2)
        # -------------------------------------------------------------------------------------------------------------------- #

        # Frame OpenCR // Pour afficher et choisir l'état de la carte OpenCR
        frameOpen = Frame(frameAngleTitre)
        frameOpen.grid(row=2, column=0, padx=10, pady=2)
        frameOpen.config(bg="gray55")
        Label(frameOpen, text="État du OpenCR:", fg="lawn green", bg="gray55", font=("Helvetica", 12, "bold")).grid(row=0, column=0, padx=10, pady=2)
        # Ajoute 1 label pour afficher l'état de la carte. Updaté dans Refresher()
        self.CurrentEtat = Label(frameOpen, bg="DarkSeaGreen1", font=("Helvetica", 10, "bold"))
        self.CurrentEtat.grid(row=1, column=0, padx=10, pady=2)

        # Valeur initiale de l'état
        switch_variable = StringVar(value="Off")

        # Ajoute 3 btn pour changer l'état de OpenCR avec com.Change_etat. Radiobutton pour un seul bnt actif à la fois
        BoutonInit = Radiobutton(frameOpen, text="(1) Init", bg="gray75", font=("Helvetica", 10, "bold"), variable=switch_variable, indicatoron=False, command=lambda: self.Change_etat(1), width=9, value="Init") #INIT
        BoutonInit.grid(row=2, column=0, padx=10, pady=2)
        BoutonManuel = Radiobutton(frameOpen, text="(2) Manuel", bg="gray75", font=("Helvetica", 10, "bold"), variable=switch_variable, indicatoron=False, command=lambda: self.Change_etat(2), width=9, value="Manuel") #Manuel
        BoutonManuel.grid(row=3, column=0, padx=10, pady=2)
        BoutonStable = Radiobutton(frameOpen, text="(3) Stable", bg="gray75", font=("Helvetica", 10, "bold"), variable=switch_variable, indicatoron=False, command=lambda: self.Change_etat(3), width=9, value="Stabiliser") #Stabiliser
        BoutonStable.grid(row=4, column=0, padx=10, pady=2)

        # -------------------------------------------------------------------------------------------------------------------- #
        # Frame Mode Stabilisation // Afficher la hauteur du robot
        frameStable = Frame(frameAngleTitre)
        frameStable.grid(sticky="NW", row=3, column=0, padx=10, pady=10)
        frameStable.config(bg="gray55")
        Label(frameStable, text = "Élévation:", fg="lawn green", bg="gray55", font=("Helvetica", 12, "bold")).grid(row=0, column=0, padx=10, pady=2)
        # Ajoute 2 boutons pour varier la hauteur du robot
        BoutonHauteurUp = Button(frameStable, text="Hauteur +", bg="gray75", command=self.btnHauteurUp, width=9)
        BoutonHauteurUp.grid(row=2, column=0, padx=10, pady=2)
        BoutonHauteurDown = Button(frameStable, text="Hauteur -", bg="gray75", command=self.btnHauteurDown, width=9)
        BoutonHauteurDown.grid(row=3, column=0, padx=10, pady=2, )

        # Label de la hauteur updaté par Refresher()
        self.CurrentHauteur = Label(frameStable, text=com.hauteur, bg="DarkSeaGreen1", font=("Helvetica", 10, "bold"))
        self.CurrentHauteur.grid(row=1, column=0, padx=10, pady=2)
        # -------------------------------------------------------------------------------------------------------------------- #

         # Frame Quit // Ajoute un frame pour mettre un bouton d'arrêt (colonne = 3
        frameQuit = Frame(self.fenetre)
        frameQuit.grid(sticky="NE", row=0, column=2, padx=10, pady=10)
        frameQuit.config(bg="gray35")
        # Ajoute bouton d'arrêt de l'application. Exécute la fonction exxit()
        BoutonQuit = Button(frameQuit, text="Quitter l'application", fg="blue", bg="gray75", font=("Helvetica", 12, "bold"), command=self.exxit)#com.btnQuit)
        BoutonQuit.grid(row=0, column=0, padx=10, pady=2)

        # -------------------------------------------------------------------------------------------------------------------- #

        # Frame Plan / Orientation // Ajoute frame pour l'orientation (colonne = 2 + 3 grâce à "colunmspan"
        # Utiliser Surf, produit vectorielle de la normal pour générer le plan?
        frameGraph = Frame(self.fenetre)
        frameGraph.grid(sticky="SW", row=0, column=2, padx=10, pady=10, columnspan=1)
        frameGraph.config(bg="gray55")
        Label(frameGraph, text="Orientation du plan:", fg="lawn green", bg="gray55", font=("Helvetica", 12, "bold")).grid(row=0, column=0, padx=10, pady=2)

        fig = plt.figure(figsize=(3.5, 2.9))
        ax = fig.add_subplot(111, projection='3d')
        x = np.linspace(-1, 1, 5)
        y = np.linspace(-1, 1, 5)
        x, y = np.meshgrid(x, y)
        z = x * 0 + com.hauteur
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_zlabel('z')

        # plot figure
        ax.plot_surface(x, y, z, linewidth=0, antialiased=False, shade=True, alpha=0.85)

        w = FigureCanvasTkAgg(fig, frameGraph)
        w.get_tk_widget().grid(row=1, column=0, padx=10, pady=2)



        # -------------------------------------------------------------------------------------------------------------------- #
        # fonction pour refresh certaines valeurs cruciales à l'écran
        def Refresher():

            # Le try/except permet d'éviter d'avoir d'autres caractères autres que des int dans les boîte Entry
            # Si caractère invalide, on écrit 0 dans le moteur
            # La méthode get() permet de lire la valeur entrée
            try:
                com.buf_moteur[0] = int(self.eM1.get())
            except:
                com.buf_moteur[0] = 0
            try:
                com.buf_moteur[1] = int(self.eM2.get())
            except:
                com.buf_moteur[1] = 0
            try:
                com.buf_moteur[2] = int(self.eM3.get())
            except:
                com.buf_moteur[2] = 0
            try:
                com.buf_moteur[3] = int(self.eM4.get())
            except:
                com.buf_moteur[3] = 0
            try:
                com.buf_moteur[4] = int(self.eM5.get())
            except:
                com.buf_moteur[4] = 0
            try:
                com.buf_moteur[5] = int(self.eM6.get())
            except:
                com.buf_moteur[5] = 0
            try:
                com.buf_moteur[6] = int(self.eM7.get())
            except:
                com.buf_moteur[6] = 0
            try:
                com.buf_moteur[7] = int(self.eM8.get())
            except:
                com.buf_moteur[7] = 0
            try:
                com.buf_moteur[8] = int(self.eM9.get())
            except:
                com.buf_moteur[8] = 0

            # Affiche la valeur ACTUELLE du moteur.
            self.CurrentValue1.configure(text=com.moteur[0])
            self.CurrentValue2.configure(text=com.moteur[1])
            self.CurrentValue3.configure(text=com.moteur[2])
            self.CurrentValue4.configure(text=com.moteur[3])
            self.CurrentValue5.configure(text=com.moteur[4])
            self.CurrentValue6.configure(text=com.moteur[5])
            self.CurrentValue7.configure(text=com.moteur[6])
            self.CurrentValue8.configure(text=com.moteur[7])
            self.CurrentValue9.configure(text=com.moteur[8])

            # Affiche la valeur actuelle des angles.
            self.CurrentAngleX.configure(text="x: " + str(com.angle[0]))
            self.CurrentAngleY.configure(text="y: " + str(com.angle[1]))

            # Affiche l'état actuelle de la carte OpenCR
            self.CurrentEtat.configure(text="Mode " + switch_variable.get())

            # Affiche la hauteur actuelle du robot
            self.CurrentHauteur.configure(text="Hauteur actuelle: " + str(com.hauteur))

            # loop la fonction à chaque 250 ms
            self.fenetre.after(250, Refresher)

        Refresher()     # Refresh certaines valeurs continuellement


        self.fenetre.mainloop() # Mainloop du GUI