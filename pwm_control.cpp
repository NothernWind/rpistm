#include "pwm_control.h"

PWM_Control::PWM_Control(QWidget *parent)
	: QWidget(parent)
{
	create_pwm_ctrl();
}

void PWM_Control::create_pwm_ctrl()
{
	grid = new QGridLayout(this);

	psc = new QVExtSlider("psc", this);
	period = new QVExtSlider("period", this);
	duty = new QVExtSlider("duty", this);
	dzone = new QVExtSlider("dzone", this);
	fdiv = new QComboBox(this);
	ngen = new QCheckBox("neg.en", this);
	start = new QPushButton("start", this);

	tick_time = new QLabel("0", this);
	tick_freq = new QLabel("0", this);
	pwm_period = new QLabel("0", this);
	pwm_freq = new QLabel("0", this);
	pwm_pulse_time = new QLabel("0", this);
	pwm_dzone_time = new QLabel("0", this);

	QStringList list;
	list << "/1" << "/2" << "/4";
	fdiv->addItems(list);

	psc->setRange(0, 65535);
	period->setRange(0, 65535);
	dzone->setRange(0, 255);

	grid->addWidget(psc, 0, 0, 9, 1);
	grid->addWidget(period, 0, 1, 9, 1);
	grid->addWidget(duty, 0, 2, 9, 1);
	grid->addWidget(dzone, 0, 3, 9, 1);

	grid->addWidget(new QLabel("Fck", this), 0, 4);
	grid->addWidget(fdiv, 0, 5);
	grid->addWidget(ngen, 1, 4);
	grid->addWidget(start, 2, 4);

	grid->addWidget(new QLabel("F(tim)   = "), 4, 3);
	grid->addWidget(new QLabel("T(tim)   = "), 4, 4);
	grid->addWidget(new QLabel("F(PWM)   = "), 4, 5);
	grid->addWidget(new QLabel("T(PWM)   = "), 4, 6);
	grid->addWidget(new QLabel("T(pulse) = "), 4, 7);
	grid->addWidget(new QLabel("T(dzone) = "), 4, 8);

	grid->setRowStretch(0, 1);

}
