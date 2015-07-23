/*!
 ********************************************************************
 * \file
 * \author
 * \version
 * \date
 * \brief
 *
 ********************************************************************
 */
#include "pwm_control.h"

PWM_Control::PWM_Control(QWidget *parent)
	: QWidget(parent)
{
	create_pwm_ctrl();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::pwm_param_changed(int)
{
	if (start_state == true) return;
	update_values();
	calc_values();
	update_ctrl();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::start_clicked()
{
	if (start_state == false) {
		start->setText("stop");
		start_state = true;
	} else {
		start->setText("start");
		start_state = false;
	}
	emit started(start_state);
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::create_pwm_ctrl()
{
	start_state = false;

	grid = new QGridLayout(this);

	psc = new QVExtSlider("psc", this);
	period = new QVExtSlider("period", this);
	duty = new QVExtSlider("duty", this);
	dzone = new QVExtSlider("dzone", this);
	fdiv = new QComboBox(this);
	ngen = new QCheckBox("neg.en", this);
	start = new QPushButton("start", this);
	single_rq = new QPushButton("set", this);

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

	dzone->setDisabled(true);

	tick_freq->setFixedWidth(120);

	psc->setFixedWidth(50);
	period->setFixedWidth(50);
	duty->setFixedWidth(50);
	dzone->setFixedWidth(50);

	grid->addWidget(psc, 0, 0, 9, 1);
	grid->addWidget(period, 0, 1, 9, 1);
	grid->addWidget(duty, 0, 2, 9, 1);
	grid->addWidget(dzone, 0, 3, 9, 1);

	grid->addWidget(addSeparator(QFrame::VLine, this), 0, 4, 9, 1);

	grid->addWidget(new QLabel("Fck", this), 0, 5);
	grid->addWidget(fdiv, 0, 6, 1, 2);
	grid->addWidget(ngen, 0, 8);
	grid->addWidget(start, 1, 5, 1, 2);
	grid->addWidget(single_rq, 1, 7, 1, 2);

	grid->addWidget(addSeparator(QFrame::HLine, this), 2, 5, 1, 4);

	QStringList l_list;
	l_list << "F(tim)   = " << "T(tim)   = " << "F(PWM)   = "
		<< "T(PWM)   = " << "T(pulse) = " << "T(dzone) = ";
	for (int i = 0; i < l_list.size(); i++) {
		grid->addWidget(new QLabel(l_list[i], this), i + 3, 5, 1, 2);
	}

//	grid->addWidget(new QLabel("F(tim)   = "), 3, 5, 1, 2);
//	grid->addWidget(new QLabel("T(tim)   = "), 4, 5, 1, 2);
//	grid->addWidget(new QLabel("F(PWM)   = "), 5, 5, 1, 2);
//	grid->addWidget(new QLabel("T(PWM)   = "), 6, 5, 1, 2);
//	grid->addWidget(new QLabel("T(pulse) = "), 7, 5, 1, 2);
//	grid->addWidget(new QLabel("T(dzone) = "), 8, 5, 1, 2);

	grid->addWidget(tick_freq, 3, 7, 1, 2);
	grid->addWidget(tick_time, 4, 7, 1, 2);
	grid->addWidget(pwm_freq, 5, 7, 1, 2);
	grid->addWidget(pwm_period, 6, 7, 1, 2);
	grid->addWidget(pwm_pulse_time, 7, 7, 1, 2);
	grid->addWidget(pwm_dzone_time, 8, 7, 1, 2);

	grid->setRowStretch(0, 1);

	connect(psc, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(period, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(duty, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(dzone, SIGNAL(valueChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(fdiv, SIGNAL(currentIndexChanged(int)),
		this, SLOT(pwm_param_changed(int)));
	connect(ngen, SIGNAL(toggled(bool)),
		dzone, SLOT(setEnabled(bool)));
	connect(start, SIGNAL(clicked()),
		this, SLOT(start_clicked()));
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
QFrame *PWM_Control::addSeparator(QFrame::Shape shape, QWidget *parent)
{
	QFrame *f = new QFrame(parent);
	f->setFrameShadow(QFrame::Sunken);
	f->setLineWidth(1);
	f->setMidLineWidth(0);
	f->setFrameShape(shape);
	return f;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::update_values() {

	tim_div = fdiv->currentIndex() + 1;
	tim_psc = psc->getValue();
	tim_period = period->getValue();
	tim_duty = duty->getValue();
	tim_dzone = dzone->getValue();
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::calc_values() {
	f_dts = (double)STM32F100xx_Fck / (double)(tim_div);
	f_tim = f_dts / (double)(tim_psc + 1);
	t_tim = 1.0f / f_tim;

	t_pwm = (double)(tim_period) * t_tim;
	if (t_pwm > 0) f_pwm = 1.0f / t_pwm;
	else f_pwm = 0;

	pwm_duty = (tim_period * tim_duty) / 100;

	t_pulse = ((double)pwm_duty) * t_tim;
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
QString PWM_Control::valueToStr(double value, bool ft) {
	double v = fabs(value);
	int p = 0;
	QStringList sl;

	if (ft) sl << "Hz" << "kHz" << "MHz" << "GHz" << "!";
	else sl << "s" << "ms" << "us" << "ns" << "!";


	if (v != 0) {
		if (ft == false) {
			while (v < 1) { v *= 1000; p++;}
		} else {
			while (v > 999) {v /= 1000; p++;}
		}
	}

	return QString("%1 %2").arg(v).arg(sl[p < 4 ? p : 4]);
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::update_ctrl() {
	tick_freq->setText(valueToStr(f_tim, true));
	tick_time->setText(valueToStr(t_tim, false));
	pwm_freq->setText(valueToStr(f_pwm, true));
	pwm_period->setText(valueToStr(t_pwm, false));
	pwm_pulse_time->setText(valueToStr(t_pulse, false));
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void PWM_Control::send_pwm_request()
{
	update_values();
	calc_values();
	update_ctrl();

	if (ngen->isChecked() == true) {
		header.bits.CH1N_En = 1;
		header.bits.DT = tim_dzone;
	} else {
		header.bits.CH1N_En = 0;
		header.bits.DT = 0;
	}

	header.bits.CK_Div = fdiv->currentIndex();

	paket.param = header.all;

	paket.div = tim_psc;
	paket.period = tim_period;
	paket.duty = pwm_duty;

	spi_ptcl->setPWM_Params(paket);
}
