QT       += core gui widgets

TARGET = QTesseractOpenGL
TEMPLATE = app

SOURCES += main.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp \
    backend.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    matrices.h \
    backend.h

RESOURCES += \
    shaders.qrc

LIBS += -lopengl32 -lglu32
# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target
