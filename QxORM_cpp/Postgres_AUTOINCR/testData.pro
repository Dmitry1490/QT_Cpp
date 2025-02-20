include(../../QxOrm.pri)


TEMPLATE = app
DEFINES += _BUILDING_QX_BLOG
INCLUDEPATH += ../../../QxOrm/include/
DESTDIR = ../../../QxOrm/test/_bin/
LIBS += -L"../../../QxOrm/lib"

!contains(DEFINES, _QX_NO_PRECOMPILED_HEADER) {
PRECOMPILED_HEADER = ./include/precompiled.h
} # !contains(DEFINES, _QX_NO_PRECOMPILED_HEADER)

macx:CONFIG-=app_bundle

CONFIG(debug, debug|release) {
TARGET = qxBlogd
LIBS += -l"QxOrmd"
} else {
TARGET = qxBlog
LIBS += -l"QxOrm"
} # CONFIG(debug, debug|release)


QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    author.cpp \
    blog.cpp \
    category.cpp \
    comment.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    author.h \
    category.h \
    comment.h \
    include/export.h \
    include/precompiled.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
