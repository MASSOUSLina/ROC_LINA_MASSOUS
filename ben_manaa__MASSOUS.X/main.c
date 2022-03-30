#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "PWM.h"
#include "ADC.h"
#include "Robot.h"
#include "main.h"

int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();

    /****************************************************************************************************/
    // Configuration des entrées sorties
    /****************************************************************************************************/
    InitIO();
    
   
    LED_BLANCHE = 1;
    LED_BLEUE = 1;
    LED_ORANGE = 1;

    /****************************************************************************************************/
    // Boucle Principale
    /****************************************************************************************************/
    InitTimer23();
    InitTimer1();
    InitTimer4();
    InitPWM();
    InitADC1();
    //PWMSetSpeed(20,MOTEUR_GAUCHE);


    while (1) {
        if (ADCIsConversionFinished() == 1) {

            unsigned int * result = ADCGetResult();
            ADCClearConversionFinishedFlag();
            float volts3 = ((float) result [0]*3.3 / 4096 * 3.2);
            robotState.distanceTelemetreExtremDroit = 34 / volts3 - 5;
            float volts4 = ((float) result [1]*3.3 / 4096 * 3.2);
            robotState.distanceTelemetreDroit = 34 / volts4 - 5;
            float volts0 = ((float) result [2]*3.3 / 4096 * 3.2);
            robotState.distanceTelemetreCentre = 34 / volts0 - 5;
            float volts2 = ((float) result [3])*3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremGauche = 34 / volts2 - 5;
            float volts1 = ((float) result [4]*3.3 / 4096 * 3.2);
            robotState.distanceTelemetreGauche = 34 / volts1 - 5;
//            

            if (robotState.distanceTelemetreExtremDroit < 30 || robotState.distanceTelemetreDroit < 30) {
                LED_ORANGE = 1;
            } else
                LED_ORANGE = 0;            
            if (robotState.distanceTelemetreCentre < 30) {
                LED_BLEUE = 1;
            } else
                LED_BLEUE = 0;
            if (robotState.distanceTelemetreGauche < 30 || robotState.distanceTelemetreExtremGauche < 30){
                LED_BLANCHE=1;
            }else
                LED_BLANCHE=0;            
        }
    }
}
    unsigned char stateRobot;

    void OperatingSystemLoop(void) {
        switch (stateRobot) {
            case STATE_ATTENTE:
                timestamp = 0;
                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                stateRobot = STATE_ATTENTE_EN_COURS;

            case STATE_ATTENTE_EN_COURS:
                if (timestamp > 1000)
                    stateRobot = STATE_AVANCE;
                break;

            case STATE_AVANCE:
                PWMSetSpeedConsigne(30, MOTEUR_DROIT);
                PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
                stateRobot = STATE_AVANCE_EN_COURS;
                break;
            case STATE_AVANCE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;

            case STATE_TOURNE_GAUCHE:
                PWMSetSpeedConsigne(30, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
                break;
            case STATE_TOURNE_GAUCHE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;

            case STATE_TOURNE_DROITE:
                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_DROITE_EN_COURS;
                break;
            case STATE_TOURNE_DROITE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;

            case STATE_TOURNE_SUR_PLACE_GAUCHE:
                PWMSetSpeedConsigne(15, MOTEUR_DROIT);
                PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
                break;
            case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;

            case STATE_TOURNE_SUR_PLACE_DROITE:
                PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
                PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
                stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
                break;
            case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
                
            case STATE_COULOIRE:
                PWMSetSpeedConsigne(20, MOTEUR_DROIT);
                PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
                break;
            case STATE_COULOIRE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
                case STATE_COULOIRE_DROIT:
                PWMSetSpeedConsigne(20, MOTEUR_DROIT);
                PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
                break;
            case STATE_COULOIRE_DROIT_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
                case STATE_COULOIRE_GAUCHE:
                PWMSetSpeedConsigne(0, MOTEUR_DROIT);
                PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
                break;
            case STATE_COULOIRE_GAUCHE_EN_COURS:
                SetNextRobotStateInAutomaticMode();
                break;
            default:
                stateRobot = STATE_ATTENTE;
                break;
        }
    }

    unsigned char nextStateRobot = 0;

    void SetNextRobotStateInAutomaticMode() { 
        
        unsigned char sensorState = 0;
        
        if(robotState.distanceTelemetreExtremGauche < 20)
            sensorState |= 0b10000;
        if(robotState.distanceTelemetreGauche < 30)
            sensorState |= 0b01000;
        if(robotState.distanceTelemetreCentre < 30)
            sensorState |= 0b00100;
        if(robotState.distanceTelemetreDroit < 30)
            sensorState |= 0b00010;
        if(robotState.distanceTelemetreExtremDroit < 20)
            sensorState |= 0b00001;
        
        switch(sensorState)
        {
            case 0b00000:
                nextStateRobot = STATE_AVANCE;
                break;
            case 0b00001:
                nextStateRobot = STATE_TOURNE_GAUCHE;
                break;
        }
        
//        unsigned char positionObstacle = PAS_D_OBSTACLE;
//
//        //Détermination de la position des obstacles en fonction des télémètres
//        if (robotState.distanceTelemetreDroit < 30 && robotState.distanceTelemetreCentre > 20 && robotState.distanceTelemetreGauche > 30) { //Obstacle à droite
//            positionObstacle = OBSTACLE_A_DROITE;
//        } else if (robotState.distanceTelemetreDroit > 30 && robotState.distanceTelemetreCentre > 20 && robotState.distanceTelemetreGauche < 30) //Obstacle à gauche
//        {
//            positionObstacle = OBSTACLE_A_GAUCHE;
//        } else if (robotState.distanceTelemetreCentre < 30) //Obstacle en face
//        {
//            positionObstacle = OBSTACLE_EN_FACE;
//        } else if (robotState.distanceTelemetreDroit > 30 && robotState.distanceTelemetreCentre > 30 && robotState.distanceTelemetreGauche > 30) //pas d?obstacle
//        {
//            positionObstacle = PAS_D_OBSTACLE;
//        } else if (robotState.distanceTelemetreExtremDroit < 20 && robotState.distanceTelemetreExtremGauche < 20) //couloire
//        {
//            positionObstacle = OBSTACLE_EXTREMES;
//        }
//        else if (robotState.distanceTelemetreExtremDroit < 20 ) //couloire doit
//        {
//            positionObstacle = OBSTACLE_A_DROITE;
//        }
//        else if ( robotState.distanceTelemetreExtremGauche < 20) //couloire gauche
//        {
//            positionObstacle = OBSTACLE_A_GAUCHE;
//        }
//
//        //Détermination de l?état à venir du robot
//        if (positionObstacle == PAS_D_OBSTACLE) {
//            nextStateRobot = STATE_AVANCE;
//        } else if (positionObstacle == OBSTACLE_A_DROITE) {
//            nextStateRobot = STATE_TOURNE_GAUCHE;
//        } else if (positionObstacle == OBSTACLE_A_GAUCHE) {
//            nextStateRobot = STATE_TOURNE_DROITE;
//        } else if (positionObstacle == OBSTACLE_EN_FACE) {
//            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
//        }
//        else if (positionObstacle == OBSTACLE_EXTREMES) {
//            nextStateRobot = STATE_COULOIRE;
//        }
//        else if (positionObstacle == OBSTACLE_couloir_DROITE) {
//            nextStateRobot = STATE_TOURNE_GAUCHE;
//        }
//        else if (positionObstacle == OBSTACLE_couloir_GAUCHE) {
//            nextStateRobot =  STATE_TOURNE_DROITE;
//        }

        //Si l?on n?est pas dans la transition de l?étape en cours
        if (nextStateRobot != stateRobot - 1) {
            stateRobot = nextStateRobot;
        }
    }


    


