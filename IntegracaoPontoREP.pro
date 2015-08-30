#-------------------------------------------------
#
# Project created by QtCreator 2015-08-22T14:44:41
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntegracaoPontoREP
TEMPLATE = app


SOURCES += main.cpp\
        sistemalogin.cpp \
    stylesheet.cpp \
    desktophome.cpp \
    relacaofiliais.cpp \
    bancodados.cpp \
    visualizacao.cpp \
    cadastrofilial.cpp \
    cadastroempresa.cpp \
    cadastrocolaborador.cpp \
    relacaocolaboradores.cpp

HEADERS  += sistemalogin.h \
    stylesheet.h \
    desktophome.h \
    relacaofiliais.h \
    bancodados.h \
    visualizacao.h \
    cadastrofilial.h \
    cadastroempresa.h \
    cadastrocolaborador.h \
    relacaocolaboradores.h

FORMS    += sistemalogin.ui \
    desktophome.ui \
    relacaofiliais.ui \
    visualizacao.ui \
    relacaocolaboradores.ui

RESOURCES += \
    img.qrc

DISTFILES += \
    img/icone_pesquisar.png
