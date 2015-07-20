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
	, spi_timeout(false)
	, spi_device_status(false)
{
	/*
	 * Инициализация будет делаться следующим образом.
	 *
	 * 1. Тут будем запускать первый поток и дожидаться гтовности
	 * устройства. Во внешнем классе будем или опрашивать статус
	 * готовности при помощи функции bool getReadyStatus(void);
	 * или будем дожидаться сигнала готовности устройства при
	 * помощи сигнала void deviceready(void);
	 *
	 * 2. В конструкторе запускаем инициализацию периферии отдельно
	 * устанавливаем RST в 0 и запускаем таймер. как только таймер
	 * сказал что всё устройство сбросилось, запускаем основной поток
	 * этого класса, и таймер.
	 *
	 */

//	int error_code = SPI_Thread_Init();
//	if (error_code != 0) {
//		printf("SPI Thread Init Failed. Error %d\n", error_code);
//		return;
//	}
//	spi_state = true;

//	for (int i = 0; i < 4; i++) {
//		out_data[i] = 0xFF;
//	}
//	out_data[0] = 0x10;
}

//! Нужно обязательно всё это деинициализировать
SPI_Thread::~SPI_Thread()
{
//	SPI_Thread_DeInit();
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
	if (spi_device_status == false) {

		wait_for_ready();

		return;
	}

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
void SPI_Thread::wait_timeout()
{
	spi_timeout = true;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Thread::wait_for_ready()
{
	// Сначала запустим таймер

	printf("Start Test\n");
	timer->start();
	while(spi_timeout == false);
	spi_timeout = false;
	printf("Test OK\n");


//	while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
//		// А тут будем проверять флаг таймаута

//	}

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
//	int rst_timeout = 0;

	printf("Reset the Device\n");

	GPIO_MARK1_SET
	bcm2835_GPIO->GPCLR0 = GPIO_GPCLR0_GP25;


	bcm2835_GPIO->GPSET0 = GPIO_GPSET0_GP25;

	if (wait_for_ready() == -1) {
		printf("Reset Device Error\n");

		return -1;
	}

	GPIO_MARK1_CLR

//	bcm2835_GPIO->GPCLR0 = GPIO_GPCLR0_GP25;
//	sleep(1);
//	bcm2835_GPIO->GPSET0 = GPIO_GPSET0_GP25;
//	sleep(1);

//	while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
//		rst_timeout++;
//		if (rst_timeout >= 1000000) {
//			rst_timeout = 0;
//			printf("Reset Timeout\n");
//			return -1;
//		}
//	}
	GPIO_MARK1_SET
	printf("Device Ready!\n");
	GPIO_MARK1_CLR

	return 0;
}
