TEMPLATE = app
TARGET = points-diameter

CONFIG += QtGui
QT += opengl

OBJECTS_DIR = bin

QMAKE_CXXFLAGS = -std=c++11 -Wall

macx {
    QMAKE_CXXFLAGS += -stdlib=libc++  
    QMAKE_LFLAGS += -lc++
}

CONFIG += precompile_header
PRECOMPILED_HEADER = src/stdafx.h

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
    src/points_diameter.h

SOURCES += src/main.cpp \
           src/convex_hull.cpp \ 
    src/points_diameter.cpp

LIBS += -Lvisualization -lvisualization
