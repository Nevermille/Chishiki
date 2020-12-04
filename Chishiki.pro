QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/about.cpp \
    src/character.cpp \
    src/charactertestresult.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/about.h \
    include/character.h \
    include/characterTranslation.h \
    include/charactertestresult.h \
    include/mainwindow.h \

FORMS += \
    ui/about.ui \
    ui/mainwindow.ui

TRANSLATIONS += \
    locale/Chishiki_en_US.ts \
    locale/Chishiki_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md

RESOURCES += \
    resource/icons.qrc
