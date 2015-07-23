HEADERS += \
    window.h \
    bcm2835/bcm2835.h \
    bcm2835/gpio.h \
    bcm2835/spi0.h \
    analogcontrol.h \
    characterdisplay.h \
    spi_protocol.h \
    qvextslider.h \
    pwm_control.h

SOURCES += \
    window.cpp \
    main.cpp \
    bcm2835/bcm2835.c \
    bcm2835/gpio.c \
    bcm2835/spi0.c \
    analogcontrol.cpp \
    characterdisplay.cpp \
    spi_protocol.cpp \
    pwm_control.cpp

win32 {
	QT += widgets
	error("Can't build this project on win32")
}
