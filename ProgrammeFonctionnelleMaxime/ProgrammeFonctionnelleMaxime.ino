float freq, debit = 0, NombreTourSec = 0, pTime = 0, cTime = 0; //Nous définissons toutes les valeurs que nous avons besoin
int period;
int dv ; // vloume d'eau par tour

void setup() //Boucle qui s'exectute une seule fois
{
  Serial.begin(9600); //Initialisation de la communication série
  pinMode(2, INPUT); //Le port 2 est une entré
  attachInterrupt(digitalPinToInterrupt(2), vit, RISING); // Permet de mesurer les impulsions sur le port digital 2, et on execute la boucle vit lorque que la broche passe de l'état BAS vers HAUT (front montant) (C'est la spécificité de RISING)
}

void loop() // La boucle loop s'execute à l'infinie tant que l'arduino est allumé
{
  delay(1000); //On fait une pause de 1 seconde
  //NombreTourSec = 1 / period; // On calcule la fréquence (f= 1/periodenseconde(s)) pour ensuite pouvoir déterminer la vitesse

  dv = 0.0096 * freq + 0,233;
  //Serial.print(debit);//L'arduino affiche la variable "Debit" dans le moniteur série
  //Serial.println(" L/min."); //L'arduino affiche ce message dans le moniteur série puis fais un retour à la ligne
  Serial.println(freq);
}

void vit() //On crée une boucle qui s'appelle vit
{
  cTime = micros();
  period = (cTime - pTime);
  freq = 1000000/period;
  pTime = cTime; 

}
