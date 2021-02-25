/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "console.h"
#include "settingsdialog.h"
#include "syntaxhighlighter/syntaxhighlighter.h"
#include "dockqml.h"

#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>

#include <QDebug>

//! [0]
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//! [0]
    ui->setupUi(this);
    console = new Console;
    console->setEnabled(false);
    setCentralWidget(console);

    readeText = new SyntaxHighlighter;
//! [1]
    serial = new QSerialPort(this);
//! [1]
    settings = new SettingsDialog;

    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionQuit->setEnabled(true);
    ui->actionConfigure->setEnabled(true);

    status = new QLabel;
    ui->statusBar->addWidget(status);

    initActionsConnections();

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);

//! [2]
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
//! [2]
    connect(console, &Console::getData, this, &MainWindow::writeData);
//! [3]
    oldDirectory = QApplication::applicationDirPath();
}
//! [3]

MainWindow::~MainWindow()
{
    for(int i = 0; i < listDockQML.size(); i++)
        delete listDockQML.at(i);
    delete readeText;
    delete console;
    delete settings;
    delete ui;
}

//! [4]
void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        showStatusMessage(tr("Open error"));
    }
}
//! [4]

//! [5]
void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}
//! [5]

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Simple Terminal"),
                       tr("The <b>Simple Terminal</b> example demonstrates how to "
                          "use the Qt Serial Port module in modern GUI applications "
                          "using Qt, with a menu bar, toolbars, and a status bar."));
}

//! [6]
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
//! [6]

//! [7]
void MainWindow::readData()
{
    QByteArray data = serial->readAll();
    console->putText(data);
}
//! [7]

//! [8]
void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::loadQML()
{
    QStringList fileName = QFileDialog::getOpenFileNames(this, tr("Script"), oldDirectory,  tr("Image Files (*.qml)"));
    if(fileName.isEmpty())//если файла не существует
        return;

    oldDirectory = QString(fileName.at(0)).remove(fileName.at(0).lastIndexOf(QRegExp("[\\/]")), QString(fileName.at(0)).size());
    for(int i = 0; i < fileName.size(); i++)
    {
        QString name = QString(fileName.at(i)).remove(0, QString(fileName.at(i)).lastIndexOf(QRegExp("[\\/]")) + 1);

        //создаю новый виджет
        listDockQML.append(new DockQML(name, this, console));
        addDockWidget(Qt::LeftDockWidgetArea, listDockQML.at(listDockQML.size() - 1));
        listDockQML.at(listDockQML.size() - 1)->loadFile(fileName.at(i));
        ui->menuScript->addAction(listDockQML.at(listDockQML.size() - 1)->toggleViewAction());
        connect(ui->menuRemoveScript->addAction(name), SIGNAL(triggered(bool)), this, SLOT(remodeDock(bool)));
    }
}

void MainWindow::remodeDock(bool ok)
{
    Q_UNUSED(ok);
    QAction *dock = (QAction*)sender();
    QList<QAction *> actionsDockDelete = ui->menuRemoveScript->actions();
    for(int i = 0; i < actionsDockDelete.size(); i++)
    {
        if(actionsDockDelete.at(i) == dock)
        {
            removeDockWidget(listDockQML.at(i));
            if(listDockQML.at(i))
                delete listDockQML.at(i);
            listDockQML.removeAt(i);
            disconnect(dock, SIGNAL(triggered(bool)), this, SLOT(remodeDock(bool)));
            ui->menuRemoveScript->removeAction(dock);
            break;
        }
    }
}

void MainWindow::openFonConfigure()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, console->font(), this);
    if (ok)
    {
        console->setFont(font);
    }
}

void MainWindow::openColorFonTerminal()
{
    QColor c = QColorDialog::getColor(console->palette().color(QPalette::Base), this, "Fon color");
    QPalette p = console->palette();
    if(c.isValid())
       p.setColor(QPalette::Base, c);
    console->setPalette(p);
}

void MainWindow::openColorTextTerminal()
{
    QColor c = QColorDialog::getColor(console->palette().color(QPalette::Text), this, "Text color");
    QPalette p = console->palette();
    if(c.isValid())
       p.setColor(QPalette::Text, c);
    console->setPalette(p);
}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionConfigure, &QAction::triggered, settings, &MainWindow::show);
    connect(ui->actionClear, &QAction::triggered, console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionOpenScript, &QAction::triggered, readeText, &SyntaxHighlighter::show);
    connect(ui->actionLoadScript, &QAction::triggered, this, &MainWindow::loadQML);
    connect(ui->actionConfigure_terminal, &QAction::triggered, this, &MainWindow::openFonConfigure);
    connect(ui->actionConfigure_terminalBaseColor, &QAction::triggered, this, &MainWindow::openColorFonTerminal);
    connect(ui->actionConfigure_terminalTextColor, &QAction::triggered, this, &MainWindow::openColorTextTerminal);
}

void MainWindow::showStatusMessage(const QString &message)
{
    status->setText(message);
}
