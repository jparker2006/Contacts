QT += core gui sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += \
    src/login.cpp \
    src/mainwindow.cpp \
    main.cpp
HEADERS += \
    include/mainwindow.h \
    include/login.h
FORMS += \
    ui/login.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
