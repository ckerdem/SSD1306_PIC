/*=============================================================================
 * SSD1306 fonksiyonları bu dosyada
 * ==========================================================================*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "i2c.h"
#include "oled.h"
#include "font.h"

//  SSD1306 Tanımları
#define SSD1306_ADDR    0x3C        // 7 bit adres

#define SSD1306_CMD     0x00
#define SSD1306_DATA    0x40

#define SSD1306_WIDTH   128
#define SSD1306_HEIGHT  64

//  Komut gönderme
void SSD1306_Command(uint8_t cmd)
{
    I2C_Start();

    I2C_Write((SSD1306_ADDR << 1) | 0); // Write

    I2C_Write(SSD1306_CMD);

    I2C_Write(cmd);

    I2C_Stop();
}

//  Tek Byte Veri Gönderme
void SSD1306_Data(uint8_t data)
{
    I2C_Start();

    I2C_Write((SSD1306_ADDR << 1));

    I2C_Write(SSD1306_DATA);

    I2C_Write(data);

    I2C_Stop();
}

//  Çoklu Byte Yazma
void SSD1306_DataBuffer(uint8_t *buffer, uint16_t length)
{
    uint16_t i;

    I2C_Start();

    I2C_Write((SSD1306_ADDR<<1));

    I2C_Write(SSD1306_DATA);

    for(i=0;i<length;i++)
    {
        I2C_Write(buffer[i]);
    }

    I2C_Stop();
}

//  İmleç (Sayfa ve Kolon) SSD1306'da satır yerine Page kullanılır.
void SSD1306_SetCursor(uint8_t page,uint8_t column)
{
    SSD1306_Command(0xB0 | page);

    SSD1306_Command(column & 0x0F);

    SSD1306_Command(0x10 | (column>>4));
}

//  Ekranı Temizleme
void SSD1306_Clear(void)
{
    uint8_t page;
    uint8_t i;

    for(page=0;page<8;page++)
    {
        SSD1306_SetCursor(page,0);

        I2C_Start();

        I2C_Write(SSD1306_ADDR<<1);

        I2C_Write(SSD1306_DATA);

        for(i=0;i<128;i++)
            I2C_Write(0x00);

        I2C_Stop();
    }
}

//  Ekranı Açma/Kapatma
void SSD1306_DisplayOn(void)
{
    SSD1306_Command(0xAF);
}

void SSD1306_DisplayOff(void)
{
    SSD1306_Command(0xAE);
}

//  Tüm Piksel Açık
void SSD1306_AllPixelsOn(void)
{
    SSD1306_Command(0xA5);
}

//  Normal moda dönüş:
void SSD1306_NormalDisplay(void)
{
    SSD1306_Command(0xA4);
}

//  Ters Göröntü
void SSD1306_InvertOn(void)
{
    SSD1306_Command(0xA7);
}

void SSD1306_InvertOff(void)
{
    SSD1306_Command(0xA6);
}

//  Başlangıç (Initialization) En yaygın kullanılan ayarlar:
void SSD1306_Init(void)
{
    SSD1306_Command(0xAE);

    SSD1306_Command(0x20);
    SSD1306_Command(0x00);

    SSD1306_Command(0xB0);

    SSD1306_Command(0xC8);

    SSD1306_Command(0x00);

    SSD1306_Command(0x10);

    SSD1306_Command(0x40);

    SSD1306_Command(0x81);
    SSD1306_Command(0x7F);

    SSD1306_Command(0xA1);

    SSD1306_Command(0xA6);

    SSD1306_Command(0xA8);
    SSD1306_Command(0x3F);

    SSD1306_Command(0xA4);

    SSD1306_Command(0xD3);
    SSD1306_Command(0x00);

    SSD1306_Command(0xD5);
    SSD1306_Command(0x80);

    SSD1306_Command(0xD9);
    SSD1306_Command(0xF1);

    SSD1306_Command(0xDA);
    SSD1306_Command(0x12);

    SSD1306_Command(0xDB);
    SSD1306_Command(0x40);

    SSD1306_Command(0x8D);
    SSD1306_Command(0x14);

    SSD1306_Command(0xAF);
}

void SSD1306_WriteString(const char* str, uint8_t page, uint8_t column, uint8_t size) {
    if (size == 1) {
        SSD1306_SetCursor(page, column);
        while (*str) {
            char c = *str++;
            if (c < 32 || c > 126) c = ' ';
            uint16_t idx = (c - 32);
            for (uint8_t i = 0; i < 5; i++) {
                SSD1306_Data(ASCII_5x7[idx][i]);
            }
            SSD1306_Data(0x00); // Boşluk
        }
    } 
    else if (size == 2) {
        // --- 2 SATIR BÜYÜKLÜK İÇİN MATEMATİKSEL ÖLÇEKLENDİRME ---
        
        // Bölüm A: Üst Satırı Bas (Yazının üst 8 piksellik parçası)
        SSD1306_SetCursor(page, column);
        const char* temp_str = str;
        while (*temp_str) {
            char c = *temp_str++;
            if (c < 32 || c > 126) c = ' ';
            uint16_t idx = (c - 32);
            
            for (uint8_t i = 0; i < 5; i++) {
                uint8_t orig = ASCII_5x7[idx][i];
                uint8_t upper = 0;
                
                // Alt 4 biti dikeyde 2 kat büyüterek 8 bite yayıyoruz
                if (orig & 0x01) upper |= 0x03;
                if (orig & 0x02) upper |= 0x0C;
                if (orig & 0x04) upper |= 0x30;
                if (orig & 0x08) upper |= 0xC0;
                
                SSD1306_Data(upper); // Yatay genişlik için 2 kez basılır
                SSD1306_Data(upper);
            }
            SSD1306_Data(0x00); SSD1306_Data(0x00);
        }
        
        // Bölüm B: Alt Satırı Bas (Yazının alt 8 piksellik parçası - 1 sayfa aşağıya)
        SSD1306_SetCursor(page + 1, column);
        temp_str = str; 
        while (*temp_str) {
            char c = *temp_str++;
            if (c < 32 || c > 126) c = ' ';
            uint16_t idx = (c - 32);
            
            for (uint8_t i = 0; i < 5; i++) {
                uint8_t orig = ASCII_5x7[idx][i];
                uint8_t lower = 0;
                
                // Üst 4 biti dikeyde 2 kat büyüterek 8 bite yayıyoruz
                if (orig & 0x10) lower |= 0x03;
                if (orig & 0x20) lower |= 0x0C;
                if (orig & 0x40) lower |= 0x30;
                if (orig & 0x80) lower |= 0xC0;
                
                SSD1306_Data(lower); 
                SSD1306_Data(lower);
            }
            SSD1306_Data(0x00); SSD1306_Data(0x00);
        }
    }
}

