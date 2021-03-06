/*!
 ********************************************************************
 * \file	window.h
 * \author	NothernWind
 * \version	0.0.3
 * \date	05.03.2015
 * \brief
 *
 ********************************************************************
 */
#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QTimer>
#include <QGroupBox>
#include <QComboBox>

#include <stdio.h>

#include "analogcontrol.h"
#include "characterdisplay.h"
#include "qvextslider.h"
#include "pwm_control.h"
#include "motorcontrol.h"

#include "spi_protocol.h"



class ADC_Dial;

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
class Window : public QWidget
{
	Q_OBJECT
public:
	explicit Window(QWidget *parent = 0);
	~Window();

private slots:
	void toggle_led(bool t);
	void spi_start_btn_clicked(void);
	void single_transfer_btn_clicked(void);
	void continuous_transfer(void);

private:
	bool start_state;

	unsigned short ADC_Values[2];

	QGridLayout * grid;
	ADC_Dial * ADC1_dial;
	ADC_Dial *ADC2_dial;
	QCheckBox * led_box;
	QPushButton * spi_start_btn;
	QLabel * spi_data_label;
	AnalogControl * ADC1_control;
	AnalogControl * ADC2_control;
	QPushButton * single_transfer_btn;
	CharacterDisplay * ch_display;

	QGroupBox * pwm_group;
	QGridLayout * pwm_grid;
	PWM_Control * pwmctrl;

	MotorControl * mctrl;

	QTimer * timer;

	SPI_Protocol * spi_device;

	void createWindow(void);
	void initilizeSystem(void);
	void add_AnalogControl(void);
	void add_PWM_Control(void);
	void add_LCD(void);
	void add_LedBox(void);

};

#endif // WINDOW_H
