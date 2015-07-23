#include "pwm_control.h"

PWM_Control::PWM_Control(QWidget *parent)
	: QWidget(parent)
{
	create_pwm_ctrl();
}

void PWM_Control::pwm_param_changed(int)
{
	int period_v;
	int duty_v;
	int d_result;

	period_v = period->getValue();
	duty_v = duty->getValue();

	d_result = (period_v * duty_v) / 100;

	pwm_period->setText(QString("%1").arg(d_result));
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

	tick_time->setFixedWidth(50);

	psc->setFixedWidth(50);
	period->setFixedWidth(50);
	duty->setFixedWidth(50);
	dzone->setFixedWidth(50);

	grid->addWidget(psc, 0, 0, 10, 1);
	grid->addWidget(period, 0, 1, 10, 1);
	grid->addWidget(duty, 0, 2, 10, 1);
	grid->addWidget(dzone, 0, 3, 10, 1);

	grid->addWidget(addSeparator(QFrame::VLine, this), 0, 4, 10, 1);

	grid->addWidget(new QLabel("Fck", this), 0, 5);
	grid->addWidget(fdiv, 0, 6, 1, 2);
	grid->addWidget(ngen, 1, 5, 1, 3);
	grid->addWidget(start, 2, 5, 1, 3);

	grid->addWidget(addSeparator(QFrame::HLine, this), 3, 5, 1, 3);

	grid->addWidget(new QLabel("F(tim)   = "), 4, 5, 1, 2);
	grid->addWidget(new QLabel("T(tim)   = "), 5, 5, 1, 2);
	grid->addWidget(new QLabel("F(PWM)   = "), 6, 5, 1, 2);
	grid->addWidget(new QLabel("T(PWM)   = "), 7, 5, 1, 2);
	grid->addWidget(new QLabel("T(pulse) = "), 8, 5, 1, 2);
	grid->addWidget(new QLabel("T(dzone) = "), 9, 5, 1, 2);

	grid->addWidget(tick_time, 4, 7);
	grid->addWidget(tick_freq, 5, 7);
	grid->addWidget(pwm_period, 6, 7);
	grid->addWidget(pwm_freq, 7, 7);
	grid->addWidget(pwm_pulse_time, 8, 7);
	grid->addWidget(pwm_dzone_time, 9, 7);

	grid->setRowStretch(0, 1);

	connect(psc, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(period, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(duty, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(dzone, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));

}

QFrame *PWM_Control::addSeparator(QFrame::Shape shape, QWidget *parent)
{
	QFrame *f = new QFrame(parent);
	f->setFrameShadow(QFrame::Sunken);
	f->setLineWidth(1);
	f->setMidLineWidth(0);
	f->setFrameShape(shape);
	return f;
}
