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
#ifndef SPI0_H
#define SPI0_H

#ifdef __cplusplus
extern "C" {
#endif

// Defines ----------------------------------------------------------
#define SPI0_CHPA_MIDDLE	0x00000000
#define SPI0_CHPA_BEGINN	0x00000002
#define SPI0_CPOL_LOW		0x00000000
#define SPI0_CPOL_HIGH		0x00000004

// Prototypes -------------------------------------------------------
int spi0_unidir_poll_init(int ckdiv, int flags);
unsigned char spi0_unidir_poll_transfer(unsigned char data);
unsigned short spi0_poll_read_EMS22A(void);
void spi0_unidir_poll_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // SPI_H
