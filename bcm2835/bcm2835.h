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
#ifndef BCM2835_H
#define BCM2835_H

#ifdef __cplusplus
extern "C" {
#endif

// Defines ----------------------------------------------------------
#define CPU_CORE_CLOCK	250000000
/*!
 ********************************************************************
 * Physical addresses range from 0x20000000 to 0x20FFFFFF for 
 * peripherals. The bus addresses for peripherals are set up to map 
 * onto the peripheral bus address range starting at 0x7E000000. 
 * Thus a peripheral advertised here at bus address 0x7Ennnnnn is 
 * available at physical address 0x20nnnnnn.
 ********************************************************************
 */
#define BCM2835_PERIPH_BASE		0x20000000

#define SYS_TIM_OFFSET			0x00003000
#define DMA_OFFSET				0x00007000
#define TIM_OFFSET				0x0000B000

#define CM_GPCTL_OFFSET			0x00101000

#define GPIO_OFFSET				0x00200000
#define UART_OFFSET				0x00201000
#define PCM_OFFSET				0x00203000
#define SPI_OFFSET				0x00204000
#define BSC0_OFFSET				0x00205000
#define PWM_OFFSET				0x0020C000

#define BSC_SPI_OFFSET			0x00214000

#define AUX_OFFSET				0x00215000
#define AUX_MU_OFFSET			0x00215040
#define AUX_SPI1_OFFSET			0x00215080
#define AUX_SPI2_OFFSET			0x002150C0

#define EMMC_OFFSET				0x00300000

#define BSC1_OFFSET				0x00804000
#define BSC2_OFFSET				0x00805000

// GPIO defines -----------------------------------------------------
#define GPIO_FSEL_INPUT		0x00
#define GPIO_FSEL_OUTPUT	0x01
#define GPIO_FSEL_ALT0		0x04
#define GPIO_FSEL_ALT1		0x05
#define GPIO_FSEL_ALT2		0x06
#define GPIO_FSEL_ALT3		0x07
#define GPIO_FSEL_ALT4		0x03
#define GPIO_FSEL_ALT5		0x02

// Typedefs ---------------------------------------------------------

// GPIO  Typedefs ---------------------------------------------------
typedef union _t_gpsn {
	unsigned int all;
	struct {
		unsigned FSELn0:3;
		unsigned FSELn1:3;
		unsigned FSELn2:3;
		unsigned FSELn3:3;
		unsigned FSELn4:3;
		unsigned FSELn5:3;
		unsigned FSELn6:3;
		unsigned FSELn7:3;
		unsigned FSELn8:3;
		unsigned FSELn9:3;
		unsigned :2;
	}bits;
} t_gpsn;

typedef union _t_gp0 {
	unsigned int all;
	struct {
		unsigned GPIO0:1;
		unsigned GPIO1:1;
		unsigned GPIO2:1;
		unsigned GPIO3:1;
		unsigned GPIO4:1;
		unsigned GPIO5:1;
		unsigned GPIO6:1;
		unsigned GPIO7:1;
		unsigned GPIO8:1;
		unsigned GPIO9:1;
		unsigned GPIO10:1;
		unsigned GPIO11:1;
		unsigned GPIO12:1;
		unsigned GPIO13:1;
		unsigned GPIO14:1;
		unsigned GPIO15:1;
		unsigned GPIO16:1;
		unsigned GPIO17:1;
		unsigned GPIO18:1;
		unsigned GPIO19:1;
		unsigned GPIO20:1;
		unsigned GPIO21:1;
		unsigned GPIO22:1;
		unsigned GPIO23:1;
		unsigned GPIO24:1;
		unsigned GPIO25:1;
		unsigned GPIO26:1;
		unsigned GPIO27:1;
		unsigned GPIO28:1;
		unsigned GPIO29:1;
		unsigned GPIO30:1;
		unsigned GPIO31:1;
	} bits;
} t_gp0;

typedef union _t_gp1 {
	unsigned int all;
	struct {
		unsigned GPIO32:1;
		unsigned GPIO33:1;
		unsigned GPIO34:1;
		unsigned GPIO35:1;
		unsigned GPIO36:1;
		unsigned GPIO37:1;
		unsigned GPIO38:1;
		unsigned GPIO39:1;
		unsigned GPIO40:1;
		unsigned GPIO41:1;
		unsigned GPIO42:1;
		unsigned GPIO43:1;
		unsigned GPIO44:1;
		unsigned GPIO45:1;
		unsigned GPIO46:1;
		unsigned GPIO47:1;
		unsigned GPIO48:1;
		unsigned GPIO49:1;
		unsigned GPIO50:1;
		unsigned GPIO51:1;
		unsigned GPIO52:1;
		unsigned GPIO53:1;
		unsigned :10;
	} bits;
} t_gp1;

typedef struct _t_gpio {
	volatile t_gpsn GPFSEL0;
	volatile t_gpsn GPFSEL1;
	volatile t_gpsn GPFSEL2;
	volatile t_gpsn GPFSEL3;
	volatile t_gpsn GPFSEL4;
	volatile t_gpsn GPFSEL5;
	volatile unsigned int r1;
	volatile t_gp0 GPSET0;
	volatile t_gp1 GPSET1;
	volatile unsigned int r2;
	volatile t_gp0 GPCLR0;
	volatile t_gp1 GPCLR1;
	volatile unsigned int r3;
	volatile t_gp0 GPLEV0;
	volatile t_gp1 GPLEV1;
	volatile unsigned int r4;
	volatile t_gp0 GPEDS0;
	volatile t_gp1 GPEDS1;
	volatile unsigned int r5;
	volatile t_gp0 GPREN0;
	volatile t_gp1 GPREN1;
	volatile unsigned int r6;
	volatile t_gp0 GPFEN0;
	volatile t_gp1 GPFEN1;
	volatile unsigned int r7;
	volatile t_gp0 GPHEN0;
	volatile t_gp1 GPHEN1;
	volatile unsigned int r8;
	volatile t_gp0 GPLEN0;
	volatile t_gp1 GPLEN1;
	volatile unsigned int r9;
	volatile t_gp0 GPAREN0;
	volatile t_gp1 GPAREN1;
	volatile unsigned int r10;
	volatile t_gp0 GPAFEN0;
	volatile t_gp1 GPAFEN1;
	volatile unsigned int r11;
	volatile unsigned int GPPUD;
	volatile t_gp0 GPPUDCLK0;
	volatile t_gp1 GPPUDCLK1;
	volatile unsigned int r12;
	volatile unsigned int test;
} t_gpio;

// SPI Typedefs -----------------------------------------------------

typedef union _t_spi_cs {
	unsigned int all;
	struct {
		unsigned CS:2;			//!< (RW) Chip Select
		unsigned CHPA:1;		//!< (RW) Clock Phase
		unsigned CPOL:1;		//!< (RW) Clock Polarity
		unsigned CLEAR:2;		//!< (RW) FIFO Clear
		unsigned CSPOL:1;		//!< (RW) Chip Select Polarity
		unsigned TA:1;			//!< (RW) Transfer Active
		unsigned DMAEN:1;		//!< (RW) DMA Enable
		unsigned INTD:1;		//!< (RW) Interrupt on Done
		unsigned INTR:1;		//!< (RW) Interrupt on RXR
		unsigned ADCS:1;		//!< (RW) Automatically Deassert Chip Select
		unsigned REN:1;			//!< (RW) Read Enable
		unsigned LEN:1;			//!< (RW) LoSSI enable
		unsigned LMONO:1;		//!< (RW) Unused 
		unsigned TE_EN:1;		//!< (RW) Unused 
		unsigned DONE:1;		//!< (RO) transfer Done 
		unsigned RXD:1;			//!< (RO) RX FIFO contains Data 
		unsigned TXD:1;			//!< (RO) TX FIFO can accept Data
		unsigned RXR:1;			//!< (RO) RX FIFO needs Reading ( full)
		unsigned RXF:1;			//!< (RO) RX FIFO Full
		unsigned CSPOL0:1;		//!< (RW) Chip Select 0 Polarity
		unsigned CSPOL1:1;		//!< (RW) Chip Select 1 Polarity
		unsigned CSPOL2:1;		//!< (RW) Chip Select 2 Polarity
		unsigned DMA_LEN:1;		//!< (RW) Enable DMA mode in Lossi mode
		unsigned LEN_LONG:1;	/*!< (RW) Enable Long data word in Lossi 
									 mode if DMA_LEN is set */
		unsigned :6;
	} bits;
} t_spi_cs;

typedef union _t_spi_dc {
	unsigned int all;
	struct {
		unsigned char TDREQ;
		unsigned char TPANIC;
		unsigned char RDREQ;
		unsigned char RPANIC;
	} rq;
} t_spi_dc;

typedef struct _t_spi {
	volatile t_spi_cs CSR;
	volatile unsigned int FIFO;
	volatile unsigned int CLR;
	volatile unsigned int DLEN;
	volatile unsigned int LTOH;
	volatile t_spi_dc DCR;
} t_spi;

// Other Typedefs ---------------------------------------------------

struct bcm2835_periph {
	unsigned long paddr;
	int fd;
	void *map;
	volatile unsigned int *addr;
};

// Extern Variables -------------------------------------------------
extern struct bcm2835_periph gpio_dsc;
extern struct bcm2835_periph spi_dsc;
extern t_spi * bcm2835_SPI;
extern t_gpio * bcm2835_GPIO;

// Public Prototypes ------------------------------------------------
int bcm2835_periph_map(struct bcm2835_periph * pr, unsigned long addr) ;
void bcm2835_periph_unmap(struct bcm2835_periph * pr);

int bcm2835_gpio_map(void);
int bcm2835_spi0_map(void);

#ifdef __cplusplus
}
#endif

#endif // BCM2835_H
