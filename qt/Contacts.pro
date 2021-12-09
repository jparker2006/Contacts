QT += core gui sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += \
    src/signup.cpp \
    src/login.cpp \
    src/mainwindow.cpp \
    src/main.cpp
HEADERS += \
    include/mainwindow.h \
    include/login.h \
    include/signup.h
FORMS += \
    ui/signup.ui \
    ui/login.ui
RESOURCES += \
    Resources.qrc
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
