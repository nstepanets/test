/*****************************************************************************
 *
 * File Name : main.c
 *
 * Description: pin PB1, freq = 5,714309 MHz CPU_CLK_240M
 *
 * Date : 2022-05-20
 *****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "wm_type_def.h"

#include "wm_gpio_afsel.h"

//#include "wm_bt_util.h"

#include "wm_ble_server_api_demo.h"

extern int demo_bt_enable (void);

static u8 buffer_out[512];

static void
my_output_func_ptr (uint8_t *p_data, uint32_t length)
{
  memcpy (buffer_out, p_data, length);
  buffer_out[length] = 0;
  printf ("my_output_func_ptr length=%d, p_data=%s\n", length, buffer_out);
  //int i_len_ret = sprintf ((char *)buffer_out, "ok, light=%d\r\n", length);
}

void
UserMain (void)
{

  printf ("user task\n");

  demo_bt_enable ();
  printf ("demo_bt_enable... delay 5 sec\n");
  tls_os_time_delay (HZ * 5);

  int i_Res = tls_ble_server_demo_api_init (&my_output_func_ptr);
  printf ("tls_ble_server_demo_api_init=%d\n", i_Res);


  return;
}