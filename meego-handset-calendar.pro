### eqmake4 was here ###
CONFIG -= debug_and_release debug
CONFIG += release

include(common/common.pri)
TEMPLATE = subdirs
SUBDIRS += src translations

# Desktop
desktop.files = share/applications/meego-handset-calendar.desktop
desktop.path = /usr/share/applications

INSTALLS += desktop
