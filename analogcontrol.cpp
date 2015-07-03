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
#include "analogcontrol.h"

AnalogControl::AnalogControl(QWidget *parent)
	: QWidget(parent)
	, rotate_angle(0)
	, range_min(0)
	, range_max(100)
	, in_value(0)
	, center_diameter(30)
	, arrow_color(240, 240, 192)
	, arror_border_color(64, 64, 64)
	, scale_color(255, 255, 240)
	, bg_scale_color(0, 0, 0)
	, center_color(64, 64, 64)
	, border_color(76, 76, 92)
	, c_name("Control")

{
	setFixedSize(100, 140);
}

/*!
 ********************************************************************
 * \brief
 *
 ********************************************************************
 */
void AnalogControl::paintEvent(QPaintEvent */*event*/)
{
	QPainter painter(this);

// Стрелка
	static const QPoint points[5] = {
		QPoint(4, 0),
		QPoint(4, 30),
		QPoint(0, 40),
		QPoint(-4, 30),
		QPoint(-4, 0)
	};

	static const QPoint points1[3] = {
		QPoint(0, 38),
		QPoint(2, 44),
		QPoint(-2, 44)
	};


// Основа
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.translate(50, 70);
	pen.setColor(border_color);
	pen.setWidth(4);
	painter.setPen(pen);
	painter.setBrush(bg_scale_color);
	painter.drawEllipse(-48, -48, 96, 96);

// Надписи
	pen.setWidth(2);
	painter.setPen(pen);
	painter.drawRoundedRect(-49, -69, 96, 16, 5, 5);
	painter.drawRoundedRect(-49, 53, 96, 16, 5, 5);

	pen.setColor(Qt::white);
	painter.setPen(pen);
	painter.setFont(QFont("Monospace", 10, -1, false));
	painter.drawText(-49, -69, 96, 16, Qt::AlignCenter, c_name);
	painter.drawText(-49, 53, 96, 16, Qt::AlignCenter,
		QString("%1").arg(in_value));

	painter.drawText(-20, 23, 40, 16, Qt::AlignCenter, "x1000");

	QFont fnt;
	fnt = QFont("Monospace", 12, -1, false);
	fnt.setBold(true);

	painter.setFont(fnt);

	painter.drawText(-29, 7, 16, 16, Qt::AlignLeft, "0");
	painter.drawText(-32, -15, 16, 16, Qt::AlignLeft, "1");
	painter.drawText(-16, -33, 16, 16, Qt::AlignLeft, "2");
	painter.drawText(0, -33, 16, 16, Qt::AlignRight, "3");
	painter.drawText(15, -15, 16, 16, Qt::AlignRight, "4");
	painter.drawText(14, 7, 16, 16, Qt::AlignRight, "5");


// Рисуем шкалу
	pen.setColor(scale_color);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(scale_color);

	for (int i = 0; i < 26; i++) {
		painter.save();
		painter.rotate((qreal)(60.0 + ((qreal)i * 9.6)));
		if (i % 5 == 0)
			painter.drawPolygon(points1, 3);
		else painter.drawLine(0, 38, 0, 44);

		painter.restore();
	}

// Рисуем стрелку
	pen.setColor(arror_border_color);
	pen.setWidth(2);
	painter.setPen(pen);
	painter.setBrush(arrow_color);

	painter.save();
	painter.rotate(rotate_angle + 60);
	painter.drawPolygon(points, 5);
	painter.restore();

	pen.setColor(center_color);
	painter.setPen(pen);
	painter.setBrush(center_color);

	int c_pos = (-1 * (center_diameter / 2));

// Ну и мелочь в виде закрывающего кружка
	painter.drawEllipse(c_pos, c_pos, center_diameter, center_diameter);

}
