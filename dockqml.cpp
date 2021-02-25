#include "dockqml.h"
#include <QQuickWidget>
#include <QQmlContext>

DockQML::DockQML(const QString &title, QWidget *parent, Console *console):
    QDockWidget(title, parent)
{
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    mainWidget = new QQuickWidget(this);
    if(console)
        mainWidget->rootContext()->setContextProperty("terminal", console);
    setWidget(mainWidget);
    mainWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
}

DockQML::~DockQML()
{
    delete mainWidget;
}

bool DockQML::loadFile(QString file)
{
    mainWidget->setSource(QUrl::fromUserInput(file));
    return mainWidget->status() != QQuickWidget::Error;
}
