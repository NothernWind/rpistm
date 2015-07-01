#include "window.h"

Window::Window(QWidget *parent)
	: QWidget(parent)
	, grid(new QGridLayout(this))
	, ADC1_dial(new ADC_Dial("ADC1", this))
	, ADC2_dial(new ADC_Dial("ADC2", this))
	, led_box(new QCheckBox("LED", this))

{
	setLayout(grid);

	grid->addWidget(ADC1_dial, 1, 0);
	grid->addWidget(ADC2_dial, 1, 1);
	grid->addWidget(led_box, 2, 0);

	ADC1_dial->setRange(0, 4096);
	ADC2_dial->setRange(0, 4096);

	adjustSize();
	setFixedSize(this->size());

	connect(led_box, SIGNAL(toggled(bool)),
		this, SLOT(toggle_led(bool)));
}

void Window::spi_send_btn_clicked()
{

}

void Window::toggle_led(bool t)
{

}


