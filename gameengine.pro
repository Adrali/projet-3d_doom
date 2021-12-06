QT       += core gui widgets
TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    boundingbox.cpp \
    camera.cpp \
    gameobject.cpp \
    player.cpp \
    transformation.cpp \
    triangle.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    boundingbox.h \
    camera.h \
    gameobject.h \
    mainwidget.h \
    geometryengine.h \
    player.h \
    transformation.h \
    triangle.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES += \
    ../sound/fire.wav \
    map.txt
