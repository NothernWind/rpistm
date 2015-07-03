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
#ifndef DINPUT_H
#define DINPUT_H

#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

/*!
 ********************************************************************
 * brief
 *
 ********************************************************************
 */
class AnalogControl : public QWidget
{
	Q_OBJECT
public:
	explicit AnalogControl(QWidget *parent = 0);

	void setRange(qreal min, qreal max) {

		range_min = min;
		range_max = max;
		update();
	}

	void setMinimum(qreal min) {range_min = min; update();}
	void setMaximum(qreal max) {range_max = max; update();}
	void setTitle(const QString &name) {c_name = name; update();}

public slots:
	void setPen(const QPen &pen) {this->pen = pen; update();}

	void setrot(qreal value) {
		in_value = value;
		rotate_angle = value * (240.000 / (range_max - range_min));
		update();
	}

protected:
	void paintEvent(QPaintEvent *);

private:
	qreal rotate_angle;
	qreal range_min;
	qreal range_max;
	qreal in_value;

	int center_diameter;

	QColor arrow_color;
	QColor arror_border_color;
	QColor scale_color;
	QColor bg_scale_color;
	QColor center_color;
	QColor border_color;

	QString c_name;

	QPen pen;

};

#endif // DINPUT_H
