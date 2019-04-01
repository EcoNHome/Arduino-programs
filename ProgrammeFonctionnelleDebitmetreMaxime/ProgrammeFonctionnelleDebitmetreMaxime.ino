float frequence, pTime = 0, cTime = 0; //Nous définissons toutes les valeurs que nous avons besoin
int period; //On definie la variable period
float dv ; // Volume d'eau par tour

void setup() //Boucle qui s'exectute une seule fois
{
  
  Serial.begin(9600); //Initialisation de la communication série
  pinMode(2, INPUT); //Le port 2 est une entré
  attachInterrupt(digitalPinToInterrupt(2), freq, RISING); // Permet de mesurer les impulsions sur le port digital 2, et on execute la boucle freq lorque que la broche passe de l'état BAS vers HAUT (front montant) (C'est la spécificité de RISING)

}

void loop() // La boucle loop s'execute à l'infinie tant que l'arduino est allumé
{
  
  delay(1000); //On fait une pause de 1 seconde
  dv = 0.0096 * frequence + 0,233; //Calcul du débit volumique à partir de la fréquence calculé grâce à la fonction déterminé avec des mesures
  Serial.print(dv); //afficher le débit volumique
  Serial.println(" L/min."); //L'arduino affiche ce message dans le moniteur série puis fais un retour à la ligne
  
}

void freq() //On crée une boucle qui s'appelle freq
{
  
  cTime = micros(); //La fonction micros renvoie le nombre de micro seconde depuis que arduino à démarré le programme
  period = (cTime - pTime); // period sera égale à la soustraction des deux variables
  frequence = 1000000/period; // 1 000 000 = 1 secondes puis on calcule le fréquences avec F = 1/T
  pTime = cTime; // remise à 0 du compteur pour capturé la différence de temps au prochain tour
  
}
