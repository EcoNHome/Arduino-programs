#define PortDeConnexionCapteurDePresence 2 //Création d'une constante nommé "PortDeConnexionCapteurDePresence" qui stock 2

boolean ValeurDePresence = false; //Création d'une variable qui peut contenir qu'un seul bit, elle s'appelle "ValeurDePresence", elle stocke par défault 0

void setup() //Boucle exécutée une seule fois, au démarrage de l'Arduino
{
    pinMode(PortDeConnexionCapteurDePresence, INPUT); //
    Serial.begin(9600); //Initialisation de la communication série

}

void loop() //Boucle infini
{

  if (Siquelquunesstla()) //Si le résultat de l'exécution de la boucle Siquelquunesstla est égale à 1
  {

    Serial.println("Personne présente"); //Alors, le programme envoie "Personne présente" dans le moniteur série 

  } else { //Sinon ...

    Serial.println("Il y a personne"); //Sinon, le programme envoie "Il y a personne" dans le moniteur série 

  }

 delay(200); // Pause de 0.2 seconde est réalisé par l'Arduino

}


boolean Siquelquunesstla() //Création d'une boucle qui s'appelle "Siquelquunesstla", elle accepte que les variables de type boolean. Elle est exécuté que quand elle est appellé ailleurs dans le programme
{
  ValeurDePresence = digitalRead(PortDeConnexionCapteurDePresence); //Le programme lit la valeur du capteur de présence et le stock dans la variable "ValeurDePresence"
 
  if (ValeurDePresence == HIGH) //Si la valeur de de la variable est égale à 1
  {
    
    return true;
  
  } else
  {
    
    return false;
 
  }
  
}
