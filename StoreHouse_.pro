#-------------------------------------------------
#
# Project created by QtCreator 2012-10-29T19:53:57
#
#-------------------------------------------------

QT       += core gui


INCLUDEPATH +=\mysqllib\include
LIBS +=\mysqllib\lib\libmysql.lib
LIBS +=\mysqllib\lib\mysqlclient.lib
LIBS +=\mysqllib\lib\libmysql.dll

TARGET = StoreHouse_
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbms.cpp \
    conhouse.cpp \
    conshelf.cpp \
    conitem.cpp \
    conbill.cpp \
    storescene.cpp \
    shelfdialog.cpp \
    housedialog.cpp

HEADERS  += mainwindow.h \
    dbms.h \
    storeitem.h \
    storeshelf.h \
    storehouse.h \
    storebill.h \
    conhouse.h \
    conshelf.h \
    conitem.h \
    conbill.h \
    storescene.h \
    shelfdialog.h \
    housedialog.h

FORMS    += mainwindow.ui \
    shelfdialog.ui \
    housedialog.ui
