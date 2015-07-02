/*!
 ********************************************************************
 * \file
 * \author	kaljan.nothern
 * \version	0.0.0
 * \date	01.03.2015
 * \brief
 *
 * Что сделать.
 * 1. переименовать файлы в spi0
 * 2. Прикрутить енкодер.
 *
 ********************************************************************
 */

#include "spi0.h"
#include "bcm2835.h"

/*!
 ********************************************************************
 * \brief
 * 
 ********************************************************************
 */
int spi0_unidir_poll_init(int ckdiv, int flags)
{
	if (bcm2835_gpio_map() == -1) return -1;
	if (bcm2835_spi0_map() == -1) return -1;
	
	// Для начала настроим порты для SPI0
	printf("Config GPIO Alternate function for SPI\n");
	
	bcm2835_GPIO->GPFSEL0.bits.FSELn9 = GPIO_FSEL_ALT0; // 21 GPIO9  SPI0_MISO
	bcm2835_GPIO->GPFSEL1.bits.FSELn0 = GPIO_FSEL_ALT0; // 19 GPIO10 SPI0_MOSI
	bcm2835_GPIO->GPFSEL1.bits.FSELn1 = GPIO_FSEL_ALT0; // 23 GPIO11 SPI_SCLK
	
	// А это Chip select GPIO8
	bcm2835_GPIO->GPFSEL0.bits.FSELn8 = GPIO_FSEL_OUTPUT;
	bcm2835_GPIO->GPSET0.bits.GPIO8 = 1;
	
	if (flags & SPI0_CHPA_BEGINN)
		bcm2835_SPI->CSR.bits.CHPA = 1;

	if (flags & SPI0_CPOL_HIGH)
		bcm2835_SPI->CSR.bits.CPOL = 1;
	
	bcm2835_SPI->CSR.bits.CLEAR = 0x3;
	bcm2835_SPI->CLR = ckdiv;
	bcm2835_SPI->CSR.bits.TE_EN = 1;
	
	return 0;
}

void spi0_unidir_poll_deinit(void)
{
	printf("Deinit SPI\n");

	bcm2835_GPIO->GPFSEL0.bits.FSELn9 = GPIO_FSEL_INPUT; // 21 GPIO9  SPI0_MISO
	bcm2835_GPIO->GPFSEL1.bits.FSELn0 = GPIO_FSEL_INPUT; // 19 GPIO10 SPI0_MOSI
	bcm2835_GPIO->GPFSEL1.bits.FSELn1 = GPIO_FSEL_INPUT; // 23 GPIO11 SPI_SCLK
	bcm2835_SPI->CSR.all = 0;

	printf("Unmap GPIO\n");
	bcm2835_periph_unmap(&gpio_dsc);
	printf("Unmap SPI\n");
	bcm2835_periph_unmap(&spi_dsc);
}

void spi0_unidir_dma_init(int speed, int flags){}

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
unsigned char spi0_unidir_poll_transfer(unsigned char data)
{
	unsigned char temp;
	//bcm2835_SPI->CSR.bits.TE_EN = 1;
	bcm2835_SPI->CSR.bits.TA = 1;
	bcm2835_SPI->FIFO = data;
	while (bcm2835_SPI->CSR.bits.DONE == 0);
	temp = (unsigned char)(bcm2835_SPI->FIFO);
	bcm2835_SPI->CSR.bits.TA = 0;
	return temp;
}

void spi_unidir_poll_buffer(const char * out, char * in, int size){}

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
unsigned short spi0_poll_read_EMS22A(void)
{
	unsigned short temp;
	bcm2835_GPIO->GPCLR0.bits.GPIO8 = 1;
	
	bcm2835_SPI->CSR.bits.TA = 1;
	bcm2835_SPI->FIFO = 0xFF;
	while (bcm2835_SPI->CSR.bits.DONE == 0);
	temp = ((unsigned short)bcm2835_SPI->FIFO) << 8;
	bcm2835_SPI->FIFO = 0xFF;
	while (bcm2835_SPI->CSR.bits.DONE == 0);
	temp |= (unsigned short)bcm2835_SPI->FIFO;
	bcm2835_SPI->CSR.bits.TA = 0;
	
	bcm2835_GPIO->GPSET0.bits.GPIO8 = 1;
	return temp;
}
