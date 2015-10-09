//V1
#include <Bridge.h>
#include <stdio.h>
#include <OneWire.h> // Inclusion de la librairie OneWire
#include <DallasTemperature.h>
 
#define BROCHE_ONEWIRE 10 // Broche utilisÃƒÂ©e pour le bus 1-Wire ds18B20
#define BROCHE_RELAIS1 13 //broche relais 1
#define BROCHE_RELAIS2 12 //broche relais 2
 
OneWire ds(BROCHE_ONEWIRE); // CrÃƒÂ©ation de l'objet OneWire ds18B20
 
// Pass our oneWire reference to Dallas Temperature. ds18B20
DallasTemperature sensors(&ds);
 
// on definie une variable pour l'etat precedent du relais
char ValRelais1[2];
char ValRelais2[2];
char temp;
String stringVal="";
 
void setup() {
  // Zero out the memory we're using for the Bridge.
  memset(ValRelais1, 0, 2);
  memset(ValRelais2, 0, 2);
  //on definie le pin BROCHE_RELAIS1 en sortie pour la commande du relais 1
  pinMode(BROCHE_RELAIS1, OUTPUT); 
  digitalWrite(BROCHE_RELAIS1, 0);     // on change l'etat de BROCHE_RELAIS a 0
  
  //on definie le pin BROCHE_RELAIS2 en sortie pour la commande du relais 2
  pinMode(BROCHE_RELAIS2, OUTPUT); 
  digitalWrite(BROCHE_RELAIS2, 0);     // on change l'etat de BROCHE_RELAIS a 0
  
  // on demarre la passerelle vers python
  Bridge.begin();
  // on demarre la passerele pour le DS18B20
  sensors.begin();
    // start serial port
  Serial.begin(9600);
  Serial.println("ARDUNO Yun Relais IP");
}

//function to extract decimal part of float
long getDecimal(float val){
  int intPart = int(val);
  long decPart = 1000*(val-intPart);      //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places
                                          //Change to match the number of decimal places you need
  if(decPart>0)return(decPart);           //return the decimal part of float number if it is available
  else if(decPart<0)return((-1)*decPart); //if negative, multiply by -1
  else if(decPart=0)return(00);           //return 0 if decimal part of float number is not available
}

void tempExt() {
  sensors.requestTemperatures();                                    // on fait une requete de temperature
  float valTemp=  sensors.getTempCByIndex(0);                       // on recupere cette temperature en Celsuis
  stringVal=String(int(valTemp))+ "."+String(getDecimal(valTemp));  // on converti en chaine de caractere
  Bridge.put("Temperature", stringVal);
  Serial.print("Temperature for Device 1 is: ");
  Serial.print("temp capteur:");
  Serial.println(valTemp);
  //Serial.print("Temp bridge:");
  //Serial.print(stringVal);
    
}

void relais() {
  // on ecrit la valeur de Relais1 sur le pin 13.
  Bridge.get("Relais1", ValRelais1, 2); // on lit la valeur de "RELAIS1" venant de python
  int EntierRelais1= atoi(ValRelais1);  // on convertit en entier
  digitalWrite(BROCHE_RELAIS1, EntierRelais1);     // on change l'etat de BROCHE_RELAIS1
  
  // on ecrit la valeur de Relais2.
  Bridge.get("Relais2", ValRelais2, 2); // on lit la valeur de "RELAIS2" venant de python
  int EntierRelais2= atoi(ValRelais2);  // on convertit en entier
  digitalWrite(BROCHE_RELAIS2, EntierRelais2);     // on change l'etat de BROCHE_RELAIS2
}
 
void loop() {
  //on test et change le relais
  relais();

  //on test la temperature et envoi
  tempExt();
  

  // on attends un peu
  delay(1000);  
}

