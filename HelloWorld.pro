QT += core gui network widgets
CONFIG += c++11

TARGET = OdooPOS
TEMPLATE = app

SOURCES += main.cpp \
           productcard.cpp

HEADERS += productcard.h

INCLUDEPATH += /opt/homebrew/opt/qt/include
LIBS += -F/opt/homebrew/opt/qt/lib -framework QtCore -framework QtGui -framework QtWidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
