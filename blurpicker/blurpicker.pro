QT += widgets core gui

SOURCES += main.cpp blurpicker.cpp blureffect.cpp \
    imageitem.cpp
HEADERS += blurpicker.h blureffect.h \
    imageitem.h
RESOURCES += blurpicker.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/effects/blurpicker
INSTALLS += target
