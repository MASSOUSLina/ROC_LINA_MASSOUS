/* 
 * File:   main.h
 * Author: TP_EO_6
 *
 * Created on 25 février 2022, 10:43
 */

#ifndef MAIN_H
#define	MAIN_H
#define FCY 40000000
#define STATE_ATTENTE 0
#define STATE_ATTENTE_EN_COURS 1
#define STATE_AVANCE 2
#define STATE_AVANCE_EN_COURS 3
#define STATE_TOURNE_GAUCHE 4
#define STATE_TOURNE_GAUCHE_EN_COURS 5
#define STATE_TOURNE_DROITE 6
#define STATE_TOURNE_DROITE_EN_COURS 7
#define STATE_TOURNE_SUR_PLACE_GAUCHE 8
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 9
#define STATE_TOURNE_SUR_PLACE_DROITE 10
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 11
#define STATE_ARRET 12
#define STATE_ARRET_EN_COURS 13
#define STATE_RECULE 14
#define STATE_RECULE_EN_COURS 15
#define PAS_D_OBSTACLE 0
#define OBSTACLE_A_GAUCHE 1
#define OBSTACLE_A_DROITE 2
#define OBSTACLE_EN_FACE 3
#define OBSTACLE_EXTREMES 4
 #define OBSTACLE_couloir_DROITE 5
#define OBSTACLE_couloir_GAUCHE 6
#define STATE_COULOIRE 16
#define STATE_COULOIRE_EN_COURS 17
#define STATE_COULOIRE_DROIT 18
#define STATE_COULOIRE_DROIT_EN_COURS 19
#define STATE_COULOIRE_GAUCHE 20 
#define STATE_COULOIRE_GAUCHE_EN_COURS 21 
void SetNextRobotStateInAutomaticMode();
void OperatingSystemLoop(void);
 
extern unsigned char stateRobot;
//void SetNextRobotStateInAutomaticMode();
extern unsigned char nextStateRobot;
#endif	/* MAIN_H */



