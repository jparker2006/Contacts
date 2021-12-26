QT += core gui sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += \
    crypto/qaesencryption.cpp \
    src/deletetags.cpp \
    src/entry.cpp \
    src/contactswindow.cpp \
    crypto/sha3.cpp \
    src/signup.cpp \
    src/login.cpp \
    src/mainwindow.cpp \
    src/main.cpp
HEADERS += \
    include/deletetags.h \
    include/entry.h \
    include/serverdata.h \
    crypto/qaesencryption.h \
    include/contactswindow.h \
    include/mainwindow.h \
    include/login.h \
    include/signup.h \
    crypto/sha3.h
FORMS += \
    ui/deletetags.ui \
    ui/entry.ui \
    ui/contactswindow.ui \
    ui/signup.ui \
    ui/login.ui
RESOURCES += \
    Resources.qrc
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
