#include "i2c.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>


/*=====================================================
 * I2C fonksiyonları
======================================================= */

static void I2C_Wait(void)
{
    while ((SSP1CON2 & 0x1F) || (SSP1STAT & 0x04));
}

void I2C_Init(void)
{
    TRISC3 = 1; // SCL
    TRISC4 = 1; // SDA
    ANSELC = 0x00;

    SSP1CON1 = 0x28; // I2C master
    SSP1CON2 = 0x00;
    SSP1ADD = 39;    // 100kHz @ 8MHz
    SSP1STAT = 0x00;
}

void I2C_Start(void)
{
    I2C_Wait();
    SSP1CON2bits.SEN = 1;
}

void I2C_Stop(void)
{
    I2C_Wait();
    SSP1CON2bits.PEN = 1;
}

void I2C_Write(unsigned char data)
{
    I2C_Wait();
    SSP1BUF = data;
}

