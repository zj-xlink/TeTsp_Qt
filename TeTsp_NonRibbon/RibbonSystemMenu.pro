TEMPLATE = app

QTITANDIR = $$quote($$(QTITANDIR))

isEmpty(QTITANDIR):QTITANDIR = $$quote($$PWD/../../../)

include($$QTITANDIR/src/shared/qtitanribbon.pri)

DESTDIR = $$QTITANDIR/bin
DESTDIR = $$member(DESTDIR, 0)$$QTITAN_LIB_PREFIX
DESTDIR = "$$DESTDIR"

!debug_and_release|build_pass {
    CONFIG(debug, debug|release) {
        TARGET = $$member(TARGET, 0)d
    }
}

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

include($$PWD/aboutdialog.pri)

macx {
    CONFIG-=app_bundle
}

!lessThan(QT_VER_MAJ, 5) {
  QT += printsupport
}

FORMS += \
    datainput_preeditdialog.ui \
    datainput_datainputdialog.ui
