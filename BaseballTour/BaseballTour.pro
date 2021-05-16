QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addsouvenir.cpp \
    csvparser.cpp \
    databasenameview.cpp \
    admin.cpp \
    databaseviewform.cpp \
    dbmanager.cpp \
    graph.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    purchasesouvenirs.cpp \
    tripplanner.cpp

HEADERS += \
    addsouvenir.h \
    csvparser.h \
    databasenameview.h \
    admin.h \
    databaseviewform.h \
    dbmanager.h \
    graph.h \
    logindialog.h \
    mainwindow.h \
    purchasesouvenirs.h \
    tripplanner.h

FORMS += \
    addsouvenir.ui \
    databasenameview.ui \
    admin.ui \
    databaseviewform.ui \
    logindialog.ui \
    mainwindow.ui \
    purchasesouvenirs.ui \
    tripplanner.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
