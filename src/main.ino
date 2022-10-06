/*
Projet: Le nom du script
Equipe: Votre numero d'equipe
Auteurs: Les membres auteurs du script
Description: Breve description du script
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <math.h>


/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces



/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void Tourner(int degree)
{
  double nbPulses = 0;
  //Serial.println(nbPulses);
  //bPulses = (910 * (asin((degree*(M_PI / 180.0))/2))/(M_PI / 180.0)); 
  //Serial.println(nbPulses);
  nbPulses = 3840; //1 roue
  nbPulses = 3700; //2 roues

  nbPulses = (3840/90)*degree;
  int i = 0;

  while (i <= nbPulses)
  {
    Serial.println(nbPulses);
    MOTOR_SetSpeed(0, 0.3);
    //MOTOR_SetSpeed(1, -0.3);
    i += ENCODER_ReadReset(0);
  }
  
  MOTOR_SetSpeed(0, 0);
  //MOTOR_SetSpeed(1, 0);
} 


/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup()
{
  BoardInit();
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() 
{
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
  //Test pour commit via VS Code
  //test
  Serial.println("test");
  //Tourner(90);
  delay(2000);
  Tourner(45);
}