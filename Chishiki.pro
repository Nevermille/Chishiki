QT       += core gui svg sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/db/character.cpp \
    src/db/charset.cpp \
    src/db/databasemanager.cpp \
    src/db/databaseupdater.cpp \
    src/etc/path.cpp \
    src/main.cpp \
    src/ui/about.cpp \
    src/ui/characterchooser.cpp \
    src/ui/home.cpp \
    src/ui/kanatest.cpp \
    src/ui/kanjitest.cpp \
    src/ui/library.cpp \
    src/ui/mainwindow.cpp \
    src/widget/kanjiselector.cpp \
    src/widget/kanjiviewer.cpp

HEADERS += \
    include/db/character.h \
    include/db/charset.h \
    include/db/databasemanager.h \
    include/db/databaseupdater.h \
    include/etc/characterTranslation.h \
    include/etc/chishiki.h \
    include/etc/path.h \
    include/ui/about.h \
    include/ui/characterchooser.h \
    include/ui/home.h \
    include/ui/kanatest.h \
    include/ui/kanjitest.h \
    include/ui/library.h \
    include/ui/mainwindow.h \
    include/widget/kanjiselector.h \
    include/widget/kanjiviewer.h

FORMS += \
    ui/about.ui \
    ui/characterchooser.ui \
    ui/home.ui \
    ui/kanatest.ui \
    ui/kanjitest.ui \
    ui/library.ui \
    ui/mainwindow.ui \
    widget/kanjiselector.ui \
    widget/kanjiviewer.ui

TRANSLATIONS += \
    locale/Chishiki_en_US.ts \
    locale/Chishiki_fr_FR.ts

RC_ICONS = resource/images/app/Chishiki.ico
ICON = resource/images/app/Chishiki.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    LICENSE \
    README.md \
    resource/style/light.qss

RESOURCES += \
    resource/chishiki.qrc
