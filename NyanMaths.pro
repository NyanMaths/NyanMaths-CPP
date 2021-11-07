CONFIG -= qt
CONFIG += c++20

TEMPLATE = lib

INCLUDEPATH += include


SOURCES += \
    $$files(src/nyanmaths/*.cpp) \
    $$files(src/nyanmaths/shapes/*.cpp) \
    $$files(src/nyanmaths/functions/*.cpp) \

HEADERS += \
    $$files(include/nyanmaths/*.hpp) \
    $$files(include/nyanmaths/shapes/*.hpp) \
    $$files(include/nyanmaths/functions/*.hpp) \


# Default rules for deployment.
unix
{
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
