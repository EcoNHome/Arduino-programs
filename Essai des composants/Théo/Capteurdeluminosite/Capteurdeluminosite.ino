#include <Wire.h> //Intégration de la librairie "Wire.h" dans le programme
#include <Digital_Light_TSL2561.h> //Intégration de la librairie "Digital_Light_TSL2561.h" dans le programme

void setup() //Boucle exécutée une seule fois, au démarrage de l'Arduino
{ 
  Wire.begin(); //Initialisation de la librairie "Wire.h"
  Serial.begin(9600); //Initialisation de la communication série
  TSL2561.init(); //Initialisation de la librairie "Digital_Light_TSL2561"
}

void loop() //Boucle infini
{
  Serial.print("Valeur de luminosité: "); //Le programme envoie "Valeur de luminosité: " dans le moniteur série 
  Serial.println(TSL2561.readVisibleLux()); //Le programme envoie "TSL2561.readVisibleLux()" dans le moniteur série
  delay(1000); // Pause de 1 seconde est réalisé par l'Arduino
}
