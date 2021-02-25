
HEADERS         = $$PWD/highlighter.h \
                  $$PWD/syntaxhighlighter.h
SOURCES         = $$PWD/highlighter.cpp \
                  $$PWD/syntaxhighlighter.cpp


wince {
   addFiles.files = main.cpp mainwindow.cpp
   addFiles.path = .
   INSTALLS += addFiles
}

RESOURCES += \
    $$PWD/dockwidgets.qrc
