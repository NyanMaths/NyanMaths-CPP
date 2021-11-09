TARGET = nyanmaths
# Classic versioning : major.minor.patch
VERSION = 0.1.0


TEMPLATE = lib

CONFIG -= qt
CONFIG += c++20

INCLUDEPATH += include

SOURCES += \
    $$files(src/nyanmaths/*.cpp) \
    $$files(src/nyanmaths/shapes/*.cpp) \
    $$files(src/nyanmaths/functions/*.cpp) \

HEADERS += \
    $$files(include/nyanmaths/*.hpp) \
    $$files(include/nyanmaths/shapes/*.hpp) \
    $$files(include/nyanmaths/functions/*.hpp) \
