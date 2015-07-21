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
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QDial>
#include <QSpinBox>

#include <stdio.h>

#include "analogcontrol.h"
#include "characterdisplay.h"

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

private:
	bool start_state;

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

	SPI_Protocol * spi_device;

	void createWindow(void);
	void initilizeSystem(void);

};

#endif // WINDOW_H
