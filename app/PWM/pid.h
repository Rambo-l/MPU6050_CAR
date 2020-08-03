#ifndef __PID_H
#define __PID_H
#include "sys.h"


void Xianfu_PID(void);
void Su(void);
int Position_P (int Encoder,int Target);
int Position_PD (int Encoder,int Target);
int Position_PID (int Encoder,int Target);
void pid_control(void);
#endif

