QT += widgets core gui

SOURCES += main.cpp blurpicker.cpp blureffect.cpp \
    imageitem.cpp \
    item.cpp
HEADERS += blurpicker.h blureffect.h \
    imageitem.h \
    item.h
RESOURCES += blurpicker.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/effects/blurpicker
INSTALLS += target
