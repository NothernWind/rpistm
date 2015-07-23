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
#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QFrame>

#include <math.h>
#include <stdio.h>

#include "qvextslider.h"

#define STM32F100xx_Fck		24000000

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
class PWM_Control : public QWidget
{
	Q_OBJECT
public:
	explicit PWM_Control(QWidget *parent = 0);

private slots:
	void pwm_param_changed(int);

private:
	int tim_div;
	int tim_psc;
	int tim_period;
	int tim_duty;
	int tim_dzone;

	double f_dts;
	double f_tim;
	double t_tim;
	double f_pwm;
	double t_pwm;
	double t_pulse;
	double t_dzone;

	QGridLayout * grid;
	QPushButton * start;
	QComboBox * fdiv;

	QVExtSlider * psc;
	QVExtSlider * period;
	QVExtSlider * duty;
	QVExtSlider * dzone;

	QCheckBox * ngen;

	QLabel * tick_time;			//!< Значение одного тика таймера, мкс.
	QLabel * tick_freq;
	QLabel * pwm_period;		//!< Период ШИМ
	QLabel * pwm_freq;			//!< Частота ШИМ
	QLabel * pwm_pulse_time;	//!< Длительность импульса
	QLabel * pwm_dzone_time;

	void create_pwm_ctrl(void);

	QFrame *addSeparator(QFrame::Shape shape = QFrame::HLine, QWidget *parent = 0);

	void update_values(void) {

		tim_div = fdiv->currentIndex() + 1;
		tim_psc = psc->getValue();
		tim_period = period->getValue();
		tim_duty = duty->getValue();
		tim_dzone = dzone->getValue();
	}

	void calc_values(void) {
		update_values();

		f_dts = (double)STM32F100xx_Fck / (double)(tim_div);
		f_tim = f_dts / (double)(tim_psc + 1);
		t_tim = 1.0f / f_tim;

		t_pwm = (double)(tim_period) * t_tim;
		if (t_pwm > 0) f_pwm = 1.0f / t_pwm;
		else f_pwm = 0;

		t_pulse = (double)((tim_period * tim_duty) / 100) * t_tim;
	}

	QString valueToStr(double value, bool ft) {
		double v = fabs(value);
		int p = 0;
		QStringList sl;

		if (ft) sl << "Hz" << "kHz" << "MHz" << "GHz" << "null" << "one";
		else sl << "s" << "ms" << "us" << "ns" << "null" << "one";


		if (v != 0) {
			if (ft == false) {
				while (v < 1) { v *= 1000; p++;}
			} else {
				while (v > 999) {v /= 1000; p++;}
			}
		}

		return QString("%1 %2").arg(v).arg(sl[p]);
	}

	void update_ctrl(void) {
		calc_values();
		tick_freq->setText(valueToStr(f_tim, true));
		tick_time->setText(valueToStr(t_tim, false));
		pwm_freq->setText(valueToStr(f_pwm, true));
		pwm_period->setText(valueToStr(t_pwm, false));
		pwm_pulse_time->setText(valueToStr(t_pulse, false));
	}

};

#endif // PWM_CONTROL_H
