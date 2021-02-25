import QtQml 2.2
import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Universal 2.0
import QtQuick.Controls.Styles 1.4

Item {
//    width: 640
//    height: 500
    focus: true



    ColumnLayout {
        anchors.rightMargin: 6
        anchors.leftMargin: 6
        anchors.bottomMargin: 6
        anchors.topMargin: 6
        anchors.fill: parent

        GroupBox {
            id: groupBox
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.preferredHeight: 230
//            Layout.preferredWidth: 370
            enabled: true
            title: qsTr("Tx")
            focus: true


            ColumnLayout {
                anchors.fill: parent

                RowLayout {
                    id: rowLayout
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    transformOrigin: Item.Center
//                    Layout.preferredHeight: 55
//                    Layout.preferredWidth: 335

                    SpinBox {
                        id: spinBox_TxFreq
                        value: slider_TxFreq.value
                        from: 60000
                        to: 6000000
                        stepSize: 1000
                        Layout.fillWidth: false
                        Layout.fillHeight: false
                    }

                    Text {
                        id: text1
//                        width: 70
//                        height: 40
                        text: qsTr("kHz")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.pixelSize: 15
                    }

                    Button {
                        id: button_appleTxFreq
                        text: qsTr("Apply")
                    }

                    Item {
                        id: item1
//                        width: 200
//                        height: 200
                        Layout.fillHeight: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.fillWidth: true
                    }
                }

                Slider {
                    id: slider_TxFreq
                    value: spinBox_TxFreq.value
                    Layout.fillWidth: true
                    Layout.fillHeight: true
//                    Layout.preferredHeight: 40
//                    Layout.preferredWidth: 322
                    from: 60000
                    to: 6000000
                    stepSize: 1000

                }

                RowLayout {
                    id: rowLayout1
                    Layout.fillWidth: true
                    Layout.fillHeight: true
//                    Layout.preferredHeight: 47
//                    Layout.preferredWidth: 352

                    Text {
                        id: text3
//                        width: 112
//                        height: 40
                        text: qsTr("Tx1 Attenuator")
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    SpinBox {
                        id: spinBox_attenuatorTx1
                    }

                    Item {
                        id: item2
//                        width: 200
//                        height: 200
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        id: text4
                        text: qsTr("Tx2 Attenuator")
//                        Layout.preferredHeight: 40
//                        Layout.preferredWidth: 112
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    SpinBox {
                        id: spinBox_attenuatorTx2
                    }

                    Item {
                        id: item3
//                        width: 200
//                        height: 200
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }
            }
        }

        GroupBox {
            id: groupBox1
            Layout.fillWidth: true
            Layout.fillHeight: true
//            Layout.preferredHeight: 149
//            Layout.preferredWidth: 370
            enabled: true
            title: qsTr("Rx")
            focus: true



            ColumnLayout {
                anchors.fill: parent

                RowLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    SpinBox {
                        id: spinBox_RxFreq
                        value: slider_RxFreq.value
                        from: 60000
                        to: 6000000
                        stepSize: 1000
                    }

                    Text {
                        id: text2
                        text: qsTr("kHz")
//                        Layout.preferredHeight: 40
//                        Layout.preferredWidth: 70
                        font.pixelSize: 15
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }

                    Button {
                        id: button_appleRxFreq
                        text: qsTr("Apply")
                    }

                    Item {
                        id: item4
//                        width: 200
//                        height: 200
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }
                }

                Slider {
                    id: slider_RxFreq
                    Layout.fillWidth: true
                    Layout.fillHeight: true
//                    Layout.preferredHeight: 40
//                    Layout.preferredWidth: 322
                    value: spinBox_RxFreq.value
                    from: 60000
                    to: 6000000
                    stepSize: 1000
                }
            }
        }

        Button {
            id: button_init
            text: qsTr("Init")
            Layout.fillWidth: true
            Layout.fillHeight: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Item {
            id: item5
//            width: 200
//            height: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

}
