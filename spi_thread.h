/*!
 ********************************************************************
 * \file	spi_thread.h
 * \author	NothernWind
 * \version	0.0.3
 * \date	05.07.2015
 * \brief
 *
 ********************************************************************
 */
#ifndef SPI_THREAD_H
#define SPI_THREAD_H

#include <QThread>
//#include <QTimer>

#include <stdio.h>

#include "bcm2835/bcm2835.h"
#include "bcm2835/gpio.h"
#include "bcm2835/spi0.h"

typedef union _t_spi_request {
	unsigned short all;
	struct {
		unsigned :8;
		unsigned rqn:6;
		unsigned rw:1;
	} bits;
}t_spi_request;

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
class SPI_Thread : public QThread
{
	Q_OBJECT
public:
	explicit SPI_Thread();

	~SPI_Thread();

	void run();

	int SPI_Thread_Init(void);

	void SPI_Thread_DeInit(void);

	bool getState(void) {return spi_state;}
	bool getThreadState(void) {return thread_state;}

	void SPI_Thread_Start(void) {
		thread_state = true;
		this->start();
	}

	void SPI_Tread_Stop(void) {
		thread_state = false;
	}

signals:
	void SPI_Tread_DataRDY(qreal v1, qreal v2);

//private slots:


private:
	bool spi_state;
	bool thread_state;

	unsigned short spi_adc_data[2];
	char out_data[8];

	int reset_spi_device(void);

	t_spi_request spi_request;

};

#endif // SPI_THREAD_H
