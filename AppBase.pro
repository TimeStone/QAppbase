QT += widgets
requires(qtConfig(filedialog))

INCLUDEPATH += $$PWD/..

HEADERS       = mainwindow.h \
    console/cli/logger/apploghandler.h \
                gui/mdi/mdichild.h \
    gui/basic/basicform.h \
    config/appconfig.h \
    core/global.h \
    core/appbase.h \
    gui/historytree/historytree.h
SOURCES       = main.cpp \
    console/cli/logger/apploghandler.cpp \
                mainwindow.cpp \
                gui/mdi/mdichild.cpp \
    gui/basic/basicform.cpp \
    config/appconfig.cpp \
    core/appbase.cpp \
    gui/historytree/historytree.cpp
RESOURCES     = AppBase.qrc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/mdi
#INSTALLS += target

FORMS += \
    gui/basic/basicform.ui \
    gui/historytree/historytree.ui

win32: {
    LIBS += -lversion
#    !debug: {
#        THE_FILE = $$PWD/qt.conf
#        THE_DEST = $${DESTDIR}
#        THE_FILE ~= s,/,\\,g
#        THE_DEST ~= s,/,\\,g
#        QMAKE_POST_LINK += "$$QMAKE_COPY $$THE_FILE $$THE_DEST $$escape_expand(\\n\\t);"
#    }
}
