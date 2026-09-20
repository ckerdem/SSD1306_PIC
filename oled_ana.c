/* 
 * File:   oled_ana.c
 * Author: Celal Erdem
 *
 * PIC18F45K22 içindir.
 * Created on June 21, 2026, 3:16 PM
 */

// 'C' source line config statements

//CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator Selection bits->Internal oscillator block
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit->Oscillator Switchover mode disabled
#pragma config PLLCFG = ON      // 4X PLL Enable->Oscillator multiplied by 4
#pragma config PRICLKEN = ON    // Primary clock enable bit->Primary clock is always enabled

//CONFIG2L
#pragma config PWRTEN = OFF     // Power-up Timer Enable bit->Power up timer disabled
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits->Brown-out Reset enabled in hardware only (SBOREN is disabled)
#pragma config BORV = 190       // Brown Out Reset Voltage bits->VBOR set to 1.90 V nominal

//CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bits->Watch dog timer is always disabled. SWDTEN has no effect.
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits->1:32768

//CONFIG3H
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up->HFINTOSC output and ready status are not delayed by the oscillator stable status
#pragma config MCLRE = EXTMCLR  // MCLR Pin Enable bit->MCLR pin enabled, RE3 input pin disabled
#pragma config CCP2MX = PORTC1  // CCP2 MUX bit->CCP2 input/output is multiplexed with RC1
#pragma config PBADEN = ON      // PORTB A/D Enable bit->PORTB<5:0> pins are configured as analog input channels on Reset
#pragma config CCP3MX = PORTB5  // P3A/CCP3 Mux bit->P3A/CCP3 input/output is multiplexed with RB5
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux bit->T3CKI is on RC0
#pragma config P2BMX = PORTD2   // ECCP2 B output mux bit->P2B is on RD2

//CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config LVP = ON         // Single-Supply ICSP Enable bit->Single-Supply ICSP enabled if MCLRE is also 1
#pragma config XINST = OFF      // Extended Instruction Set Enable bit->Instruction set extension and Indexed Addressing mode disabled (Legacy mode)

//CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0->Block 0 (000800-001FFFh) not code-protected
#pragma config CP1 = OFF        // Code Protection Block 1->Block 1 (002000-003FFFh) not code-protected
#pragma config CP2 = OFF        // Code Protection Block 2->Block 2 (004000-005FFFh) not code-protected
#pragma config CP3 = OFF        // Code Protection Block 3->Block 3 (006000-007FFFh) not code-protected

//CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit->Boot block (000000-0007FFh) not code-protected
#pragma config CPD = OFF        // Data EEPROM Code Protection bit->Data EEPROM not code-protected

//CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0->Block 0 (000800-001FFFh) not write-protected
#pragma config WRT1 = OFF       // Write Protection Block 1->Block 1 (002000-003FFFh) not write-protected
#pragma config WRT2 = OFF       // Write Protection Block 2->Block 2 (004000-005FFFh) not write-protected
#pragma config WRT3 = OFF       // Write Protection Block 3->Block 3 (006000-007FFFh) not write-protected

//CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit->Configuration registers (300000-3000FFh) not write-protected
#pragma config WRTB = OFF       // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit->Data EEPROM not write-protected

//CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF      // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks
#pragma config EBTR2 = OFF      // Table Read Protection Block 2->Block 2 (004000-005FFFh) not protected from table reads executed in other blocks
#pragma config EBTR3 = OFF      // Table Read Protection Block 3->Block 3 (006000-007FFFh) not protected from table reads executed in other blocks

//CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit->OFF



#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "i2c.h"
#include "oled.h"
#include "font.h"

/*
 * 
 */
char dizi[16];

int main() {
    
    OSCCON = 0x70; // 16 MHz

    I2C_Init();
    SSD1306_Init();
    
    SSD1306_Clear();

    
    while(1){
        SSD1306_Clear();
       float volt = 4.12;
    snprintf(dizi, 16, "Volt: %.2f", volt);
    SSD1306_WriteString(dizi,5, 8, 2);
         __delay_ms(1000);
    SSD1306_WriteString("Merhaba", 2, 10, 2);
    
       SSD1306_Command(0xA5);       //  Bütün pikseller açık
       __delay_ms(5000);
       SSD1306_Command(0xA4);       //  Normal görüntü
       __delay_ms(5000);
       SSD1306_Command(0xA7);       //  Pikseller ters
       __delay_ms(5000);
       SSD1306_Command(0xA6);       //  Pikseller düz
       __delay_ms(5000);
       SSD1306_Command(0xAE);       //  Panel kapalı
       __delay_ms(5000);
       SSD1306_Command(0xAF);       //  Panel açık
       __delay_ms(5000);
       SSD1306_Command(0xA1);       // Panel yatayda simetrik gösterir
       __delay_ms(5000); 
       SSD1306_Command(0xA0);       // Panel yatayda simetriği düzeltir
       __delay_ms(5000);  
       SSD1306_Command(0xC8);       // Panel düşeyde simetrik gösterir
       __delay_ms(5000); 
       SSD1306_Command(0xC0);       // Panel düşeyde simetriği düzeltir
       __delay_ms(5000);
        
       SSD1306_Command(0x26);       //  Sağa kaydırma ayarları
       SSD1306_Command(0x0);
       SSD1306_Command(0x1);        //  Başlangıç sayfası: 1
       SSD1306_Command(0x1);        //  Bekleme: 64 kare
       SSD1306_Command(0x6);        //  Son sayfa:6
       SSD1306_Command(0x0);
       SSD1306_Command(0xFF);
       SSD1306_Command(0x2F);       //  Kaydırmayı başlat
       __delay_ms(5000);
       SSD1306_Command(0x2E);       //  Kaydırmayı durdur
       
       SSD1306_Command(0x27);       //  Sola kaydırma ayarları
       SSD1306_Command(0x0);
       SSD1306_Command(0x1);        //  Başlangıç sayfası: 1
       SSD1306_Command(0x1);        //  Bekleme: 64 kare
       SSD1306_Command(0x6);        //  Son sayfa:6
       SSD1306_Command(0x0);
       SSD1306_Command(0xFF);
       SSD1306_Command(0x2F);       //  Kaydırmayı başlat
       __delay_ms(5000);
       SSD1306_Command(0x2E);       //  Kaydırmayı durdur   
       
       SSD1306_Command(0xA3);       //  Düşey kaydırma ayarları   
       SSD1306_Command(0x00);       //  Yukarıdaki sabit satır sayısı
       SSD1306_Command(0x40);       // Kaydırmaya girecek satır sayısı
       SSD1306_Command(0x2F);       //  Kaydırmayı başlat
       SSD1306_Command(0x29);       //  
       SSD1306_Command(0x00);
       SSD1306_Command(0x00);        //  Kaydırmaya girecek ilk sayfa adresi
       SSD1306_Command(0x02);        //  Kaydırma için beklenecek frame sayısı
       SSD1306_Command(0x07);        //  Kaydırmaya girecek son sayfa adresi
       SSD1306_Command(0x02);        //  Düşey kaydırmada bir kerede kaydırılacak satır sayısı
       SSD1306_Command(0x2F);       //  Kaydırmayı başlat   
       __delay_ms(5000);    
       SSD1306_Command(0x2E);       //  Kaydırmayı durdur 
       __delay_ms(5000);  
       
    } 
    
}

