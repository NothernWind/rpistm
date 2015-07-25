#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QLabel>

#include "qvextslider.h"


class MotorControl : public QWidget
{
	Q_OBJECT
public:
	explicit MotorControl(QWidget *parent = 0);

private:
	QGridLayout * grid;

	QSpinBox * FreqBox;
	QPushButton * RunButton;

	QVExtSlider * PWM_CH1P;
	QVExtSlider * PWM_CH2P;
	QVExtSlider * PWM_CH3P;

	QRadioButton * PWM_CH1N;
	QRadioButton * PWM_CH2N;
	QRadioButton * PWM_CH3N;

	void create_mc(void);
};

#endif // MOTORCONTROL_H
