/*!
 ********************************************************************
 * \file	window.cpp
 * \author	NothernWind
 * \version	0.0.3
 * \date	05.07.2015
 * \brief
 *
 * Нужно организовать систему так, чтобы в этом фале небыло никаких
 * упоминаний вообще про железо. только высокий уровень и вызов готовых
 * методов. весь протокол запихнуть в отдельный класс. и в отдельном
 * том классе только создавать методы работы с устройством. кстати
 * нужно что-то подобное сделать и в самом устройстве, что бы нужно
 * было только добавлять функционал.
 *
 * в этом классе нужно создавать только сам виджет и работать на уровне
 * сигналов и слотов и не больше.
 *
 ********************************************************************
 */
#include "window.h"

Window::Window(QWidget *parent)
	: QWidget(parent)
{
	createWindow();
	initilizeSystem();
}

Window::~Window(){}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::createWindow()
{
	grid = new QGridLayout(this);

	led_box = new QCheckBox("LED", this);
	spi_start_btn = new QPushButton("start", this);
	spi_data_label = new QLabel(this);
	ADC1_control = new AnalogControl(this);
	ADC2_control = new AnalogControl(this);
	single_transfer_btn = new QPushButton("send", this);
	ch_display = new CharacterDisplay(this);

	setFont(QFont("Monospace", 10, -1, false));
	setLayout(grid);

	ADC1_control->setRange(0, 5000.000);
	ADC1_control->setTitle("ADC1");

	ADC2_control->setRange(0, 5000.000);
	ADC2_control->setTitle("ADC2");

	led_box->setDisabled(true);
	spi_start_btn->setDisabled(true);
	single_transfer_btn->setDisabled(true);

	ch_display->write_string("Test SPI Device                 ");

	grid->addWidget(ch_display, 0, 0, 1, 3);
	grid->addWidget(ADC1_control, 1, 0, 4, 1);
	grid->addWidget(ADC2_control, 1, 1, 4, 1);

	grid->addWidget(led_box, 1, 2);
	grid->addWidget(spi_start_btn, 2, 2);
	grid->addWidget(single_transfer_btn, 3, 2);
	grid->addWidget(spi_data_label, 5, 0, 1, 3);

	adjustSize();
	setFixedSize(this->size());


}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::initilizeSystem()
{
	timer = new QTimer(this);
	timer->setSingleShot(true);
	start_state = false;

	spi_device = new SPI_Protocol(this);

	if (spi_device->getStatus() != 0) return;

	single_transfer_btn->setDisabled(false);
	spi_start_btn->setDisabled(false);
	led_box->setDisabled(false);

	connect(led_box, SIGNAL(toggled(bool)),
		this, SLOT(toggle_led(bool)));

	connect(spi_start_btn, SIGNAL(clicked()),
		this, SLOT(spi_start_btn_clicked()));

	connect(single_transfer_btn, SIGNAL(clicked()),
		this, SLOT(single_transfer_btn_clicked()));

	connect(ch_display, SIGNAL(changed(const char*)),
		spi_device, SLOT(writeToDisplay(const char*)));

	connect(timer, SIGNAL(timeout()),
		this, SLOT(continuous_transfer());

}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::toggle_led(bool t)
{
	if (t == false) {
		bcm2835_GPIO->GPCLR0 = GPIO_GPSET0_GP26;
	} else {
		bcm2835_GPIO->GPSET0 = GPIO_GPCLR0_GP26;
	}
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::spi_start_btn_clicked()
{
	if (start_state == false) {
		spi_start_btn->setText("stop");
		start_state = true;

		spi_device->getADCValues(ADC_Values[0], ADC_Values[1]);

		ADC1_control->setValue((qreal)ADC_Values[0]);
		ADC2_control->setValue((qreal)ADC_Values[1]);

		timer->start(20);

	} else {
		spi_start_btn->setText("start");
		start_state = false;
	}

	single_transfer_btn->setDisabled(start_state);

}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::continuous_transfer()
{
	if (start_state == true) {
		spi_device->getADCValues(ADC_Values[0], ADC_Values[1]);

		ADC1_control->setValue((qreal)ADC_Values[0]);
		ADC2_control->setValue((qreal)ADC_Values[1]);

		timer->start(20);
	}
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::single_transfer_btn_clicked()
{
	unsigned short adc1;
	unsigned short adc2;

	spi_device->getADCValues(adc1, adc2);

	ADC1_control->setValue((qreal)adc1);
	ADC2_control->setValue((qreal)adc2);
}


