#!/usr/bin/python

ip=["192.168.0.24","192.168.0.24","192.168.0.24"] //adresses a tester
import os
import sys
sys.path.insert(0,'/usr/lib/python2.7/bridge')

from time import sleep

from bridgeclient import BridgeClient as bridgeclient
value=bridgeclient()
compteur=0

def relais():
        for idx in range(0,2):
                value.put('Relais','0')
                sleep(1)
                value.put('Relais','1')
                sleep(1)
        value.put('Relais','0')

def pingTo(ip):
        u=os.popen("ping -c 1 "+ip)
        result=u.read()
        print("ping execute")
        if result.count("0 packets")!=0 or result.count("100% packet")!=0:
                print("erreur de ping " + addr)
                return False
        return True

while True:
        print("on boucle")
        if compteur<2:
                print(str(compteur))
                testall=0
                for addr in ip:
                        if not pingTo(addr): testall+=1
                        print("testall de {}:"+str(testall))
                        sleep(1)
                if testall>=len(ip)-1:
                        print(relais)
                        relais()
                        compteur+=1
                print("on attends 300s (5min) pour le prochain")
                sleep(3)
        else:
                compteur=0
                print("ca fait deux fois que c'est naze on arrete pendant 3600s ou 1h")
                sleep(120)

