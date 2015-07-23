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

	QStringList list;
	list << "/1" << "/2" << "/4";

	grid->addWidget(psc, 0, 0);
	grid->addWidget(period, 0, 1);
	grid->addWidget(duty, 0, 2);
	grid->addWidget(dzone, 0, 3);

	grid->addWidget(new QLabel("Fck", this), 1, 0);
	grid->addWidget(fdiv, 1, 1);
	grid->addWidget(ngen, 1, 2, 1, 2);
	grid->addWidget(start, 2, 0, 1, 2);

}
