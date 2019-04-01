#include <Wire.h> //Intégration de la librairie "Wire"
#include <Bridge.h> //Intégration de la librairie "Bridge"
#include <HttpClient.h> //Intégration de la librairie "HttpClient"
#include <Digital_Light_TSL2561.h> //Intégration de la librairie "Digital_Light_TSL2561"

//PortDeConnexionLuxmetre: I2C
#define PortDeConnexionLampe 6 //Création d'une constante nommée "PortDeConnexionLampe" qui stocke 6
#define PortDeConnexionBouton 4 //Création d'une constante nommée "PortDeConnexionBouton" qui stocke 4
#define PortDeConnexionCapteurTemperature 0 //Création d'une constante nommée "PortDeConnexionCapteurTemperature" qui stocke 0
#define PortDeConnexionCapteurDePresence 2 //Création d'une constante nommée "PortDeConnexionCapteurDePresence" qui stocke 2

boolean ValeurDePresence = false; //Création d'une varaible qui peut stocker que 0 ou 1 qui s'appelle "ValeurDePresence" qui stocke 0
boolean EtatBoutonAllumageLampe = false; //Création d'une varaible qui peut stocker que 0 ou 1 qui s'appelle "EtatBoutonAllumageLampe" qui stocke 0

byte ValeurAllumageLampe; //Création d'une varaible qui peut stocker que 0 à 255 qui s'appelle "ValeurAllumageLampe"

unsigned long MilisDuPasse = 0; //Création d'une variable nommé MilisDuPasse qui stocke 0, unsigned long permet d'avoir un nombre que positif, il va de 0 à 2 147 483 647 
const unsigned int TotalMillis = 30000; //Création d'une constante nommé TotalMillis qui stocke 30000, const unsigned long permet d'avoir une constante que positif qui ne change pas

int ValeurMesureLuxmetre; //Création d'une variable ValeurMesureLuxmetre qui peut stocker de 0 à 32 767  
int ValeurMesureLuxmetre0a400; //Création d'une variable ValeurMesureLuxmetre0a400
int ValeurMesureLuxmetre0a400aLampe; //Création d'une variable ValeurMesureLuxmetre0a400aLampe
int TempsEntreChaqueAppuieBoutonAllumageLampe = 200; //Création d'une variable TempsEntreChaqueAppuieBoutonAllumageLampe

String URL; //Création d'une chaîne de caractère
String URLpresence = "http://api.econhome.ovh/attendance/";
String URLluminosite = "http://api.econhome.ovh/lightning/";

String essai;

HttpClient Arduino; //Au lieu d'avoir HttpClient.get(); nous pouvons avoir Arduino.get();.

void setup() //Boucle éxécutée une seule fois
{
  Serial.begin(9600); //Initialisation d'une communication série à une vitessd de 9600 bauds
  Wire.begin(); //Initialisation de la librairie Wire
  Bridge.begin(); //Initialisation de la librairie Bridge
  TSL2561.init(); //Initialisation de la commincation avec le capteur de luminosité
  pinMode(PortDeConnexionLampe, OUTPUT); //Défini le port 6 comme sortie
  pinMode(PortDeConnexionBouton, INPUT); //Défini le port 4 comme entrée
  pinMode(PortDeConnexionCapteurTemperature, INPUT); //Défini le port 0 comme entrée
  pinMode(PortDeConnexionCapteurDePresence, INPUT); //Défini le port 2 comme entrée
}

void loop() //Boucle infini
{

  EtatBoutonAllumageLampe = digitalRead(PortDeConnexionBouton); //Le programme lit la valeur sur le port de connexon du bouton et stocke la valeur dans la variable EtatBoutonAllumageLampe


  if (EtatBoutonAllumageLampe == 1) //Si la valeur stocker dans EtatBoutonAllumageLampe est égale à 1.. 
  {
    ValeurAllumageLampe ++; //Alors, on incremente ValeurAllumageLampe de 1   
    delay(TempsEntreChaqueAppuieBoutonAllumageLampe); //Et, on fait une pause 200 ms
  }


  switch (ValeurAllumageLampe) //Explication à l'oral
  {

    case 0:

      mesure();
      EnvoiesDesDonnees(); 

      if (essai == "true")
      {
        ValeurMesureLuxmetre0a400 = min(ValeurMesureLuxmetre, 400);
        ValeurMesureLuxmetre0a400aLampe = map(ValeurMesureLuxmetre0a400, 0, 400, 1023, 0);
        Serial.println(ValeurMesureLuxmetre0a400);
        analogWrite(PortDeConnexionLampe, ValeurMesureLuxmetre0a400aLampe);


      } else
      {
        analogWrite(PortDeConnexionLampe, 0);

      }
      delay(200);


      break;

    case 1:

      mesure();
      analogWrite(PortDeConnexionLampe, 1023);


      break;

    case 2:

      ValeurAllumageLampe = 0;

      break;

  }


}


void mesure()
{

  ValeurMesureLuxmetre = TSL2561.readVisibleLux();

  if (Siquelquunesstla())
  {
    essai = "true";
  } else {
    essai = "false";

  }


}

boolean Siquelquunesstla()
{
  ValeurDePresence = digitalRead(PortDeConnexionCapteurDePresence);
  if (ValeurDePresence == HIGH) //if the sensor value is HIGH?
  {
    return true;
  } else
  {
    return false;
  }
}

void EnvoiesDesDonnees()
{
  unsigned long MillisActuel = millis();
  if (MillisActuel - MilisDuPasse >= TotalMillis)
  {

    MilisDuPasse = MillisActuel;
    URL = URLluminosite + ValeurMesureLuxmetre;
    Arduino.get(URL);
    URL = URLpresence + essai;
    Arduino.get(URL);

  }


}
