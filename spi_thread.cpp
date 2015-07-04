/*!
 ********************************************************************
 * file
 * author	kaljan
 * version	0.0.0
 * date
 * brief
 *
 ********************************************************************
 */
#include "spi_thread.h"

SPI_Thread::SPI_Thread()
	: spi_state(false)
	, thread_state(false)
{
	int error_code = SPI_Thread_Init();
	if (error_code != 0) {
		printf("SPI Thread Init Failed. Error %d\n", error_code);
		return;
	}
	spi_state = true;

	for (int i = 0; i < 4; i++) {
		out_data[i] = 0xFF;
	}
}

SPI_Thread::~SPI_Thread()
{
	SPI_Thread_DeInit();
}

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
void SPI_Thread::run()
{
	int error_code;
	int spi_wait_timeout;
	while (thread_state == true) {

		spi_wait_timeout = 0;

		while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
			spi_wait_timeout++;
			if (spi_wait_timeout >= 1000000) {
				spi_wait_timeout = 0;
				printf("SPI Device Timeout error\n");
				thread_state = false;
				return;
			}
		}

		error_code = spi0_unidir_poll_block_transfer(
			(const char *)(&out_data[0]), (char *)(&ADC_data[0]), 4);

		if (error_code != 0) {
			printf("SPI Data Transfer Error: %d\n"
				"Device not response\n", error_code);
			thread_state = false;
			return;
		}
		emit SPI_Tread_DataRDY((qreal)ADC_data[0], (qreal)ADC_data[0]);
	}

	printf("SPI Device Stopped\n");
}

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
int SPI_Thread::SPI_Thread_Init()
{
	int i = 10000;

	if (gpio_init() == -1) return -1;

	if (spi0_unidir_poll_init(250,
		SPI0_CHPA_BEGINN | SPI0_CPOL_HIGH) == -1) return -2;

	printf("Reset the Device\n");
	bcm2835_GPIO->GPCLR0 = GPIO_GPCLR0_GP25;

	while (i--);
	bcm2835_GPIO->GPSET0 = GPIO_GPSET0_GP25;

	i = 0;

	while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
		i++;
		if (i >= 1000000) {
			i = 0;
			return -3;
		}
	}
	printf("Device Ready!\n");
	return 0;
}

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
void SPI_Thread::SPI_Thread_DeInit()
{
	gpio_deinit();
	spi0_unidir_poll_deinit();
}
