
QT      += qml quick
QT      -= gui

TARGET   = tst_itemstest
CONFIG  += console qmltestcase
CONFIG  -= app_bundle

TEMPLATE = app

DESTDIR  = $$PWD/../../bin

SOURCES += tst_itemstest.cpp

OTHER_FILES += \
    cases/tst_ActionNode.qml

DISTFILES += \
    cases/tst_Blackboard.qml
