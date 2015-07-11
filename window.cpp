/*!
 ********************************************************************
 * \file	window.cpp
 * \author	NothernWind
 * \version	0.0.3
 * \date	05.07.2015
 * \brief
 *
 ********************************************************************
 */
#include "window.h"

char strrr[] = "0123456789ABCDEF0123456789ABCDEF";

Window::Window(QWidget *parent)
	: QWidget(parent)
	, start_state(false)
	, grid(new QGridLayout(this))
	, led_box(new QCheckBox("LED", this))
	, spi_start_btn(new QPushButton("start", this))
	, spi_data_label(new QLabel(this))
	, ADC1_control(new AnalogControl(this))
	, ADC2_control(new AnalogControl(this))
	, single_transfer_btn(new QPushButton("send", this))
	, ch_display(new CharacterDisplay(this))
{
	setFont(QFont("Monospace", 10, -1, false));
	setLayout(grid);

	ADC1_control->setRange(0, 5000.000);
	ADC1_control->setTitle("ADC1");

	ADC2_control->setRange(0, 5000.000);
	ADC2_control->setTitle("ADC2");

	led_box->setDisabled(true);
	spi_start_btn->setDisabled(true);
	single_transfer_btn->setDisabled(true);

	ch_display->write_string(strrr);

	grid->addWidget(ch_display, 0, 0, 1, 3);
	grid->addWidget(ADC1_control, 1, 0, 4, 1);
	grid->addWidget(ADC2_control, 1, 1, 4, 1);

    grid->addWidget(led_box, 1, 2);
    grid->addWidget(spi_start_btn, 2, 2);
    grid->addWidget(single_transfer_btn, 3, 2);
    grid->addWidget(spi_data_label, 5, 0, 1, 3);


	adjustSize();
	setFixedSize(this->size());

	spi_device = new SPI_Thread();

	if (spi_device->getState() == false) return;

	single_transfer_btn->setDisabled(false);
	spi_start_btn->setDisabled(false);
	led_box->setDisabled(false);

	single_transfer_btn->setDisabled(false);

	connect(led_box, SIGNAL(toggled(bool)),
		this, SLOT(toggle_led(bool)));

	connect(spi_device, SIGNAL(SPI_Tread_DataRDY(qreal,qreal)),
		this, SLOT(spi_device_value_rdy(qreal,qreal)));

	connect(spi_start_btn, SIGNAL(clicked()),
		this, SLOT(spi_start_btn_clicked()));

	connect(single_transfer_btn, SIGNAL(clicked()),
		this, SLOT(single_transfer_btn_clicked()));

}

Window::~Window()
{
	delete spi_device;
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
		spi_device->SPI_Thread_Start();
		single_transfer_btn->setDisabled(true);
	} else {
		spi_start_btn->setText("start");
		start_state = false;
		spi_device->SPI_Tread_Stop();
		single_transfer_btn->setDisabled(false);
	}

}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::spi_device_value_rdy(qreal v1, qreal v2)
{
	ADC1_control->setValue(v1);
	ADC2_control->setValue(v2);
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::spi_dev_stopped()
{
	spi_start_btn->setText("start");
	start_state = false;
}

char spi_out_data[4] = {0x10, 0x00, 0xFF, 0xFF};
unsigned short ADC_values[2];

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void Window::single_transfer_btn_clicked()
{
	GPIO_MARK1_SET

	spi_request.bits.rqn = 0x01;
	spi_request.bits.rw = 1;

	spi0_unidir_poll_block_transfer(
		(const char *)(&spi_request),
		(char *)(&spi_out_data[2]), 2
		);

	int spi_wait_timeout = 0;

	// Ожидание готовности устройства
	while (bcm2835_GPIO->GPLEV0.bits.GPIO24 == 1) {
		spi_wait_timeout++;
		if (spi_wait_timeout >= 1000000) {
			spi_wait_timeout = 0;
			printf("SPI Device Timeout error\n");
			break;
		}
	}

	spi0_unidir_poll_block_transfer(
		(const char *)(&spi_out_data[0]),
		(char *)(&ADC_values[0]), 4
		);
	GPIO_MARK1_CLR

	ADC1_control->setValue((qreal)ADC_values[0]);
	ADC2_control->setValue((qreal)ADC_values[1]);
}
