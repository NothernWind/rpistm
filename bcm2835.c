/*!
 ********************************************************************
 * \file
 * \author	kaljan.nothern
 * \version	0.0.0
 * \date
 * \brief
 *
 ********************************************************************
 */
#include "bcm2835.h"

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// Variables --------------------------------------------------------
struct bcm2835_periph gpio_dsc = {BCM2835_PERIPH_BASE | GPIO_OFFSET};
struct bcm2835_periph spi_dsc = {BCM2835_PERIPH_BASE | SPI_OFFSET};
t_gpio * bcm2835_GPIO;
t_spi * bcm2835_SPI;

/*!
 ********************************************************************
 * \brief
 * 
 ********************************************************************
 */
int bcm2835_gpio_map(void) 
{
	printf("Map GPIO\n");
	if (bcm2835_periph_map(&gpio_dsc, BCM2835_PERIPH_BASE | GPIO_OFFSET) == -1) {
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}
	bcm2835_GPIO = (t_gpio *)gpio_dsc.addr;
	printf("Success\n");
	return 0;
}

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
int bcm2835_periph_map(struct bcm2835_periph * pr, unsigned long addr)
{
	if ((pr->fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
		printf("Failed to open /dev/mem, try checking premissions.\n");
		return -1;
	}

	pr->paddr = addr;
		
	pr->map = mmap(
		NULL, 
		4096, 
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		pr->fd, 
		pr->paddr
	);
	
	if (pr->map == MAP_FAILED) {
		perror("mmap");
		printf("Map failed\n");
		return -1;
	}
	
	pr->addr = (volatile unsigned int *)pr->map;	
	return 0;
}

/*!
 ********************************************************************
 * \brief
 * 
 ********************************************************************
 */
void bcm2835_periph_unmap(struct bcm2835_periph * pr)
{
	munmap(pr->map, 4096);
	close(pr->fd);
}

/*!
 ********************************************************************
 * \brief
 * 
 ********************************************************************

int init_piriph(void) {
	printf("Peripheral Initialization\n");
	
	if (periph_map(&gpio_dsc, BCM2835_PERIPH_BASE | GPIO_OFFSET) == -1) {
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	} else printf("[ ok ] GPIO mapped\n");
	
	if (periph_map(&spi_dsc, BCM2835_PERIPH_BASE | SPI_OFFSET) == -1) {
		printf("Failed to map the physical SPI registers into the virtual memory space.\n");
		return -1;
	} else printf("[ ok ] SPI mapped\n");
	
	bcm2835_GPIO = (t_gpio *)gpio_dsc.addr;
	bcm2835_SPI = (t_spi *)spi_dsc.addr;
	
	printf("Config GPIO Alternate function for SPI\n");
	
	bcm2835_GPIO->GPFSEL0.bits.FSELn9 = GPIO_FSEL_ALT0; // 21 GPIO9  SPI0_MISO
	bcm2835_GPIO->GPFSEL1.bits.FSELn0 = GPIO_FSEL_ALT0; // 19 GPIO10 SPI0_MOSI
	bcm2835_GPIO->GPFSEL1.bits.FSELn1 = GPIO_FSEL_ALT0; // 23 GPIO11 SPI_SCLK	
	
	printf("Success\n");
}
 */
