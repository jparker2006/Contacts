QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += \
    src/login.cpp \
    src/mainwindow.cpp \
    main.cpp \
    SHA256/src/SHA256.cpp
HEADERS += \
    include/mainwindow.h \
    include/login.h \
    SHA256/include/SHA256.h
FORMS += \
    ui/login.ui
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
