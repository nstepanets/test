/*
  UTFT.cpp - Мульти-платформенная библиотека поддерживабщая цветные TFT
LCD-панели Copyright (C)2015 Авторское Право: Rinky-Dink Electronics, Henning
Karlsen. Все права защищены

  Эта библиотека является продолжением моих библиотек ITDB02_Graph,
ITDB02_Graph16 и RGB_GLCD для Arduino и chipKit. Так как количество
поддерживаемых модулей и контроллеров начало расти, я решил, что пришло время
создать одну универсальную библиотеку.

  Основные функции этой библиотеки были созданы на основе демо-кода,
  предоставленного ITead Studio (для модулей ITDB02) и NKC Electronics (для RGB
GLCD модулей/шилдов).

  Эта библиотека поддерживает 8 битные, 16 битные и последовательные интерфейсы
графических дисплеев, и будет работать с платами Ардуино, chipKit и select TI
LaunchPads. Полный список протестированных модулей и контроллеров укзан в файле
UTFT_Supported_display_modules_&_controllers.pdf.

  При использовании 8 битных и 16 битных модулей, существуют некоторые
требования, которые вы должны соблюдать. Эти требования можно найти в
UTFT_Requirements.pdf. При использовании модулей с последовательным
интерфейсом, нет никаких специальных требований.

  Вы можете найти свежую версию библиотеки перейдя по ссылке:
http://www.RinkyDinkElectronics.com/

  Эта библиотека является свободным программным обеспечением;
  Вы можете распространять и/или изменять её в соответствии с пунктом 3.0
лицензии CC BY-NC-SA.

  Коммерческое использование этой библиотеки предусматривает приобретение
лицензии. Включая использование библиотеки, модифицированной или нет, как
инструмент для продажи продуктов.

  Лицензия распространяется на все библиотеки, в том числе примеры и
инструменты, поставляемые с библиотекой.



исходники библиотеки, взяты отсюда:
https://wiki.iarduino.ru/page/rabota-s-cvetnym-graficheskim-displeem/

добавлен ILI9225B из:
https://github.com/gnulabis/UTFT-ESP.git

добавлены русские буквы из:
https://github.com/twsdwf/UTFT-rus.git

главный источник:
## License and Credits
This project is based on the original [UTFT
library](http://www.rinkydinkelectronics.com/library.php?id=51) developed and
maintained by Henning Karlsen, and licensed under [CC
BY-NC-SA 3.0](http://creativecommons.org/licenses/by-nc-sa/3.0/).



для UTFT_loadBitmap - нужно подготовить файлы, способы:
1)с помощью конверторов идущих с библиотекой UTFT
   http://www.rinkydinkelectronics.com/library.php?id=51
 в raw формат

2) для Linux, это можно сделать с помощью утилиты convert, входящую в состав
ImageMagick. [Руководство пользователя ImageMagick
v. 7.1.0](https://coollib.net/b/558566-ivan-georgievich-titarenko-rukovodstvo-polzovatelya-imagemagick-v-710)
 или
 https://www.altlinux.org/ImageMagick_-_%D0%BE%D0%B1%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%BA%D0%B0_%D0%B8%D0%B7%D0%BE%D0%B1%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D0%B9

например, конвертировать все изображения png (или jpg ниже), текущей
директории, в bmp формат размера 480 на 320 без сохранения соотношения сторон
для формата цвета пикселя RGB565 (такой нужен для TFT большенства дисплеев)

# convert *.png -resize 480x320! -define bmp:subtype=RGB565 p%03d.bmp
# convert *.jpg -resize 480x320! -define bmp:subtype=RGB565 j%03d.bmp
# convert *.JPG -resize 480x320! -rotate 180 -define bmp:subtype=RGB565
j%03d.bmp

или если дисплей 24 бит на пиксель RGB888, то просто resize
convert *.jpg -resize 480x320! j%03d-480x320.jpg

*/

#ifndef UTFT_h
#define UTFT_h

#ifdef __cplusplus
extern "C"
{
#endif

#define UTFT_VERSION 281

#define NO_GPIO_PIN 255

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define PORTRAIT 0
#define LANDSCAPE 1

#define HX8347A 0
#define ILI9327 1
#define SSD1289 2
#define ILI9325C 3
#define ILI9325D_8 4
#define ILI9325D_16 5
#define HX8340B_8 6
#define HX8340B_S 7
#define HX8352A 8
#define ST7735 9
#define PCF8833 10
#define S1D19122 11
#define SSD1963_480 12
#define SSD1963_800 13
#define S6D1121_8 14
#define S6D1121_16 15
#define SSD1289LATCHED 16
//#define NOT_IN_USE	17
//#define NOT_IN_USE	18
#define SSD1289_8 19
#define SSD1963_800ALT 20
#define ILI9481 21
#define ILI9325D_16ALT 22
#define S6D0164 23
#define ST7735S 24
#define ILI9341_S5P 25
#define ILI9341_S4P 26
#define R61581 27
#define ILI9486 28
#define CPLD 29
#define HX8353C 30
#define ST7735_ALT 31
#define ILI9341_UNO 32
#define ILI9341_MEGA 33
#define ILI9327_UNO 34
#define HX8357C 35
#define ILI9225B 36
#define TFT00_96SP 37
#define TFT01_3SP 38
#define TFT01_47V89 39
#define TFT01_14V89 40
#define TFT01_69V89 41
#define TFT_320QDT_9341 42
#define TFT2_4SP_9341 43
#define TFT02_0V89 44
#define TFT_397T_NT35510 45
#define TFT3_2SP_9341 46
#define TFT3_5SP_9488 47
#define MHS3528 48
#define MSP2834 49
#define MSP3223 50
#define TFT00_96SP_2 51
#define MSP3525 52
#define MSP3526 52
#define TFT01_9V89 53

#define ITDB32 0 // HX8347-A (16bit)
#define ITDB32WC 1 // ILI9327  (16bit)
#define TFT01_32W 1 // ILI9327	(16bit)
#define ITDB32S 2 // SSD1289  (16bit)
#define TFT01_32 2 // SSD1289  (16bit)
#define CTE32 2 // SSD1289  (16bit)
#define ITDB24 3 // ILI9325C (8bit)
#define ITDB24D 4 // ILI9325D (8bit)
#define ITDB24DWOT 4 // ILI9325D (8bit)
#define ITDB28 4 // ILI9325D (8bit)
#define TFT01_24_8 4 // ILI9325D (8bit)
#define DMTFT24104 4 // ILI9325D (8bit)
#define DMTFT28103 4 // ILI9325D (8bit)
#define TFT01_24_16 5 // ILI9325D (16bit)
#define ITDB22 6 // HX8340-B (8bit)
#define ITDB22SP 7 // HX8340-B (Serial 4Pin)
#define ITDB32WD 8 // HX8352-A (16bit)
#define TFT01_32WD 8 // HX8352-A	(16bit)
#define CTE32W 8 // HX8352-A	(16bit)
#define ITDB18SP 9 // ST7735   (Serial 5Pin)
#define LPH9135 10 // PCF8833	(Serial 5Pin)
#define ITDB25H 11 // S1D19122	(16bit)
#define ITDB43 12 // SSD1963	(16bit) 480x272
#define TFT01_43 12 // SSD1963	(16bit) 480x272
#define ITDB50 13 // SSD1963	(16bit) 800x480
#define TFT01_50 13 // SSD1963	(16bit) 800x480
#define CTE50 13 // SSD1963	(16bit) 800x480
#define EHOUSE50 13 // SSD1963	(16bit) 800x480
#define ITDB24E_8 14 // S6D1121	(8bit)
#define TFT01_24R2 14 // S6D1121	(8bit)
#define ITDB24E_16 15 // S6D1121	(16bit)
#define INFINIT32                                                             \
  16 // SSD1289	(Latched 16bit) -- Legacy, will be removed later
#define ELEE32_REVA 16 // SSD1289	(Latched 16bit)
//#define NOT_IN_USE	17
//#define NOT_IN_USE	18
#define ELEE32_REVB 19 // SSD1289	(8bit)
#define TFT01_70 20 // SSD1963	(16bit) 800x480 Alternative Init
#define CTE70 20 // SSD1963	(16bit) 800x480 Alternative Init
#define EHOUSE70 20 // SSD1963	(16bit) 800x480 Alternative Init
#define CTE32HR 21 // ILI9481	(16bit)
#define TFT32MEGA 21 // ILI9481	(16bit)
#define CTE28 22 // ILI9325D (16bit) Alternative Init
#define TFT01_28 22 // ILI9325D (16bit) Alternative Init
#define CTE22 23 // S6D0164	(8bit)
#define TFT01_22 23 // S6D0164	(8bit)
#define DMTFT22102 23 // S6D0164  (8bit)
#define TFT01_18SP 24 // ST7735S  (Serial 5Pin)
#define TFT01_22SP 25 // ILI9341	(Serial 5Pin)
#define TFT01_24SP 25 // ILI9341	(Serial 5Pin)
#define TFT22SHLD 25 // ILI9341	(Serial 5Pin)
#define DMTFT28105 25 // ILI9341  (Serial 5Pin)
#define MI0283QT9 26 // ILI9341	(Serial 4Pin)
#define CTE35IPS 27 // R61581	(16bit)
#define CTE40 28 // ILI9486	(16bit)
#define EHOUSE50CPLD 29 // CPLD		(16bit)
#define CTE50CPLD 29 // CPLD		(16bit)
#define CTE70CPLD 29 // CPLD		(16bit)
#define DMTFT18101 30 // HX8353C  (Serial 5Pin)
#define TFT18SHLD 31 // ST7735	(Serial 5Pin) Alternative Init
#define TFT28UNO 32 // ILI9341	(8bit)
#define TFT28MEGA 33 // ILI9341	(8bit)
#define TFT395UNO 34 // ILI9327	(8bit)
#define TFT32MEGA_2 35 // HX8357C	(16bit)

#define SERIAL_4PIN 4
#define SERIAL_5PIN 5
#define LATCHED_16 17
#define NOTINUSE 255

//*********************************
// COLORS
//*********************************
// VGA color palette
#define VGA_BLACK 0x0000
#define VGA_WHITE 0xFFFF
#define VGA_RED 0xF800
#define VGA_GREEN 0x0400
#define VGA_BLUE 0x001F
#define VGA_SILVER 0xC618
#define VGA_GRAY 0x8410
#define VGA_MAROON 0x8000
#define VGA_YELLOW 0xFFE0
#define VGA_OLIVE 0x8400
#define VGA_LIME 0x07E0
#define VGA_AQUA 0x07FF
#define VGA_TEAL 0x0410
#define VGA_NAVY 0x0010
#define VGA_FUCHSIA 0xF81F
#define VGA_PURPLE 0x8010
#define VGA_TRANSPARENT 0xFFFFFFFF

#include "wm_hostspi.h"
#include "wm_type_def.h"

#include <stdio.h>
#include <stdlib.h>

#define LOG(...) printf (__VA_ARGS__)

  typedef u8 byte;
  typedef u16 word;

#define bitmapdatatype unsigned short *

  typedef struct
  {
    uint8_t *font;
    uint8_t x_size;
    uint8_t y_size;
    uint8_t offset;
    uint8_t numchars;
  } _current_font_t;

  typedef _current_font_t _current_font;

  typedef bool boolean;
  /*
  void UTFT_UTFT (byte model, byte RS, byte WR, byte CS, byte RST, byte SER,
  u32 spi_freq, u8 spi_mode);

  для паралельной шины, указываются RS, WR, CS, RST
   Выводы параллельной шины данных не указываются
    если, параллельная 16 бит шина = PB0 ... PB15 !
    если было бы 8 бит шина = PB0 ... PB7 !


  для шины SPI 
   RS это SDA  данные
   WR это SCL  синхросигнал
   CS это  CS  выбор чипа
   RST это RES сброс (reset)
   SER это DC  комманда/данные
   spi_freq    частота SPI(Герц)

   для 5 контактных SPI дисплеев
   (где отдельно ножка комманда/данные)
   програмируеться HW SPI на ножки (предопред)
         wm_spi_cs_config (WM_IO_PB_14); - не исп, но занята
    WR = wm_spi_ck_config (WM_IO_PB_15);
         wm_spi_di_config (WM_IO_PB_16); - не исп, но занята
    RS = wm_spi_do_config (WM_IO_PB_17);
   но, можно отказаться от HW SPI в пользу Soft SPI
    установив spi_freq=0 -  эмуляция SPI
    это удобно для разных ножек

    максимально, частота spi_freq = 20000000 (20MHz)
        но!      если spi_freq > 20000000 тогда работает spi SDIO
        частоту можно ставить от 21000000 до 120000000 герц (работает при 240Mhz тактовой)
    контакты:
       WM_IO_PB_06 CK   -> SCL
       WM_IO_PB_07 CMD  -> MOSI

  */
  void UTFT_UTFT (byte model, byte RS, byte WR, byte CS, byte RST, byte SER,
                  u32 spi_freq);

  void UTFT_InitLCD (byte orientation);
  // InitLCD(byte orientation=LANDSCAPE);
  void UTFT_clrScr ();
  void UTFT_drawPixel (int x, int y);
  void UTFT_drawLine (int x1, int y1, int x2, int y2);
  void UTFT_fillScr (byte r, byte g, byte b);
  void UTFT_fillScr2 (word color);
  void UTFT_drawRect (int x1, int y1, int x2, int y2);
  void UTFT_drawRoundRect (int x1, int y1, int x2, int y2);
  void UTFT_fillRect (int x1, int y1, int x2, int y2);
  void UTFT_fillRoundRect (int x1, int y1, int x2, int y2);
  void UTFT_drawCircle (int x, int y, int radius);
  void UTFT_fillCircle (int x, int y, int radius);
  void UTFT_setColor (byte r, byte g, byte b);
  void UTFT_setColor2 (word color);
  word UTFT_getColor ();
  void UTFT_setBackColor (byte r, byte g, byte b);
  void UTFT_setBackColor2 (uint32_t color);
  word UTFT_getBackColor ();
  void UTFT_print (char *st, int x, int y, int deg);
  // print(char *st, int x, int y, int deg=0);
  // void	UTFT_print2(String st, int x, int y, int deg);
  void UTFT_printNumI (long num, int x, int y, int length, char filler);
  // printNumI(long num, int x, int y, int length=0, char filler=' ');
  void UTFT_printNumF (double num, byte dec, int x, int y, char divider,
                       int length, char filler);
  // printNumF(double num, byte dec, int x, int y, char divider='.', int
  // length=0, char filler=' ');
  void UTFT_setFont (uint8_t *font);
  uint8_t *UTFT_getFont ();
  uint8_t UTFT_getFontXsize ();
  uint8_t UTFT_getFontYsize ();
  void UTFT_drawBitmap (int x, int y, int sx, int sy, bitmapdatatype data,
                        int scale);
  // drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int
  // scale=1);
  void UTFT_drawBitmap24bpp (int x, int y, int sx, int sy, u32 *data);

  void UTFT_drawBitmap2 (int x, int y, int sx, int sy, bitmapdatatype data,
                         int deg, int rox, int roy);
  // void UTFT_drawBitmapLEBF (int x, int y, int sx, int sy, bitmapdatatype
  // data);

  void UTFT_lcdOff ();
  void UTFT_lcdOn ();
  void UTFT_setContrast (char c);
  int UTFT_getDisplayXSize ();
  int UTFT_getDisplayYSize ();
  void UTFT_setBrightness (byte br);
  void UTFT_setDisplayPage (byte page);
  void UTFT_setWritePage (byte page);
  word UTFT_loadBitmap (int x, int y, int sx, int sy, char *filename);

  /* включить, выключить, сохранение распаковки jpg в память psram */
  u8 * UTFT_store_to_psram(bool b_Set_store_to_psram);
  /* из памяти psram на дисплей */
  void UTFT_psram_to_drawBitmap(void);

#ifdef __cplusplus
}
#endif

#endif
