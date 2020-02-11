TEMPLATEROOT = ../../C335-labs-Fall2019

# compilation flags for gdb

CFLAGS  = -O1 -g
ASFLAGS = -g 

# object files

OBJS=  $(STARTUP) 	main.o \
			queue.o \
			f3d_user_btn.o \
			glcdfont.o \
			f3d_i2c.o \
			f3d_i2c2.o \
			f3d_nunchuk.o \
			f3d_uart.o \
			f3d_lcd_sd.o \
			f3d_accel.o \
			f3d_led.o \
			f3d_delay.o \
			f3d_systick.o \
			f3d_timer2.o \
			f3d_rtc.o \
			f3d_dac.o \
			stm32f30x_i2c.o \
			stm32f30x_rcc.o \
			stm32f30x_tim.o \
			stm32f30x_gpio.o \
			stm32f30x_usart.o \
			stm32f30x_spi.o \
			stm32f30x_dma.o \
			stm32f30x_dac.o \
			stm32f30x_rtc.o \
			stm32f30x_pwr.o \
			stm32f30x_misc.o \
			mmcbb.o \
			ff.o \
			newlib_stubs.o
# include common make file

include $(TEMPLATEROOT)/c335.mk


