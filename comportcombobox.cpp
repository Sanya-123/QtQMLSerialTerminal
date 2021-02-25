#include "comportcombobox.h"
#include <QDebug>
#include <QSerialPortInfo>

ComPortComboBox::ComPortComboBox(QWidget *parent) : QComboBox(parent)
{
    addData();
}

ComPortComboBox::~ComPortComboBox()
{

}

void ComPortComboBox::mousePressEvent(QMouseEvent *e)
{
    QString oldCurrentIndexMaster;
    //если был выбран какойто индекс чтобы он остался
    if(currentIndex() > 0)
        oldCurrentIndexMaster = currentText();

    clear();
    addData();


    //выставляю индекс обратно
    setCurrentText(oldCurrentIndexMaster);
    return QComboBox::mousePressEvent(e);
}

void ComPortComboBox::addData()
{
    static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");
    QString description;
    QString manufacturer;
    QString serialNumber;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())//цикл поиска всех портов
    {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);
        addItem(list.first(), list);//добаления
    }
    addItem(tr("Custom"));//add custom input
}
