import serial
import struct
import glob
import struct
import time
import numpy as np

#arduino = serial.Serial('COM3', 9600)

moteur = [0,0,0,0,0,0,0]
etat = 0


def manuel(moteur1, moteur2):
    print("manuel")
    print(moteur1,moteur2)
    #arduino.write(b'manuel')
    #arduino.write(moteur1)
    #arduino.write(moteur2)

def stop():
    print("stop")
    #arduino.write(b'stop')

def initalisation():
    print("init")
    #arduino.write(b'init')

def lectureArduino():
    print("lA")
    #entete = arduino.readline()
    #if entete==

    #confirmationEtat = arduino.readline()
    #commandeMoteur0 = arduino.readline()

#-----------------------------------------------------------------------------------------







class communicationOpenCr(object):
    """A class to read the serial messages from Arduino. The code running on Arduino
    can for example be the ArduinoSide_LSM9DS0 sketch."""

    def __init__(self, port, SIZE_STRUCT=12, verbose=0):
        self.port = port
        self.SIZE_STRUCT = SIZE_STRUCT
        self.verbose = verbose
        self.latest_values = -1
        self.t = 0
        self.port.flushInput()

    def read_one_value(self):
            data = self.port.read(self.SIZE_STRUCT)
            print(data)
            new_values = struct.unpack('iii', data)
            print(new_values);

    def envoieVersArduino(self, port, moteur):
        #print("Envoie des donnees")
        value = struct.pack('iii', etat, moteur[0], moteur[1])
        self.port.write(value)





portArduino = serial.Serial('COM3', 9600)
Arduino = communicationOpenCr(portArduino)

#Arduino.read_one_value()
#Arduino.envoieVersArduino(arduino, moteur)


