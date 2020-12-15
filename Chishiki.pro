QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/db/character.cpp \
    src/db/charactertestresult.cpp \
    src/db/database.cpp \
    src/db/path.cpp \
    src/main.cpp \
    src/pdf/documentwriter.cpp \
    src/pdf/pdfcharacterzone.cpp \
    src/pdf/pdflayout.cpp \
    src/ui/about.cpp \
    src/ui/home.cpp \
    src/ui/kanatest.cpp \
    src/ui/mainwindow.cpp

HEADERS += \
    include/db/character.h \
    include/db/charactertestresult.h \
    include/db/database.h \
    include/db/path.h \
    include/etc/characterTranslation.h \
    include/pdf/documentwriter.h \
    include/pdf/pdfcharacterzone.h \
    include/pdf/pdflayout.h \
    include/pdf/pdfsettings.h \
    include/ui/about.h \
    include/ui/home.h \
    include/ui/kanatest.h \
    include/ui/mainwindow.h

FORMS += \
    ui/about.ui \
    ui/home.ui \
    ui/kanatest.ui \
    ui/mainwindow.ui

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
    README.md

RESOURCES += \
    resource/databases.qrc \
    resource/fonts.qrc \
    resource/images.qrc
