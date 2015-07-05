/*!
 ********************************************************************
 * \file	main.cpp
 * \author	NothernWind
 * \version	0.0.3
 * \date	05.07.2015
 * \brief
 *
 ********************************************************************
 */
#include <QApplication>
#include "window.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	Window w;
	w.show();
	return app.exec();
}

