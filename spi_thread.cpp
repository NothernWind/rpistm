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
	out_data[0] = 0x10;
}

//! Нужно обязательно всё это деинициализировать
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
int SPI_Thread::SPI_Thread_Init()
{
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

		spi_request.bits.rqn = 0x01;
		spi_request.bits.rw = 1;

		spi0_unidir_poll_block_transfer(
			(const char *)(&spi_request),
			(char *)(&spi_adc_data[0]), 2);

		// Ожидание готовности устройства
		while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
			spi_wait_timeout++;
			if (spi_wait_timeout >= 1000000) {
				spi_wait_timeout = 0;
				printf("SPI Device Timeout error\n");
				//printf("Tryin to reset\n");
				//reset_spi_device();
				//continue;
				return;
			}
		}

		// Передача данных
		spi0_unidir_poll_block_transfer(
			(const char *)(&out_data[0]), (char *)(&spi_adc_data[0]), 4);
		// Сигналим о готовности данных
		emit SPI_Tread_DataRDY((qreal)spi_adc_data[0], (qreal)spi_adc_data[1]);
	}

	printf("SPI Device Stopped\n");
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Thread::wait_for_ready()
{
	int timeout = 0;
	while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
		usleep(1);
		timeout++;
		if (timeout >= 1000000) return -1;
	}

	return 0;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Thread::reset_spi_device()
{
	printf("Reset the Device\n");

	GPIO_MARK1_SET
	bcm2835_GPIO->GPCLR0 = GPIO_GPCLR0_GP25;
	usleep(10000);
	bcm2835_GPIO->GPSET0 = GPIO_GPSET0_GP25;

	if (wait_for_ready() == -1) {
		printf("Reset Device Error\n");
		return -1;
	}

	GPIO_MARK1_CLR

	printf("Device Ready!\n");

	return 0;
}
