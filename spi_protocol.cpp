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

	if (spi0_wait_process() != 0) {
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
	return 0;
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

	if (spi0_wait_process() != 0) {
		printf("SPI Device Timeout error on step 1\n");
		return;
	}

	spi0_unidir_poll_block_rx((char *)(&spi_temp_data[0]), 4);

	if (spi0_wait_process() != 0) {
		printf("SPI Device Timeout error on step 2\n");
		return;
	}

	adc1 = spi_temp_data[0];
	adc2 = spi_temp_data[1];

	delete [] spi_temp_data;
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

	if (spi0_wait_process()  !=0) {
		printf("SPI Device Timeout error on step 1\n");
		return;
	}

	spi0_unidir_poll_block_tx(str, 32);

	if (spi0_wait_process() != 0) {
		printf("SPI Device Timeout error on step 2\n");
		return;
	}
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void SPI_Protocol::setPWM_Params(t_spctl_pwm pwm_params)
{

}
