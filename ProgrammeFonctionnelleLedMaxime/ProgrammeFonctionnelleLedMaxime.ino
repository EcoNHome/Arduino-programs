
#include <ChainableLED.h> //On inclut la librairie ChainableLed

#define NUM_LEDS 1  //Cela indique le nombre de led que nous avons 1 dans notre cas

ChainableLED leds(6, 7, NUM_LEDS); //On definit les ports sur lesquels la led est branchée

void setup() //Boucle qui est executée une seule fois au démarrage
{
  
}


void loop()
{

  leds.setColorRGB(0, 255, 0, 0); //On choisit une couleur pour la led ici c'est du rouge 
  delay(100); //Pause d'un dixième de seconde
  leds.setColorRGB(0, 0, 0, 0); //On choisit on ne met aucune couleur donc la Led est éteinte
  delay(100); //Pause d'un dixième de seconde

}
