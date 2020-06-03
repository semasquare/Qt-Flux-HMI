TEMPLATE = app
TARGET = automotive
QT += quick quickcontrols2

HEADERS += \
    src/actions/actiontypes.h \
    src/actions/caractions.h \
    src/middlewares/carmiddleware.h \
    src/services/carservice.h \
    src/store/carstore.h

SOURCES += \
    src/main.cpp \
    src/actions/caractions.cpp \
    src/middlewares/carmiddleware.cpp \
    src/services/carservice.cpp \
    src/store/carstore.cpp

RESOURCES += \
    icons/icons.qrc \
    imagine-assets/imagine-assets.qrc \
    qml/qml.qrc \
    qtquickcontrols2.conf

INCLUDEPATH += $$PWD/src

include(src/flux_qt/flux_qt.pri)

target.path = $$[QT_INSTALL_EXAMPLES]/quickcontrols2/imagine/automotive
INSTALLS += target
