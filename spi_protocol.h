#ifndef SPI_PROTOCOL_H
#define SPI_PROTOCOL_H

#include <QObject>
#include <QThread>

#include <stdio.h>

#include "bcm2835/bcm2835.h"
#include "bcm2835/gpio.h"
#include "bcm2835/spi0.h"

//! Структура запроса к устройству
typedef union _t_spi_request {
	unsigned short all;
	struct {
		unsigned :8;
		unsigned rqn:6;
		unsigned rw:1;
	} bits;
} t_spi_request;

typedef union _t_spctl_tim {
	unsigned short all;
	struct {
		unsigned CK_Div:2;
		unsigned CH1N_En:1;
		unsigned :5;
		unsigned DT:8;
	}bits;
} t_spctl_tim;

typedef struct _t_spctl_pwm{
	unsigned short param;
	unsigned short div;
	unsigned short period;
	unsigned short duty;
} t_spctl_pwm;

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
class SPI_Protocol : public QObject
{
	Q_OBJECT
public:
	explicit SPI_Protocol(QObject *parent = 0);

	~SPI_Protocol(){deInitializeSPI();}

	int getStatus(void) {return device_status;}

	int resetDevice(void);
	int initializeDevice(void);
	void deInitializeSPI(void);
	void getADCValues(unsigned short &adc1, unsigned short &adc2);

public slots:
	void writeToDisplay(const char * str);
	void setPWM_Params(t_spctl_pwm pwm_params);

private:
	int device_status;
	t_spi_request spi_request;
};

#endif // SPI_PROTOCOL_H
