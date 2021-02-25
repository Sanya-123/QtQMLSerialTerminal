QT       += widgets serialport
QT       += quickwidgets qml quick quickcontrols2

TARGET = MyTerminal
TEMPLATE = app

include(./syntaxhighlighter/syntaxhighlighter.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    console.cpp \
    dockqml.cpp \
    comportcombobox.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    console.h \
    dockqml.h \
    comportcombobox.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc

#target.path = $$[QT_INSTALL_EXAMPLES]/serialport/terminal
#INSTALLS += target
