#ifndef __MDREGPOOL_H__
#define __MDREGPOOL_H__


#include "mdtype.h"
#include "mdconfig.h"


typedef struct Register* RegisterHandle;
struct Register
{
    mdU32 addr;
    mdU32 dat;
    RegisterHandle next;
};

typedef struct RegisterPool* RegisterPoolHandle;
struct RegisterPool
{
    RegisterHandle pool;
    //线圈、输入状态、输入寄存器、保持寄存器
    RegisterHandle quickMap[4][REGISTER_POOL_MAX_BUFFER];
    mdU32 curRegisterNumber,maxRegisterNumber;

    mdSTATUS (*mdReadBit)(RegisterPoolHandle handler,mdU32 addr,mdBit *abit) reentrant;
    mdSTATUS (*mdWriteBit)(RegisterPoolHandle handler,mdU32 addr,mdBit abit) reentrant;
    mdSTATUS (*mdReadBits)(RegisterPoolHandle handler,mdU32 addr,mdU32 len,mdBit *bits) reentrant;
    mdSTATUS (*mdWriteBits)(RegisterPoolHandle handler,mdU32 addr,mdU32 len,mdBit *bits) reentrant;
    mdSTATUS (*mdReadU16)(RegisterPoolHandle handler,mdU32 addr,mdU16 *dat) reentrant;
    mdSTATUS (*mdWriteU16)(RegisterPoolHandle handler,mdU32 addr,mdU16 dat) reentrant;
    mdSTATUS (*mdReadU16s)(RegisterPoolHandle handler,mdU32 addr,mdU32 len,mdU16 *dat) reentrant;
    mdSTATUS (*mdWriteU16s)(RegisterPoolHandle handler,mdU32 addr,mdU32 len,mdU16 *dat) reentrant;

    mdSTATUS (*mdReadCoil)(RegisterPoolHandle handler, mdU32 addr, mdBit* abit) reentrant;
    mdSTATUS (*mdReadCoils)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdBit* bits) reentrant;
    mdSTATUS (*mdWriteCoil)(RegisterPoolHandle handler, mdU32 addr, mdBit abit) reentrant;
    mdSTATUS (*mdWriteCoils)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdBit* bits) reentrant; 
    mdSTATUS (*mdReadInputCoil)(RegisterPoolHandle handler, mdU32 addr, mdBit* abit) reentrant;
    mdSTATUS (*mdReadInputCoils)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdBit* bits) reentrant;
    mdSTATUS (*mdWriteInputCoil)(RegisterPoolHandle handler, mdU32 addr, mdBit abit) reentrant;
    mdSTATUS (*mdWriteInputCoils)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdBit* bits) reentrant;
    mdSTATUS (*mdReadInputRegister)(RegisterPoolHandle handler, mdU32 addr, mdU16* dat) reentrant;
    mdSTATUS (*mdReadInputRegisters)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdU16* dat) reentrant;
    mdSTATUS (*mdWriteInputRegister)(RegisterPoolHandle handler, mdU32 addr, mdU16 dat) reentrant;
    mdSTATUS (*mdWriteInputRegisters)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdU16* dat) reentrant;
    mdSTATUS (*mdReadHoldRegister)(RegisterPoolHandle handler, mdU32 addr, mdU16* dat) reentrant;
    mdSTATUS (*mdReadHoldRegisters)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdU16* dat) reentrant;
    mdSTATUS (*mdWriteHoldRegister)(RegisterPoolHandle handler, mdU32 addr, mdU16 dat) reentrant;
    mdSTATUS (*mdWriteHoldRegisters)(RegisterPoolHandle handler, mdU32 addr, mdU32 len, mdU16* dat) reentrant;
};


mdExport mdSTATUS mdCreateRegisterPool(RegisterPoolHandle* regpoolhandle);
mdExport mdVOID mdDestoryRegisterPool(RegisterPoolHandle* regpoolhandle);

#define mdGetBit(reg,offset) ((reg>>offset)&1)
#define mdSetBit(handler, offset, abit) do{(handler->dat) |= (abit << offset);}while(0)

#endif

