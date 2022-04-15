/* 
 * File:   CB_TX1.h
 * Author: TP_EO_6
 *
 * Created on 15 avril 2022, 09:41
 */

#ifndef CB_TX1_H
#define	CB_TX1_H
void SendMessage(unsigned char* message, int length);

void CB_TX1_Add(unsigned char value);
void SendOne();
unsigned char CB_TX1_IsTranmitting(void);
int CB_TX1_RemainingSize(void);
void __attribute__((interrupt, no_auto_psv))_U1TXInterrupt(void);
unsigned char CB_TX1_Get(void);


#endif	/* CB_TX1_H */

