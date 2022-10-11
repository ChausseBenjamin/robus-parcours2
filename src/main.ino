/*
Projet: DefiDuParcous2
Equipe: P6
Auteurs: Simon Gagné
Description: Programme pour du robot #2 pour le défi du parcours
Date: Derniere date de modification
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */
#include <LibRobus.h> // Essentielle pour utiliser RobUS

/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

// Avance le robot sur une distance
void Avancer(float distance)
{
	// code
	int PULSE_PAR_CM = 3200 / (7.62 * PI); // 3pouces de diametres = 7,62 cm

	int pulseAFaire = distance * PULSE_PAR_CM;
	int pulseFait = 0;
	int nbVerif = 0;
	int nbPulseVouluParIntervalle = 400;
	int intervalleTemps = 100;

	int pulseReelTotalGauche = 0;
	int pulseReelTotalDroit = 0;

	// To be updated
	float kp = 0.0005;
	float ki = 0.0001;

	float previousSpeedGauche = 0.32;
	float previousSpeedDroit = 0.3;
	MOTOR_SetSpeed(LEFT, previousSpeedGauche);
	MOTOR_SetSpeed(RIGHT, previousSpeedDroit);

	while (pulseFait < pulseAFaire)
	{
		delay(intervalleTemps);
		nbVerif++;
		int nbPulseReelGauche = ENCODER_Read(LEFT);
		int nbPulseReelDroit = ENCODER_Read(RIGHT);
		int erreurGauche = nbPulseVouluParIntervalle - nbPulseReelGauche;
		int erreurDroit = nbPulseVouluParIntervalle - nbPulseReelDroit;

		Serial.print("Nb pusle reel : ");
		Serial.print(nbPulseReelDroit);
		Serial.print(" ----- Motor Speed Left: ");
		Serial.print(previousSpeedGauche);
		Serial.print(" ----- Erreur Gauche: ");
		Serial.print(erreurGauche);
		Serial.print("\n");

		int pulseVouluTotal = nbPulseVouluParIntervalle * nbVerif;
		pulseReelTotalGauche += nbPulseReelGauche;
		pulseReelTotalDroit += nbPulseReelDroit;
		ENCODER_Reset(LEFT);
		ENCODER_Reset(RIGHT);
		int erreurTotalGauche = pulseVouluTotal - pulseReelTotalGauche;
		int erreurTotalDroit = pulseVouluTotal - pulseReelTotalGauche;

		float correctionGauche = erreurGauche * kp + erreurTotalGauche * ki;
		float correctionDroit = erreurDroit * kp + erreurTotalDroit * ki;

		float newSpeedGauche = previousSpeedGauche + correctionGauche;
		float newSpeedDroit = previousSpeedDroit + correctionDroit;
		MOTOR_SetSpeed(LEFT, newSpeedGauche);
		MOTOR_SetSpeed(RIGHT, newSpeedDroit);

		previousSpeedGauche = newSpeedGauche;
		previousSpeedDroit = newSpeedDroit;
		pulseFait += nbPulseReelDroit;
	}

	MOTOR_SetSpeed(LEFT, 0);
	MOTOR_SetSpeed(RIGHT, 0);
	ENCODER_Reset(LEFT);
	ENCODER_Reset(RIGHT);
}

void Tourner(int degree, int cote)
{
	int moteur = LEFT;
	if (cote == LEFT)
	{
		moteur = RIGHT;
	}
	double nbPulses = 0;
	// Serial.println(nbPulses);
	// bPulses = (910 * (asin((degree*(M_PI / 180.0))/2))/(M_PI / 180.0));
	// Serial.println(nbPulses);
	nbPulses = 3840; // 1 roue
	nbPulses = 3700; // 2 roues

	//float arc  = angle*rayon;
	nbPulses = (3840 / 90) * degree;
	int i = 0;

	while (i <= nbPulses)
	{
		Serial.println(nbPulses);
		MOTOR_SetSpeed(moteur, 0.3);
		// MOTOR_SetSpeed(1, -0.3);
		i += ENCODER_ReadReset(moteur);
	}

	MOTOR_SetSpeed(moteur, 0);
	// MOTOR_SetSpeed(1, 0);
}



void Faire180()
{
	double nbPulses = 0;
	int i = 0;
	//nbPulses = 3620; //Robot A
	nbPulses = 3950; //Robot B
	while (i <= nbPulses)
	{
		Serial.println(nbPulses);
		MOTOR_SetSpeed(0, 0.2);
		MOTOR_SetSpeed(1, -0.2);
		i += ENCODER_ReadReset(0);
	}
  
  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
  ENCODER_Reset(LEFT);
  ENCODER_Reset(RIGHT);
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
	delay(100); // Delais pour décharger le CPU
	if (ROBUS_IsBumper(REAR))
	{
		// Différentes parties du parcours

		//Robot B
		Avancer(111);
		Tourner(90, LEFT);
		Avancer(66);
		Tourner(90, RIGHT);
		Avancer(80);
		Tourner(47, RIGHT);
		Avancer(160);
		Tourner(90, LEFT);
		Avancer(39);
		Tourner(45, RIGHT);
		Avancer(105);
		delay(500);
		Faire180();
		delay(500);
		Avancer(105);
		Tourner(45, LEFT);
		Avancer(39);
		Tourner(92, RIGHT);
		Avancer(160);
		Tourner(47, LEFT);
		Avancer(80);
		Tourner(90, LEFT);
		Avancer(66);
		Tourner(90, RIGHT);
		Avancer(111);

		//Faire180();

		while (true)
		{
			/* do nothing --- needed to stop "loop" */
		}
	}
}