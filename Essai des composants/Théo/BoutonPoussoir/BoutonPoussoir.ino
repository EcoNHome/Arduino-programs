#define PortDeConnexionDuBouton = 2; //Création d'une constante nommé "PortDeConnexionDuBouton" qui stock le nombre 2, pour enregistrer le numéro du port
boolean EtatDuBouton = false; //Création de la variable EtatDuBouton et elle contient le nombre 0 

void setup() //Boucle d'initialisation, elle est éxécutée qu'une seule fois, au démarrage de la carte
{
  
  pinMode(PortDeConnexionDuBouton, INPUT); //Nous définissons que le port de connexion du bouton est une sortie
  
}

void loop() // Boucle infini
{
  
  EtatDuBouton = digitalRead(PortDeConnexionDuBouton); //Le programme lit l'état du bouton et le stock dans la variable "EtatBouton"

  if (EtatDuBouton == HIGH) //Si l'état du bouton est égale à 1
  {

    Serial.println("Bouton appuyé"); // Alors, le programme envoie "Bouton appuyé" dans le moniteur série avec un retour série chariot

  } else //Sinon...
  { 

    Serial.println("Bouton non appuyé"); //Le programme envoie "Bouton non appuyé" dans le moniteur série avec un retour chariot

  }
}
