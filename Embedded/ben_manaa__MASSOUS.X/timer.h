#ifndef TIMER_H
#define TIMER_H
void InitTimer23 ( void );
void InitTimer1 ( void );
void SetFreqTimer1(float freq);
extern unsigned long timestamp ;
void InitTimer4 ( void );
void SetFreqTimer4(float freq);
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
#endif 

