/***************************************************************************** 
* 
* File Name : main.c
* 
* Description: main 
* 
* Date : 2022-06-05
*****************************************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "wm_type_def.h"
//#include "wm_uart.h"
#include "wm_gpio.h"
//#include "wm_hostspi.h"
//#include "wm_socket.h"
//#include "wm_sockets.h"
//#include "wm_wifi.h"
//#include "wm_hspi.h"
//#include "wm_pwm.h"
//#include "wm_params.h"
#include "wm_osal.h"
//#include "wm_netif.h"
//#include "wm_efuse.h"
//#include "wm_mem.h"
#include "wm_regs.h"
#include "wm_rtc.h"
#include "wm_timer.h"
#include "wm_watchdog.h"
#include "wm_cpu.h"
//#include "csi_core.h"



//#include "driver_st7920_interface.h"
#include "driver_st7920_display_test.h"


void UserMain(void)
{
    printf("user task\n");

    //tls_sys_clk_set(CPU_CLK_240M); 

    for(;;)
     {
     tls_os_time_delay(HZ*5);
     st7920_display_test();
     }

}
