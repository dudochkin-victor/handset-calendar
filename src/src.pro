### eqmake4 was here ###
CONFIG -= debug_and_release debug
CONFIG += release

include(../common/common.pri)
# -------------------------------------------------
# Project created by QtCreator 2010-06-24T09:38:52
# -------------------------------------------------
TEMPLATE = app
CONFIG += meegotouch
QT += testlib
target.path = /usr/bin
TARGET = meego-handset-calendar
MOC_DIR = .moc
OBJECTS_DIR = .obj
MGEN_OUTDIR = .gen


# Input
SOURCES += main.cpp \
    mmonthview.cpp \
    mcomingupview.cpp \
    mthreedayview.cpp \
    mviewmanager.cpp \
    comingupviewitemcreator.cpp \
    comingupviewitemmodel.cpp \
    threedayviewitemcreator.cpp \
    threedayviewitemmodel.cpp \
    mdetaildialog.cpp \
    calendarevent.cpp \
    calendardata.cpp \
    mcalendarlayout.cpp \
    mcalendaritem.cpp \
    mcreatenewdialog.cpp \
    calengine.cpp
HEADERS += mmonthview.h \
    mcomingupview.h \
    mthreedayview.h \
    mviewmanager.h \
    comingupviewitemcreator.h \
    comingupviewitemmodel.h \
    calendarevent.h \
    calendardata.h \
    mcalendarlayout.h \
    mcalendaritem.h \
    threedayviewitemcreator.h \
    threedayviewitemmodel.h \
    mdetaildialog.h \
    calendarevent.h \
    calendardata.h \
    mcalendarlayout.h \
    mcalendaritem.h \
    mcreatenewdialog.h \
    calengine.h

INCLUDEPATH +=  /usr/include/meegotouch \
                /usr/include/kcalcoren \
                /usr/include/mkcal

LIBS += -L/usr/lib/
LIBS += -L/usr/lib/ -lkcalcoren
LIBS += -L/usr/lib/ -lmkcal
#RESOURCES += CalRes.qrc

MAKE_CLEAN += $$OBJECTS_DIR/*.o
MAKE_DISTCLEAN += $$MOC_DIR/* \
    $$MOC_DIR \
    $$OBJECTS_DIR/* \
    $$OBJECTS_DIR \
    $$MGEN_OUTDIR/* \
    $$MGEN_OUTDIR

INSTALLS += target
