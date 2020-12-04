#-------------------------------------------------
#
# Project created by QtCreator 2019-11-20T16:45:09
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Phase6
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        phase6_gui.cpp \
    Vocabulary.cpp \
    Word.cpp \
    dialog_edit.cpp \
    dialog_overview.cpp \
    wordgroupbox.cpp \
    dialog_add.cpp

HEADERS += \
        phase6_gui.h \
    Vocabulary.h \
    Word.h \
    dialog_edit.h \
    dialog_overview.h \
    wordgroupbox.h \
    dialog_add.h

FORMS += \
        phase6_gui.ui \
    dialog_app.ui \
    dialog_edit.ui \
    dialog_overview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
