case TFT01_3SP+100:
   LOG("TFT01_3SP init\n"); 

// 7735R init, part 1 (red or green tab)
// 15 commands in list:
#define ST77XX_SWRESET 0x01
    UTFT_LCD_Write_COM(ST77XX_SWRESET);
 //  1: Software reset, 0 args, w/delay
 //     150 ms delay
    delay(150);

#define ST77XX_SLPOUT 0x11
    UTFT_LCD_Write_COM(ST77XX_SLPOUT);
 //  2: Out of sleep mode, 0 args, w/delay
//     500 ms delay
    delay(500);


    /* Memory Data Access Control */
    UTFT_LCD_Write_COM(0x36);
//    if(conf->direction==0)
UTFT_LCD_Write_DATA2(0x00);
//    else if(conf->direction==1)
//UTFT_LCD_Write_DATA2(0xC0);
//    else if(conf->direction==2)
//UTFT_LCD_Write_DATA2(0x70);
//    else if(conf->direction==3)
//UTFT_LCD_Write_DATA2(0xA0);
    /* RGB 5-6-5-bit  */
    UTFT_LCD_Write_COM(0x3A);
    UTFT_LCD_Write_DATA2(0x05);
    /* Porch Setting */
    UTFT_LCD_Write_COM(0xB2);
    UTFT_LCD_Write_DATA2(0x0C);
    UTFT_LCD_Write_DATA2(0x0C);
    UTFT_LCD_Write_DATA2(0x00);
    UTFT_LCD_Write_DATA2(0x33);
    UTFT_LCD_Write_DATA2(0x33);
    /*  Gate Control */
    UTFT_LCD_Write_COM(0xB7);
    UTFT_LCD_Write_DATA2(0x35);
    /* VCOM Setting */
    UTFT_LCD_Write_COM(0xBB);
    UTFT_LCD_Write_DATA2(0x32);
    /* LCM Control */
    // UTFT_LCD_Write_COM(0xC0);
    // UTFT_LCD_Write_DATA2(0x2C);
    /* VDV and VRH Command Enable */
    UTFT_LCD_Write_COM(0xC2);
    UTFT_LCD_Write_DATA2(0x01);
    /* VRH Set */
    UTFT_LCD_Write_COM(0xC3);
    UTFT_LCD_Write_DATA2(0x15);
    /* VDV Set */
    UTFT_LCD_Write_COM(0xC4);
    UTFT_LCD_Write_DATA2(0x20);
    /* Frame Rate Control in Normal Mode */
    UTFT_LCD_Write_COM(0xC6);
    UTFT_LCD_Write_DATA2(0x0F);
    /* Power Control 1 */
    UTFT_LCD_Write_COM(0xD0);
    UTFT_LCD_Write_DATA2(0xA4);
    UTFT_LCD_Write_DATA2(0xA1);
    /* Positive Voltage Gamma Control */
    UTFT_LCD_Write_COM(0xE0);
    UTFT_LCD_Write_DATA2(0xD0);
    UTFT_LCD_Write_DATA2(0x08);
    UTFT_LCD_Write_DATA2(0x0E);
    UTFT_LCD_Write_DATA2(0x09);
    UTFT_LCD_Write_DATA2(0x09);
    UTFT_LCD_Write_DATA2(0x05);
    UTFT_LCD_Write_DATA2(0x31);
    UTFT_LCD_Write_DATA2(0x33);
    UTFT_LCD_Write_DATA2(0x48);
    UTFT_LCD_Write_DATA2(0x17);
    UTFT_LCD_Write_DATA2(0x14);
    UTFT_LCD_Write_DATA2(0x15);
    UTFT_LCD_Write_DATA2(0x31);
    UTFT_LCD_Write_DATA2(0x34);
    /* Negative Voltage Gamma Control */
    UTFT_LCD_Write_COM(0xE1);
    UTFT_LCD_Write_DATA2(0xD0);
    UTFT_LCD_Write_DATA2(0x08);
    UTFT_LCD_Write_DATA2(0x0E);
    UTFT_LCD_Write_DATA2(0x09);
    UTFT_LCD_Write_DATA2(0x09);
    UTFT_LCD_Write_DATA2(0x15);
    UTFT_LCD_Write_DATA2(0x31);
    UTFT_LCD_Write_DATA2(0x33);
    UTFT_LCD_Write_DATA2(0x48);
    UTFT_LCD_Write_DATA2(0x17);
    UTFT_LCD_Write_DATA2(0x14);
    UTFT_LCD_Write_DATA2(0x15);
    UTFT_LCD_Write_DATA2(0x31);
    UTFT_LCD_Write_DATA2(0x34);
    /* Display Inversion On */
    UTFT_LCD_Write_COM(0x21);
    /* Sleep Out */
    UTFT_LCD_Write_COM(0x11);
    /* wait for power stability */
    delay(100);


#define ST77XX_NORON 0x13
UTFT_LCD_Write_COM(ST77XX_NORON);//  3: Normal display on, no args, w/delay
    delay(10);                           //     10 ms delay

#define ST77XX_DISPON 0x29
UTFT_LCD_Write_COM(ST77XX_DISPON);//  4: Main screen turn on, no args w/delay

    delay(100);                        //     100 ms delay



	break;



case TFT01_3SP:
   LOG("TFT01_3SP init 9 commands in list\n"); 
         // Init commands for 7789 screens
         //  9 commands in list:
#define ST77XX_SWRESET 0x01
    UTFT_LCD_Write_COM(ST77XX_SWRESET);
 //  1: Software reset, 0 args, w/delay
 //     150 ms delay
    delay(150);

#define ST77XX_SLPOUT 0x11
    UTFT_LCD_Write_COM(ST77XX_SLPOUT);
 //  2: Out of sleep mode, 0 args, w/delay
//     10 ms delay
    delay(500);

    UTFT_LCD_Write_COM(ST77XX_COLMOD);//  3: Set color mode, 1 arg + delay:
    UTFT_LCD_Write_DATA2(0x55);      //     16-bit color
    delay(10);                      //     10 ms delay

    UTFT_LCD_Write_COM(ST77XX_MADCTL);              //  4: Mem access ctrl (directions), 1 arg:
    UTFT_LCD_Write_DATA2(0x00);                       //     Row/col addr, bottom-top refresh

#define ST77XX_CASET 0x2A
    UTFT_LCD_Write_COM(ST77XX_CASET);   //  5: Column addr set, 4 args, no delay:
    UTFT_LCD_Write_DATA2(0x00);
    UTFT_LCD_Write_DATA2(0);        //     XSTART = 0
    UTFT_LCD_Write_DATA2(0);
   UTFT_LCD_Write_DATA2(240);  //     XEND = 240

#define ST77XX_RASET 0x2B
    UTFT_LCD_Write_COM(ST77XX_RASET);           //  6: Row addr set, 4 args, no delay:
   UTFT_LCD_Write_DATA2(0x00);
   UTFT_LCD_Write_DATA2(0);             //     YSTART = 0
   UTFT_LCD_Write_DATA2(240>>8);
   UTFT_LCD_Write_DATA2(240&0xFF);  //     YEND = 240

    UTFT_LCD_Write_COM(ST77XX_INVON);//  7: hack
    delay(10);
    UTFT_LCD_Write_COM(ST77XX_NORON);//  8: Normal display on, no args, w/delay
    delay(10);//     10 ms delay
    UTFT_LCD_Write_COM(ST77XX_DISPON);//  9: Main screen turn on, no args, delay
    delay(500); //    10 ms delay

    UTFT_LCD_Write_COM(ST77XX_MADCTL);
#define ST7789_MADCTL_RGB 0x00
    UTFT_LCD_Write_DATA2(ST7789_MADCTL_RGB);


	break;