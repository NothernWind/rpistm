HEADERS += \
    window.h \
    bcm2835/bcm2835.h \
    bcm2835/gpio.h \
    bcm2835/spi0.h \
    analogcontrol.h \
    spi_thread.h

SOURCES += \
    window.cpp \
    main.cpp \
    bcm2835/bcm2835.c \
    bcm2835/gpio.c \
    bcm2835/spi0.c \
    analogcontrol.cpp \
    spi_thread.cpp

QT += widgets
