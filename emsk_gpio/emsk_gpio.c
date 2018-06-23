/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */
/**
 * \defgroup	BOARD_EMSK_DRV_GPIO	EMSK GPIO Driver
 * \ingroup	BOARD_EMSK_DRIVER
 * \brief	EMSK Onboard GPIO Peripherals Driver
 * \details
 *		Implementation of EMSK on-board button, led, dip switch driver,
 *	this is for better use, you don't have to get a gpio object before operating
 *	led,button,switch, because some basic functions for usage are provided.
 */

/**
 * \file
 * \ingroup	BOARD_EMSK_DRV_GPIO
 * \brief	all on emsk board gpio device init and operate functions
 * \details	this gpio devices are button, led, dip switch
 */

/**
 * \addtogroup	BOARD_EMSK_DRV_GPIO
 * @{
 */

#include "embARC.h"
#include "embARC_debug.h"
#include <stdio.h>


static DEV_GPIO *led_port;
static DEV_GPIO *button;
static DEV_GPIO *switch_port;

#define EMSK_GPIO_CHECK_EXP_NORTN(EXPR)		CHECK_EXP_NOERCD(EXPR, error_exit)


/** emsk on-board led init, led default off */
void emsk_ledtest_init(void)
{
	led_port = gpio_get_dev(DEV_GPIO_PORT_A);

	//EMSK_GPIO_CHECK_EXP_NORTN(led_port != NULL);

	if (led_port->gpio_open(0xf << 28) == E_OPNED) {
		led_port->gpio_control(GPIO_CMD_SET_BIT_DIR_OUTPUT, (void *)(0xf << 28));
		led_port->gpio_control(GPIO_CMD_DIS_BIT_INT, (void *)(0xf << 28));
		printf("open port A\n");
	}

	
error_exit:
	return;
}


void emsk_button(void)
{
	button = gpio_get_dev(DEV_GPIO_PORT_A);

	EMSK_GPIO_CHECK_EXP_NORTN(button != NULL);

	if (button->gpio_open(0x0 << 16) == E_OPNED) {
		button->gpio_control(GPIO_CMD_SET_BIT_DIR_INPUT, (void *)(0xf << 16));
		button->gpio_control(GPIO_CMD_DIS_BIT_INT,(void *)(0xf << 16));
		printf("open port C\n");
	}

error_exit:
	return;
}


uint32_t button_readtest(uint32_t mask)
{
	EMSK_GPIO_CHECK_EXP_NORTN(button != NULL);
	uint32_t led;

	mask = (mask << 16) & (0xf << 16);
	button->gpio_read(&led, mask);

	printf("led value = 0x%x\n", (led>>16));
	return (led >> 16);

error_exit:
	return -1;
}



/** emsk on-board button init */

/** write 1 to light on led bit, else light off led */
void led_writetest(uint32_t led_val, uint32_t mask)
{
	EMSK_GPIO_CHECK_EXP_NORTN(led_port != NULL);

	led_val = (~led_val) & mask;
	led_val = led_val << 28;
	mask = (mask << 28) & (0xf << 28);

	led_val = (~led_val);
	led_port->gpio_write(led_val, mask);

	error_exit:
	return;
}




int main(void)
{
	emsk_ledtest_init();
	emsk_button();
	uint32_t led_read;
	while (1) {
		//led_writetest(0xF, 0xF);
		//board_delay_ms(500, 1);
		led_read = button_readtest(0xF);
		switch (led_read) {
			case 0 : 
				led_writetest(0xb, 0xf); //red
 				break;
			case 1 : 
				led_writetest(0xd, 0xf); //green
				break;
			case 2 : 
				led_writetest(0xe, 0xf); //blue
				break;
			case 3 : 
				led_writetest(0x9, 0xf); //yellow
				break;
			case 4 : 
				led_writetest(0xc, 0xf); //cock blue
				break;
			case 5 : 
				led_writetest(0xa, 0xf); //purple
				break;
			case 6 : 
				led_writetest(0x8, 0xf); //white
				break;
			case 7 : 
				led_writetest(0xf, 0xf); //dark
				break;							
			default :
				break;


		}

		
		printf("led_read = %x\n", led_read);
		board_delay_ms(500, 1);
		/*
		if (led_readtest(0xf) == 0x1)
			led_writetest(0x0, 0xF);
		else if (led_readtest(0xf) == 0x0)
			led_writetest(0xF, 0xF);
		//board_delay_ms(500, 1);
		//printf("round\n");*/
		/*
		led_writetest(0x0, 0xf);
		led_read = led_readvalue(0xf);
		printf("led_read = %x\n", led_read);
		board_delay_ms(500, 1);
		led_writetest(0xf,0xf);
		led_read = led_readvalue(0xf);
		printf("led_read = %x\n", led_read);
		board_delay_ms(500, 1);
		led_writetest(0x7, 0xf);
		led_read = led_readvalue(0xf);
		printf("led_read = %x\n", led_read);
		board_delay_ms(500, 1);
		*/
	}
	return 0;
}


/** @} end of group BOARD_EMSK_DRV_GPIO */