#include <Adafruit_NeoPixel.h>
//#include <Bridge.h>
//#include <HttpClient.h>

#define PortDeConnexionBandeauLED 6
#define NombresDeLEDSduBandeau 10
#define PortDeConnexionBouton 4


unsigned long MilisDuPasse = 0;
const unsigned long TotalMillis = 1000;


byte ValeurSelecProg = 0;
boolean EtatBoutonSelec = false;
int TempsEntreChaqueAppuieBoutonSelec = 200;

int ValeurPlus;

int ValeurLuminosite;
byte ValeurLuminositeSurBandeauDeLED;
int ValeurDebit;
byte ValeurTemperature;


Adafruit_NeoPixel LampeIndicative = Adafruit_NeoPixel(NombresDeLEDSduBandeau, PortDeConnexionBandeauLED, NEO_GRB + NEO_KHZ800);
//HttpClient ReceptionDesDonnees;             //Au lieu d'avoir HttpClient.get(); nous pouvons avoir Arduino.get();.


void setup()
{

  Serial.begin(9600);
  LampeIndicative.begin();
  //Bridge.begin();

}

void loop()
{

  EtatBoutonSelec = digitalRead(PortDeConnexionBouton);

  if (EtatBoutonSelec == 1)
  {
    ValeurSelecProg ++;
    delay(TempsEntreChaqueAppuieBoutonSelec);
  }

  Serial.println(ValeurSelecProg);

  switch (ValeurSelecProg)
  {

    case 0: //Luminosite

      RecuperationDesDonnees();
      ValeurLuminosite = 240;

      ValeurLuminositeSurBandeauDeLED = map(ValeurLuminosite, 0, 400, 0, NombresDeLEDSduBandeau);


      if (ValeurLuminositeSurBandeauDeLED < 3 )
      {




        for (int ValeurPlus = ValeurLuminositeSurBandeauDeLED; ValeurPlus < 3; ValeurPlus   ++)
        {

          LampeIndicative.setPixelColor(ValeurPlus, 255, 0, 0);
          LampeIndicative.setPixelColor(ValeurPlus + 3, 0, 0, 0);
          LampeIndicative.show();

        }
        if (ValeurLuminositeSurBandeauDeLED < 7 && ValeurLuminositeSurBandeauDeLED > 3 )
        {

          ValeurPlus = ValeurLuminositeSurBandeauDeLED;


          for ( int ValeurPlus = 3; ValeurPlus < 7; ValeurPlus ++)
          {

            LampeIndicative.setPixelColor(ValeurPlus, 0, 255, 0);
            LampeIndicative.setPixelColor(ValeurPlus + 3, 0, 0, 0);
            LampeIndicative.show();

          }


        }


        if (ValeurLuminositeSurBandeauDeLED < 7 && ValeurLuminositeSurBandeauDeLED < 10)
        {

          ValeurPlus = ValeurLuminositeSurBandeauDeLED;


          for ( int ValeurPlus = 7; ValeurPlus < 10; ValeurPlus ++)
          {

            LampeIndicative.setPixelColor(ValeurPlus, 0, 0, 255);
            LampeIndicative.setPixelColor(ValeurPlus + 3, 0, 0, 0);
            LampeIndicative.show();

          }

        }


        if (ValeurLuminositeSurBandeauDeLED == 10)
        {

          LampeIndicative.setPixelColor(NombresDeLEDSduBandeau, 255, 0, 0);
          LampeIndicative.show();
          delay(100);
          LampeIndicative.setPixelColor(NombresDeLEDSduBandeau, 255, 0, 0);
          LampeIndicative.show();

        }

      }

      break;

    case 1:

      RecuperationDesDonnees();
      LampeIndicative.setPixelColor(NombresDeLEDSduBandeau, 255, 0, 255);

      break;


    case 2:

      RecuperationDesDonnees();
      LampeIndicative.setPixelColor(NombresDeLEDSduBandeau, 255, 255, 0);

      break;




    case 3:

      ValeurSelecProg = 0;

      break;



  }






}


void RecuperationDesDonnees()
{
  unsigned long MillisActuel = millis();
  if (MillisActuel - MilisDuPasse >= TotalMillis)
  {

    MilisDuPasse = MillisActuel;
    ValeurLuminosite = 240;//ReceptionDesDonnees.get("reception.econhome.ovh/data/lightning/");
    ValeurDebit = 150;//ReceptionDesDonnees.get("reception.econhome.ovh/data/flow/");
    ValeurTemperature = 23;//ReceptionDesDonnees.get("reception.econhome.ovh/data/temperature/");

  }


}
