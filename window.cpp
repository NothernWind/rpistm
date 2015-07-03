#include "window.h"

Window::Window(QWidget *parent)
	: QWidget(parent)
	, grid(new QGridLayout(this))
	, ADC1_dial(new ADC_Dial("ADC1", this))
	, ADC2_dial(new ADC_Dial("ADC2", this))
	, led_box(new QCheckBox("LED", this))
	, spi_send_btn(new QPushButton("send", this))

{
	setLayout(grid);

	grid->addWidget(ADC1_dial, 1, 0);
	grid->addWidget(ADC2_dial, 1, 1);
	grid->addWidget(led_box, 2, 0);
	grid->addWidget(spi_send_btn, 3, 0);

	led_box->setDisabled(true);

	spi_send_btn->setDisabled(true);

	ADC1_dial->setRange(0, 4096);
	ADC2_dial->setRange(0, 4096);

	adjustSize();
	setFixedSize(this->size());

	if (gpio_init() == -1) return;
	if (spi0_unidir_poll_init(250,
		SPI0_CHPA_BEGINN | SPI0_CPOL_HIGH) == -1) return;

	spi_send_btn->setDisabled(false);
	led_box->setDisabled(false);

	connect(led_box, SIGNAL(toggled(bool)),
		this, SLOT(toggle_led(bool)));

	connect(spi_send_btn, SIGNAL(clicked()),
		this, SLOT(spi_send_btn_clicked()));

}

Window::~Window()
{
	gpio_deinit();
	spi0_unidir_poll_deinit();
}

void Window::spi_send_btn_clicked()
{
	printf("Send one byte to SPI0\n");
	bcm2835_GPIO->GPCLR0.bits.GPIO8 = 1;
	unsigned char data = spi0_unidir_poll_transfer(0xAA);
	bcm2835_GPIO->GPSET0.bits.GPIO8 = 1;
}

void Window::toggle_led(bool t)
{
	if (t == false) {
		bcm2835_GPIO->GPCLR0.bits.GPIO26 = 1;
	} else {
		bcm2835_GPIO->GPSET0.bits.GPIO26 = 1;
	}
}


