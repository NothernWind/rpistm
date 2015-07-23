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

#include "qvextslider.h"

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

private:

	QGridLayout * grid;
	QPushButton * start;
	QComboBox * fdiv;

	QVExtSlider * psc;
	QVExtSlider * period;
	QVExtSlider * duty;
	QVExtSlider * dzone;

	QCheckBox * ngen;

	void create_pwm_ctrl(void);


};

#endif // PWM_CONTROL_H
