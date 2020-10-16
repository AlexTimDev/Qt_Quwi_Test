QT += core gui widgets network
TEMPLATE = app
CONFIG += c++11
SOURCES = \
    app.cpp \
    logindlg.cpp \
    main.cpp \
    mainwnd.cpp \
    projectinfodlg.cpp \
    projectitemwdt.cpp \
    projectswdt.cpp \
    projuseritemwdt.cpp \
    serverapi.cpp
HEADERS = \
    app.h \
    logindlg.h \
    mainwnd.h \
    projectinfodlg.h \
    projectitemwdt.h \
    projectswdt.h \
    projuseritemwdt.h \
    serverapi.h
LIBS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a
INCLUDEPATH += $$top_srcdir/components/
TARGET = examples-exe
PRE_TARGETDEPS += $$top_builddir/components/$(OBJECTS_DIR)/libcomponents.a

RESOURCES += \
    test.qrc

FORMS += \
    logindlg.ui \
    mainwnd.ui \
    projectinfodlg.ui \
    projectitemwdt.ui \
    projectswdt.ui \
    projuseritemwdt.ui
