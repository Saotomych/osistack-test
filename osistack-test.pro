#-------------------------------------------------
#
# Project created by QtCreator 2016-02-29T17:18:24
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

CONFIG   += console
CONFIG 	 += c++11
CONFIG   -= app_bundle
CONFIG   += static

TEMPLATE = app

DESTDIR = bin
VERSION = 0.0.0.0

INCLUDEPATH += ../ositransport
INCLUDEPATH += $(JENKINS_HOME)/jobs/ositransport/workspace
INCLUDEPATH += ../ASN1/include
INCLUDEPATH += $(JENKINS_HOME)/jobs/ASN1/workspace/include
INCLUDEPATH += ../ASN1
INCLUDEPATH += $(JENKINS_HOME)/jobs/ASN1/workspace
INCLUDEPATH += ../osistack/include
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include
INCLUDEPATH += ../osistack/include/acse-asn1
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include/acse-asn1
INCLUDEPATH += ../osistack/include/presentation-asn1
INCLUDEPATH += $(JENKINS_HOME)/jobs/osistack/workspace/include/presentation-asn1

SOURCES += osistack-test.cpp

HEADERS += osistack-test.h 

unix{
	CONFIG (debug, debug|release){
	    OBJECTS_DIR = build/debug
		LIBS += -L../osistack/bin -L$(JENKINS_HOME)/jobs/osistack/workspace/bin
		LIBS += -L../ASN1/bin -L$(JENKINS_HOME)/jobs/ASN1/workspace/bin 
		LIBS += -L../ositransport/bin -L$(JENKINS_HOME)/jobs/ositransport/workspace/bin 
        LIBS += -lcppunit -lgcov -losistackd
		DEFINES += DEBUG
		TARGET = osistack-testd
		
		QMAKE_CXXFLAGS_RELEASE -= -O
		QMAKE_CXXFLAGS_RELEASE -= -O1
		QMAKE_CXXFLAGS_RELEASE -= -O2
		QMAKE_CXXFLAGS += -O0 -fprofile-arcs -ftest-coverage -fPIC
			
	} else {
	    OBJECTS_DIR = build/release
		LIBS += -L../osistack/bin -L$(JENKINS_HOME)/jobs/osistack/workspace/bin
		LIBS += -L../ASN1/bin -L$(JENKINS_HOME)/jobs/ASN1/workspace/bin 
		LIBS += -L../ositransport/bin -L$(JENKINS_HOME)/jobs/ositransport/workspace/bin 
        LIBS += -lcppunit -losistack
		TARGET = osistack-test
		
		QMAKE_CXXFLAGS_RELEASE += -fPIC
	}
}else{
    TARGET = osistack-test-notunix
}

CONFIG += debug_and_release build_all
