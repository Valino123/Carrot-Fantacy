QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    block.cpp \
    bullet.cpp \
    drawlist.cpp \
    enemy.cpp \
    main.cpp \
    mainwindow.cpp \
    startfrom.cpp \
    tower.cpp \
    wave.cpp

HEADERS += \
    Utility.h \
    block.h \
    bullet.h \
    drawlist.h \
    enemy.h \
    mainwindow.h \
    startfrom.h \
    tower.h \
    wave.h

FORMS += \
    mainwindow.ui \
    startfrom.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    pics/BG.PNG \
    pics/Road.PNG \
    pics/t1-1.PNG \
    pics/t1-2.PNG \
    pics/t1-3.PNG \
    pics/t2-1.PNG \
    pics/t2-2.PNG \
    pics/tower1_BG.PNG
