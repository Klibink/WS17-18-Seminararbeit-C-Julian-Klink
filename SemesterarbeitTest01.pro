TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    lib1.cpp \
    tokenlib.cpp \
    attlib.cpp \
    txtlib.cpp

DISTFILES += \
    daten.txt \
    daten.dtd \
    daten.xml
data.path = $$OUT_PWD/

data.files += $$PWD/*.dat

data.files += $$PWD/*.xml

data.files += $$PWD/*.dtd

INSTALLS += data

HEADERS += \
    class.h \
    token.h \
    att.h \
    ausgabe.h
