TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        drawingsystem.cpp \
        gamefield.cpp \
        main.cpp \
        tetramino.cpp \
        tile.cpp

LIBS += -L$$PWD/SFML/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/SFML/include
DEPENDPATH += $$PWD/SFML/include

HEADERS += \
    drawingsystem.h \
    gamefield.h \
    tetramino.h \
    tile.h
