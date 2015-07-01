/*!
 ********************************************************************
 * file
 * author	kaljan
 * version	0.0.0
 * date
 * brief
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

#include "bcm2835.h"

class ADC_Dial;

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
class Window : public QWidget
{
	Q_OBJECT
public:
	explicit Window(QWidget *parent = 0);

private slots:
	void spi_send_btn_clicked(void);
	void toggle_led(bool t);

private:
	QGridLayout * grid;
	ADC_Dial * ADC1_dial;
	ADC_Dial *ADC2_dial;
	QCheckBox * led_box;
	QPushButton * spi_send_btn;

	int LED_Init(void) {
		if (bcm2835_gpio_map() == -1) return -1;
		bcm2835_GPIO->GPFSEL2.bits.FSELn6 = GPIO_FSEL_OUTPUT;
		return 0;
	}

};

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
class ADC_Dial : public QWidget
{
	Q_OBJECT
public:
	explicit ADC_Dial(QWidget *parent = 0)
		:QWidget(parent)
	{
		create_adc_dial("dial");
	}

	explicit ADC_Dial(const QString &d_title, QWidget *parent = 0)
		:QWidget(parent)
	{
		create_adc_dial(d_title);
	}

	void setRange(int min, int max) { dial->setRange(min, max);}

	int value(void) { return dial->value();}
	void setValue(int value) {dial->setValue(value);}

private slots:
	void dial_value_changed(int value) {
		dv_label->setText(QString("%1").arg(value));
	}

private:
	QGridLayout * grid;
	QLabel * tt_label;
	QDial * dial;
	QLabel *dv_label;

	void create_adc_dial(const QString &d_title) {
		grid = new QGridLayout(this);
		dial = new QDial(this);
		tt_label = new QLabel(d_title, this);
		dv_label = new QLabel("0", this);

		setLayout(grid);

		grid->addWidget(tt_label, 0, 0);
		grid->addWidget(dial, 1, 0);
		grid->addWidget(dv_label, 2, 0);

		grid->setMargin(0);

		adjustSize();
		setFixedSize(size());

		grid->setAlignment(tt_label, Qt::AlignCenter);
				grid->setAlignment(dial, Qt::AlignHCenter);
				grid->setAlignment(dv_label, Qt::AlignCenter);

		connect(dial, SIGNAL(valueChanged(int)),
			this, SLOT(dial_value_changed(int)));

	}
};

#endif // WINDOW_H
