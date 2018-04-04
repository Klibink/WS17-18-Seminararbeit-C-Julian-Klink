TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    attlib.cpp \
    tokenlib.cpp \
    txtlib.cpp

DISTFILES += \
    daten.txt \
    daten.dtd \
    daten.xml \
    daten.dtd \
    daten.xml \
    daten.txt


data.path = $$OUT_PWD/

data.files += $$PWD/*.dat

data.files += $$PWD/*.xml

data.files += $$PWD/*.dtd

data.files += $$PWD/*.txt

INSTALLS += data

HEADERS += \
    att.h \
    class.h \
    token.h

