#include <Wire.h>
#include <Digital_Light_TSL2561.h>
#include <Adafruit_NeoPixel.h>

//PortDeConnexionLuxmetre: I2C
#define PortDeConnexionBandeauLED 6
#define PortDeConnexionBouton A1
#define PortDeConnexionCapteurTemperature 0
#define PortDeConnexionCapteurDePresence 4

#define NombresDeLEDSduBandeau 10

unsigned long MilisDuPasse = 0;
const unsigned long TotalMillis = 1000;

int ValeurMesureLuxmetre;
int ValeurMesureCapteurTemperature;
int ValeurDeLaTermistance = 3975;
int TempsEntreChaqueAppuieBoutonSelec = 200;
float ResistanceDuCapteurDeTemperature;
byte TemperatureMesure;
byte ValeurSelecProg = 0;
byte HauteurBandeauDeLeds = 0;
boolean ValeurMesureCapteurDePresence = false;
boolean EtatBoutonSelec = false;


Adafruit_NeoPixel Lampe = Adafruit_NeoPixel(NombresDeLEDSduBandeau, PortDeConnexionBandeauLED, NEO_GRB + NEO_KHZ800);

void setup() {

  Serial.begin(9600);
  Wire.begin();
  Lampe.begin();
  TSL2561.init();

  pinMode(PortDeConnexionBandeauLED, OUTPUT);
  pinMode(PortDeConnexionCapteurTemperature, INPUT);
  pinMode(PortDeConnexionCapteurDePresence, INPUT);

}

void loop()
{

  EtatBoutonSelec = analogRead(PortDeConnexionBouton);

  if (EtatBoutonSelec == 1)
  {
    ValeurSelecProg ++;
    delay(TempsEntreChaqueAppuieBoutonSelec);
  }

  Serial.println(ValeurSelecProg);

  if (ValeurSelecProg = 0)
  {

      Serial.println("0");

      ValeurMesureLuxmetre = TSL2561.readVisibleLux();
      HauteurBandeauDeLeds = map(ValeurMesureLuxmetre, 0, 400, 0, 10);
      Lampe.show();

      delay(70);

      for ( int valeur = 0; valeur < HauteurBandeauDeLeds; valeur ++)
      {

        Lampe.setPixelColor(valeur, 238, 223, 156);
        Lampe.setPixelColor(valeur + 3, 0, 0, 0);

      }

  } else if (ValeurSelecProg = 1)
  {

      Serial.println("1");

  } else if (ValeurSelecProg = 2)
  {

      Serial.println("2");

  } else
  {

      ValeurSelecProg = 0;
  }



}

void mesure()
{
  unsigned long MillisActuel = millis();
  if (MillisActuel - MilisDuPasse >= TotalMillis)
  {

    MilisDuPasse = MillisActuel;
    ValeurMesureLuxmetre = TSL2561.readVisibleLux();

    ValeurMesureCapteurTemperature = analogRead(PortDeConnexionCapteurTemperature);
    ResistanceDuCapteurDeTemperature = (float)(1023 - ValeurMesureCapteurTemperature) * 10000 / ValeurMesureCapteurTemperature;
    TemperatureMesure = 1 / (log(ResistanceDuCapteurDeTemperature / 10000) / ValeurDeLaTermistance + 1 / 298.15) - 273.15;

    ValeurMesureCapteurDePresence = digitalRead(PortDeConnexionCapteurDePresence);

  }


}
