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

#include <stdio.h>

#include "spi0.h"
#include "bcm2835.h"

t_spi * bcm2835_SPI;

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
int bcm2835_spi0_map(void)
{
	printf("Map SPI0\n");
	if (bcm2835_periph_map(&spi_dsc, BCM2835_PERIPH_BASE | SPI_OFFSET) == -1) {
		printf("Failed to map the physical SPI registers into the virtual memory space.\n");
		return -1;
	}
	bcm2835_SPI = (t_spi *)spi_dsc.addr;
	printf("Success\n");
	return 0;
}

/*!
 ********************************************************************
 * \brief
 * 
 ********************************************************************
 */
int spi0_unidir_poll_init(int ckdiv, int flags)
{
	if (bcm2835_spi0_map() == -1) return -1;
	
	printf("Configure SPI:\n");

	if (flags & SPI0_CHPA_BEGINN)
		bcm2835_SPI->CSR.bits.CHPA = 1;

	if (flags & SPI0_CPOL_HIGH)
		bcm2835_SPI->CSR.bits.CPOL = 1;
	
	bcm2835_SPI->CSR.bits.CLEAR = 0x3;
	bcm2835_SPI->CLR = ckdiv;
	bcm2835_SPI->CSR.bits.TE_EN = 1;
	
	printf(
		"CHPA = %d;\n"
		"CPOL = %d;\n"
		"F(CK) = %f Hz;",
		bcm2835_SPI->CSR.bits.CHPA,
		bcm2835_SPI->CSR.bits.CPOL,
		((double)250000000) / ((double)ckdiv)
	);


	return 0;
}

void spi0_unidir_poll_deinit(void)
{
	printf("Deinit SPI\n");
	bcm2835_SPI->CSR.all = 0;
	printf("Unmap SPI\n");
	bcm2835_periph_unmap(&spi_dsc);
}

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
