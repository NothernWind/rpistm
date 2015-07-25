#include "motorcontrol.h"

MotorControl::MotorControl(QWidget *parent)
	:QWidget(parent)
{
	create_mc();
}

void MotorControl::create_mc() {
	grid = new QGridLayout(this);
	FreqBox = new QSpinBox(this);
	RunButton = new QPushButton("run", this);

	PWM_CH1P = new QVExtSlider("CH1P", this);
	PWM_CH2P = new QVExtSlider("CH2P", this);
	PWM_CH3P = new QVExtSlider("CH3P", this);

	PWM_CH1N = new QRadioButton("CH1N", this);
	PWM_CH2N = new QRadioButton("CH2N", this);
	PWM_CH3N = new QRadioButton("CH3N", this);

	FreqBox->setRange(1, 30);

	grid->addWidget(new QLabel("Freq.", this), 0, 0);
	grid->addWidget(FreqBox, 0, 1);
	grid->addWidget(new QLabel("kHz", this), 0, 2);

	grid->addWidget(RunButton, 1, 0, 1, 3);

	grid->addWidget(PWM_CH1P, 2, 0);
	grid->addWidget(PWM_CH2P, 2, 1);
	grid->addWidget(PWM_CH3P, 2, 2);

	grid->addWidget(PWM_CH1N, 3, 0);
	grid->addWidget(PWM_CH2N, 3, 1);
	grid->addWidget(PWM_CH3N, 3, 2);

	init_state_system();
}

void MotorControl::init_state_system()
{
	connect(PWM_CH1N, SIGNAL(toggled(bool)),
		PWM_CH1P, SLOT(setDisabled(bool)));

	connect(PWM_CH1N, SIGNAL(toggled(bool)),
		PWM_CH2P, SLOT(setEnabled(bool)));

	connect(PWM_CH1N, SIGNAL(toggled(bool)),
		PWM_CH3P, SLOT(setEnabled(bool)));


	connect(PWM_CH2N, SIGNAL(toggled(bool)),
		PWM_CH2P, SLOT(setDisabled(bool)));

	connect(PWM_CH2N, SIGNAL(toggled(bool)),
		PWM_CH1P, SLOT(setEnabled(bool)));

	connect(PWM_CH2N, SIGNAL(toggled(bool)),
		PWM_CH3P, SLOT(setEnabled(bool)));


	connect(PWM_CH3N, SIGNAL(toggled(bool)),
		PWM_CH3P, SLOT(setDisabled(bool)));

	connect(PWM_CH3N, SIGNAL(toggled(bool)),
		PWM_CH1P, SLOT(setEnabled(bool)));

	connect(PWM_CH3N, SIGNAL(toggled(bool)),
		PWM_CH2P, SLOT(setEnabled(bool)));

}
