QT       += core gui widgets
TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    gameobject.cpp \
    transformation.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    gameobject.h \
    mainwidget.h \
    geometryengine.h \
    transformation.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES += \
    ../sound/fire.wav \
    map.txt
