QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

HEADERS        = mainwindow.h \
    seg2file.h \
    seg2stosegys.h \
    segyfile.h \
    datainput_preeditdialog.h \
    datainput_datainputdialog.h \
    qcustomplot.h \
    seismicplotwidget.h \
    tetsp.h \
    seismicdata.h

SOURCES        = main.cpp \
                 mainwindow.cpp \
    seg2file.cpp \
    seg2stosegys.cpp \
    segyfile.cpp \
    datainput_preeditdialog.cpp \
    datainput_datainputdialog.cpp \
    qcustomplot.cpp \
    seismicplotwidget.cpp \
    seismicdata.cpp

RESOURCES     = RibbonSystemMenu.qrc



macx {
    CONFIG-=app_bundle
}

qtHaveModule(printsupport): QT += printsupport

FORMS += \
    datainput_preeditdialog.ui \
    datainput_datainputdialog.ui
