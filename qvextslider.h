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
#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QGridLayout>

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
class QVExtSlider : public QWidget
{
	Q_OBJECT
public:
	explicit QVExtSlider(QWidget *parent = 0)
		: QWidget(parent) {
		create_slider("slider", 10);
	}

	explicit QVExtSlider(QString title, QWidget *parent = 0)
		: QWidget(parent) {
		create_slider(title, 0);
	}

	void setValue(int value) { slider->setValue(value);}
	int getValue(void){return slider->value();}
	void setRange(int min, int max) {slider->setRange(min, max);}
	void setMin(int min) {slider->setMinimum(min);}
	void setMax(int max) {slider->setMaximum(max);}

signals:
	void valueChanged(int);

private slots:
	void value_changed(int value){
		valuelbl->setText(QString("%1").arg(value));
		emit this->valueChanged(value);
	}

private:
	QGridLayout * grid;
	QLabel * titlelbl;
	QSlider * slider;
	QLabel * valuelbl;

	void create_slider(const QString & title, int value) {
		grid = new QGridLayout(this);
		titlelbl = new QLabel(title, this);
		slider = new QSlider(Qt::Vertical, this);
		valuelbl = new QLabel("0", this);

		slider->setValue(value);

		grid->addWidget(titlelbl, 0, 0);
		grid->addWidget(slider, 1, 0);
		grid->addWidget(valuelbl, 2, 0);

		grid->setAlignment(titlelbl, Qt::AlignCenter);
		grid->setAlignment(slider, Qt::AlignHCenter);
		grid->setAlignment(valuelbl, Qt::AlignCenter);

		grid->setMargin(0);
		grid->setRowStretch(1, 1);

		this->setLayout(grid);

		connect(slider, SIGNAL(valueChanged(int)),
			this, SLOT(value_changed(int)));

		value_changed(value);
	}

};

#endif // SLIDER_H
