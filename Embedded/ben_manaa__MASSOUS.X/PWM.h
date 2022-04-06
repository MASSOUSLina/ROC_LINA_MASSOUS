/* 
 * File:   PWM.h
 * Author: TP_EO_6
 *
 * Created on 27 octobre 2021, 11:36
 */

#ifndef PWM_H
#define	PWM_H

#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1

void InitPWM(void);
void PWMUpdateSpeed(void);
void PWMSetSpeedConsigne(float vitessePourcents , unsigned char nbMoteur);

#endif