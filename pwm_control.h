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
#include <QTimer>

#include <math.h>
#include <stdio.h>

#include "qvextslider.h"

#include "spi_protocol.h"

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

	void setProtocol(SPI_Protocol * sp) {spi_ptcl = sp;}

signals:
	void started(bool);

private slots:
	void pwm_param_changed(int);
	void start_clicked(void);

private:
	bool start_state;

	int tim_div;
	int tim_psc;
	int tim_period;
	int tim_duty;
	int tim_dzone;
	int pwm_duty;

	double f_dts;
	double f_tim;
	double t_tim;
	double f_pwm;
	double t_pwm;
	double t_pulse;
	double t_dzone;

	t_spctl_tim header;
	t_spctl_pwm paket;

	QGridLayout * grid;
	QPushButton * start;
	QPushButton * single_rq;
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

	SPI_Protocol * spi_ptcl;

	void create_pwm_ctrl(void);
	QFrame *addSeparator(QFrame::Shape shape = QFrame::HLine,
		QWidget *parent = 0);
	void update_values(void);
	void calc_values(void);
	QString valueToStr(double value, bool ft);
	void update_ctrl(void);

	void send_pwm_request(void);

};

#endif // PWM_CONTROL_H
