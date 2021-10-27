#ifndef __HARDWAREIIC_H
#define __HARDWAREIIC_H


void Start();
void SendData(char dat);
void RecvACK();
char RecvData();
void SendACK();
void SendNAK();
void Stop();
void Delay(); 
void IIC_Init(void);


#endif