/*****************************************************************************
 *
 * File Name : main.c
 *
 * Description: main
 *
 * Date : 2022-12-21
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wm_type_def.h"

#include "wm_cpu.h"
#include "wm_rtc.h"
#include "wm_timer.h"

#include "wm_gpio.h"
#include "wm_gpio_afsel.h"
#include "wm_osal.h"

#include "mod1/UTFT.h"
#include "mod1/u_jpeg.h"

extern uint8_t SmallFont[]; // подключаем маленький шрифт
extern uint8_t BigFont[];   // подключаем большой шрифт
extern uint8_t
    SevenSegNumFont[]; // подключаем шрифт имитирующий семисегментный индикатор
extern uint8_t SmallSymbolFont[];

#include "encoder.h"

#define USER_APP1_TASK_SIZE 2048
static OS_STK UserApp1TaskStk[USER_APP1_TASK_SIZE];
#define USER_APP1_TASK_PRIO 32


void
user_app1_task (void *sdata)
{
  printf ("user_app1_task start\n");

  libENCODER_t enc_pin = {
    .ENCODER_S = WM_IO_PA_11,
    .ENCODER_A = WM_IO_PA_12,
    .ENCODER_B = WM_IO_PA_13,
    .ADD_BUTTON_1 = WM_IO_PA_14,
    .ADD_BUTTON_2 = NO_GPIO_PIN,
    .ADD_BUTTON_3 = NO_GPIO_PIN,
  };
  bsp_encoder_init (&enc_pin);
/*
  printf ("user_app1_task start TFT01_18SP 128x160\n");
  UTFT_UTFT (TFT01_18SP,
             (u8)NO_GPIO_PIN // WM_IO_PB_17  //RS  SDA
             ,
             (u8)NO_GPIO_PIN // WM_IO_PB_15  //WR  SCL
             ,
             WM_IO_PB_23 //(u8)NO_GPIO_PIN // WM_IO_PB_14  //CS  CS
             ,
             (u8)WM_IO_PB_21 // RST reset RES
             ,
             (u8)WM_IO_PB_22 // SER => DC !
             ,
             // 120000000
             60000000
  );         */

  printf ("user_app1_task start 3.5 TFT 320x480 HW SDIO SPI MSP3526 \n");

  // подключаем библиотеку UTFT
  UTFT_UTFT (MSP3526 //
             ,
             (u8)NO_GPIO_PIN // WM_IO_PB_17  //RS  SDA
             ,
             (u8)NO_GPIO_PIN // WM_IO_PB_15  //WR  SCL
             ,
             WM_IO_PB_23 //(u8)NO_GPIO_PIN // WM_IO_PB_14  //CS  CS
             ,
             (u8)WM_IO_PB_21 // RST reset RES
             ,
             (u8)WM_IO_PB_22 // SER => DC !
             ,
             //120000000
                60000000
             /* spi_freq(Герц) для 5 контактных SPI дисплеев
                (где отдельно ножка комманда/данные)
             програмируеться HW SPI на ножки (предопред)
                 wm_spi_cs_config (WM_IO_PB_14);
                 wm_spi_ck_config (WM_IO_PB_15);
                 wm_spi_di_config (WM_IO_PB_16);
                 wm_spi_do_config (WM_IO_PB_17);
             но, можно отказаться от HW SPI в пользу Soft SPI
             установив spi_freq=0
             эмуляции SPI, это удобно для разных ножек

    максимально, частота spi_freq = 20000000 (20MHz)
        но!      если spi_freq > 20000000 тогда работает spi SDIO
        частоту можно ставить от 21000000 до 120000000 герц (работает при
    240Mhz тактовой) контакты: WM_IO_PB_06 CK   -> SCL 
                               WM_IO_PB_07 CMD  -> MOSI
           */
  );
  /*
  ---- ------
  W801 LCD
  ---- ------
  3.3v bl    подсветка
  3.3v vcc
  gnd  gnd
  PB21 res   RESET сброс
  PB23 cs    CS выбор чипа
  PB22 dc    комманда/данные
  PB07 sda   данные
  PB06 sck   синхросигнал
  ---- ------
  W801 LCD
  ---- ------


  */

  UTFT_InitLCD (LANDSCAPE); // инициируем дисплей
  // UTFT_InitLCD (PORTRAIT);

  UTFT_clrScr (); // стираем всю информацию с дисплея
  //UTFT_setFont (SmallFont); // устанавливаем шрифт
  UTFT_setFont (BigFont); // устанавливаем шрифт
  char msg[100];
  msg[0] = 0;

  int i_enc_diff = get_encoder_diff () + 1;
  bool btn_state = !get_encoder_btn_state ();
  bool add_btn_1 = !get_add_btn_1_state ();
  while (1)
    { //

      int i_enc_curr = get_encoder_diff ();
      if (i_enc_curr != i_enc_diff)
        {
          i_enc_diff = i_enc_curr;
          if (i_enc_diff > 0)
            UTFT_setColor2 (VGA_GREEN);
          else if (i_enc_diff == 0)
            UTFT_setColor2 (VGA_WHITE);
          else
            UTFT_setColor2 (VGA_BLUE);
          sprintf (msg, " i_enc_diff=%d ", i_enc_diff);
          UTFT_print (msg, CENTER, 50, 0);
        }

      bool btn_state_curr = get_encoder_btn_state ();
      if (btn_state != btn_state_curr) //Нажали
        {
          btn_state = btn_state_curr;
          if (btn_state)
            {
              UTFT_setColor2 (VGA_WHITE);
              sprintf (msg, " button encoder RELEASE ");
            }
          else
            {
              UTFT_setColor2 (VGA_RED);
              sprintf (msg, "  button encoder PUSH   ");
              set_encoder_diff (0);
            }
          UTFT_print (msg, CENTER, 80, 0);
        }


      bool add_btn_1_curr = get_add_btn_1_state ();
      if (add_btn_1 != add_btn_1_curr) //Нажали
        {
          add_btn_1 = add_btn_1_curr;
          if (add_btn_1)
            {
              UTFT_setColor2 (VGA_WHITE);
              sprintf (msg, " button 1 RELEASE ");
            }
          else
            {
              UTFT_setColor2 (VGA_RED);
              sprintf (msg, "  button 1 PUSH   ");
              set_encoder_diff (0);
            }
          UTFT_print (msg, CENTER, 120, 0);
        }

      tls_os_time_delay (HZ / 50);

    } //
}

void
UserMain (void)
{
  printf ("UserMain start");
  tls_sys_clk_set (CPU_CLK_240M);

  tls_os_task_create (NULL, NULL, user_app1_task, NULL,
                      (void *)UserApp1TaskStk, /* task's stack start address */
                      USER_APP1_TASK_SIZE
                          * sizeof (u32), /* task's stack size, unit:byte */
                      USER_APP1_TASK_PRIO, 0);
}
