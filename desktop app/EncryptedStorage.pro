QT += core gui sql network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11
SOURCES += \
    main/src/home.cpp \
    main/crypto/qaesencryption.cpp \
    contacts/src/deletetags.cpp \
    contacts/src/entry.cpp \
    contacts/src/contactswindow.cpp \
    main/crypto/sha3.cpp \
    account/src/signup.cpp \
    account/src/login.cpp \
    main/src/mainwindow.cpp \
    animations/point3.cpp \
    animations/part.cpp \
    animations/particle.cpp \
    animations/firework.cpp \
    main/src/main.cpp
HEADERS += \
    contacts/include/deletetags.h \
    contacts/include/entry.h \
    main/include/home.h \
    main/include/serverdata.h \
    main/crypto/qaesencryption.h \
    contacts/include/contactswindow.h \
    main/include/mainwindow.h \
    account/include/login.h \
    account/include/signup.h \
    main/crypto/sha3.h \
    animations/point3.h \
    animations/particle.h \
    animations/firework.h \
    animations/part.h
FORMS += \
    contacts/ui/deletetags.ui \
    contacts/ui/entry.ui \
    contacts/ui/contactswindow.ui \
    account/ui/signup.ui \
    account/ui/login.ui \
    main/ui/home.ui
RESOURCES += \
    Resources.qrc
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
