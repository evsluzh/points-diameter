TEMPLATE = app
TARGET = convex-hull

CONFIG += QtGui
QT += opengl

OBJECTS_DIR = bin

QMAKE_CXXFLAGS = -std=c++11 -Wall

macx {
    QMAKE_CXXFLAGS += -stdlib=libc++  
    QMAKE_LFLAGS += -lc++
}

CONFIG += precompile_header
PRECOMPILED_HEADER = stdafx.h

DEPENDPATH += src \
              visualization/headers \
              visualization/headers/common \
              visualization/headers/io \
              visualization/headers/visualization \

INCLUDEPATH += src \
               visualization/headers \

HEADERS += src/stdafx.h \
           src/viewer.h \
           src/convex_hull.h \

SOURCES += src/main.cpp \
           src/convex_hull.cpp \ 

LIBS += -Lvisualization -lvisualization
