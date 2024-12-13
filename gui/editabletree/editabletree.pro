QT += widgets
requires(qtConfig(treeview))

INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../3rd

FORMS       =  \
               mainwindow.ui \
               treeview.ui \
               addnodedlg.ui

HEADERS     = \
             ../../3rd/jsonc/printbuf.h \
             ../../3rd/jsonc/linkhash.h \
             ../../3rd/jsonc/jsoncxx.h \
                ../../3rd/jsonc/json_util.h \
                ../../3rd/jsonc/json_tokener.h \
                ../../3rd/jsonc/json_object_private.h \
                ../../3rd/jsonc/json_object.h \
                ../../3rd/jsonc/json.h \
                ../../3rd/jsonc/debug.h \
                ../../3rd/jsonc/bits.h \
                ../../3rd/jsonc/arraylist.h \
                ../../3rd/jsonc/config.h \
              jsontreeitem.h \
              jsontreemodel.h \
    mainwindow.h \
              treeitem.h \
              treemodel.h \
              JSHighlighter.h \
              addnodedlg.h \
              treeview.h

RESOURCES   = editabletreemodel.qrc
SOURCES     = \
                ../../3rd/jsonc/printbuf.c \
                ../../3rd/jsonc/linkhash.c \
                ../../3rd/jsonc/jsoncxx.cpp \
                ../../3rd/jsonc/json_util.c \
                ../../3rd/jsonc/json_tokener.c \
                ../../3rd/jsonc/json_object.c \
                ../../3rd/jsonc/debug.c \
                ../../3rd/jsonc/arraylist.c \
              jsontreeitem.cpp \
              jsontreemodel.cpp \
               mainwindow.cpp \
              treeitem.cpp \
              treemodel.cpp \
              main.cpp \
              addnodedlg.cpp \
              treeview.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/editabletreemodel
INSTALLS += target
