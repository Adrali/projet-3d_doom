QT       += core gui widgets multimedia
TARGET = gameengine
TEMPLATE = app

SOURCES += main.cpp \
    boundingbox.cpp \
    camera.cpp \
    ennemy.cpp \
    entity.cpp \
    gameobject.cpp \
    loot.cpp \
    player.cpp \
    transformation.cpp \
    triangle.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    boundingbox.h \
    camera.h \
    const_entity.h \
    ennemy.h \
    entity.h \
    file3D.h \
    gameTime.h \
    gameobject.h \
    loot.h \
    mainwidget.h \
    geometryengine.h \
    player.h \
    transformation.h \
    triangle.h

RESOURCES += \
    maps.qrc \
    obj.qrc \
    shaders.qrc \
    sounds.qrc \
    textures.qrc

# install
target.path = $$[YOUR_PATH]
INSTALLS += target

DISTFILES += \
    FirstStage.obj
