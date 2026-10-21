QT       += core gui
#QT += doc

#QMAKE_DOCS = $$PWD/Doxyfile
#QMAKE_DOCS_OUTPUTDIR = $$PWD/docs_doxy/html

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    docktitlebar.cpp \
    main.cpp \
    mainwindow.cpp \
    movabledockwidget.cpp \
    utils.cpp

HEADERS += \
    docktitlebar.h \
    main.h \
    mainwindow.h \
    movabledockwidget.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#docs.commands = doxygen $$PWD/Doxyfile
#docs.target = docs
#QMAKE_EXTRA_TARGETS += docs
#PRE_TARGETDEPS += docs

DOXYGEN_CONFIG = $$PWD/Doxyfile
doxygen_docs.target = doxygen_docs
doxygen_docs.commands = doxygen $$DOXYGEN_CONFIG

doxygen_docs.depends = $$DOXYGEN_CONFIG $$HEADERS $$SOURCES

QMAKE_EXTRA_TARGETS += doxygen_docs

QMAKE_POST_LINK += doxygen $$DOXYGEN_CONFIG
