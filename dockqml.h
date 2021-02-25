#ifndef DOCKQML_H
#define DOCKQML_H

#include <QMainWindow>
#include <QDockWidget>
#include "console.h"

class QQuickWidget;
//class Console;

class DockQML : public QDockWidget
{
    Q_OBJECT

public:
    DockQML(const QString &title, QWidget *parent = NULL, Console *console = NULL);
    ~DockQML();
    bool loadFile(QString file);

private:
    QQuickWidget *mainWidget;
};

#endif // DOCKQML_H
