/*!
 ********************************************************************
 * \file
 * \author
 * \version
 * \date
 * \brief
 *
 ********************************************************************
 */
#include "spi_protocol.h"

SPI_Protocol::SPI_Protocol(QObject *parent)
	: QObject(parent)
	, device_status(0)
{
	device_status = initializeDevice();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Protocol::resetDevice()
{
	GPIO_MARK1_SET
	bcm2835_GPIO->GPCLR0 = GPIO_GPCLR0_GP25;
	usleep(10000);
	bcm2835_GPIO->GPSET0 = GPIO_GPSET0_GP25;

	if (wait_for_ready() == -1) {
		printf("Reset Device Error\n");
		return -1;
	}

	return 0;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int SPI_Protocol::initializeDevice()
{
	if (gpio_init() != 0) return -1;

	if (spi0_unidir_poll_init(250,
		SPI0_CHPA_BEGINN | SPI0_CPOL_HIGH) != 0) return -2;

	if (resetDevice() != 0) return -3;

	printf("Device Ready!\n");
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void SPI_Protocol::deInitializeSPI()
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
void SPI_Protocol::getADCValues(
	unsigned short &adc1, unsigned short &adc2)
{
	unsigned short *spi_temp_data;

	spi_temp_data = new unsigned short[2];

	spi_request.bits.rqn = 0x01;
	spi_request.bits.rw = 1;
	spi0_unidir_poll_block_tx((const char *)(&spi_request), 2);

	if (spi_device->wait_for_ready() == -1) {
		printf("SPI Device Timeout error on step 1\n");
		return;
	}

	spi0_unidir_poll_block_rx((char *)(&spi_temp_data[0]), 4);

	if (spi_device->wait_for_ready() == -1) {
		printf("SPI Device Timeout error on step 2\n");
		return;
	}

	adc1 = spi_temp_data[0];
	adc2 = spi_temp_data[1];
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void SPI_Protocol::writeToDisplay(const char *str)
{
	spi_request.bits.rqn = 0x01;
	spi_request.bits.rw = 0;

	spi0_unidir_poll_block_tx((const char *)(&spi_request), 2);

	if (spi_device->wait_for_ready() == -1) {
		printf("SPI Device Timeout error on step 1\n");
		return;
	}

	spi0_unidir_poll_block_tx(str, 32);


	if (spi_device->wait_for_ready() == -1) {
		printf("SPI Device Timeout error on step 2\n");
		return;
	}
}


