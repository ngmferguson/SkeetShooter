#include <f3d_systick.h>
#include <f3d_led.h> 
#include <f3d_user_btn.h>
#include <f3d_uart.h>

volatile int systick_flag = 0;
extern int state = 0;

void f3d_systick_init(void) {
   SysTick_Config(SystemCoreClock/100); //100 interrupts per second
}

void SysTick_Handler(void) {
  if (user_btn_read())
    SysTick_Config(SystemCoreClock/10);
  else
    SysTick_Config(SystemCoreClock/100);
}

/* f3d_systick.c ends here */
