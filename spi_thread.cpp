/*!
 ********************************************************************
 * \file	spi_thread.cpp
 * \author	NothernWind
 * \version	0.0.3
 * \date	05.07.2015
 * \brief
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
 * \brief
 *
 ********************************************************************
 */
void SPI_Thread::run()
{
	int spi_wait_timeout;
	while (thread_state == true) {

		spi_wait_timeout = 0;

		// Ожидание готовности устройства
		while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
			spi_wait_timeout++;
			if (spi_wait_timeout >= 1000000) {
				spi_wait_timeout = 0;
				printf("SPI Device Timeout error\n");
				printf("Tryin to reset\n");
				reset_spi_device();
				continue;
			}
		}

		// Передача данных
		spi0_unidir_poll_block_transfer(
			(const char *)(&out_data[0]), (char *)(&spi_adc_data[0]), 4);
		// Сигналим о готовности данных
		emit SPI_Tread_DataRDY((qreal)spi_adc_data[0], (qreal)spi_adc_data[1]);
	}

	printf("SPI Device Stopped\n");
	emit spi_thread_stopped();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Thread::SPI_Thread_Init()
{
	int i = 1000000;

	if (gpio_init() == -1) return -1;

	if (spi0_unidir_poll_init(250,
		SPI0_CHPA_BEGINN | SPI0_CPOL_HIGH) == -1) return -2;

	if (reset_spi_device() == -1) {
		return -3;
	}

	printf("Device Ready!\n");
	return 0;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void SPI_Thread::SPI_Thread_DeInit()
{
	gpio_deinit();
	spi0_unidir_poll_deinit();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Thread::reset_spi_device()
{
	int rst_timeout = 0;
	int rst_wait = 10000;

	printf("Reset the Device\n");

	bcm2835_GPIO->GPCLR0 = GPIO_GPCLR0_GP25;
	while (rst_wait--);
	bcm2835_GPIO->GPSET0 = GPIO_GPSET0_GP25;

	while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
		rst_timeout++;
		if (rst_timeout >= 1000000) {
			rst_timeout = 0;
			printf("Reset Timeout\n");
			return -1;
		}
	}

	printf("Device Ready!\n");

	return 0;
}
