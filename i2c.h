/* 
 * File:   i2c.h
 * Author: Celal
 *
 * Created on August 7, 2026, 3:13 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <xc.h>
#define _XTAL_FREQ 16000000

// LCD I2C adresi 0x27 ancak 0x27<1 | 0 -> 0x4E (Yani yazma için 0 eklenince))
#define LCD_ADDR 0x4E

static void I2C_Wait(void);
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(unsigned char data);


#endif	/* I2C_H */

