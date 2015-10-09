#!/usr/bin/python

ip=["192.168.0.24","192.168.0.24","192.168.0.24"]
import os
import sys
sys.path.insert(0,'/usr/lib/python2.7/bridge')

from time import sleep

from bridgeclient import BridgeClient as bridgeclient
value=bridgeclient()

def relay(numRelais):
    nom='Relais'+str(numRelais)
    value.put(nom,'0')
    sleep(1)
    value.put(nom,'1')
    print("Commande du Relais {} pendant 5s".format(nom))
    sleep(5)
    value.put(nom,'0')
    print("Relais au repos")

def temp():
    temp=value.get('Temperature')
    return temp


def afficheLog():
    try:
        f=open('/root/script/log.log',"r")
        lin=f.readlines()
        f.close()
        for i in lin:
            print("{}".format(i))
    except:
        print("fichier /root/script/log.log inexistant")



intRel=0
os.system('clear')
while True:

        print("MENU:")
        print("1: action sur le Relais 1")
        print("2: action sur le relais 2")
        print("3: voir temperature")
        print("4: voir les logs")
        print("5: sortir")
        rel=input("Votre choix : ")
        os.system('clear')
        try:
                intRel=int(rel)
                if (intRel==1):
                    relay(1)
                elif (intRel==2):
                    relay(2)
                elif (intRel==3):
                    print("\nTemperature: {} degres Celsius\n".format(temp()))
                elif (intRel==4):
                    afficheLog()
                else:
                    break

        except:
                print("ERREUR DE SAISIE!!!!\r\n")
                intRel=0
        rel=''
        intRel=0
