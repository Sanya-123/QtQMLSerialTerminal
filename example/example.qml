import QtQml 2.2
import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls.Universal 2.0
import QtQuick.Controls.Styles 1.4
/*asdasd*/
//asdasd

Item {
    id: mainIteam
    Universal.theme: Universal.Light
    Universal.accent: Universal.Green
    Universal.foreground: Universal.Indigo

//    Connections {
//        target: terminal
//        onGetData: {}
//        onPutsData: {}
//    }

    ColumnLayout {
        id: columnLayout
        anchors.rightMargin: 4
        anchors.leftMargin: 4
        anchors.bottomMargin: 4
        anchors.topMargin: 4
        anchors.fill: parent
        transformOrigin: Item.Center

        SpinBox {
            id: spinBox
            to: 100
            from: 1
            value: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }

        Repeater {
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            model: spinBox.value
            RowLayout {
                id: rowLayout
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                TextInput {
                    id: textInput
                    //                    width: 200
                    text: qsTr("test")
                    font.pixelSize: 12
                }

                Button {
                    id: button
                    text: qsTr("CMD") + index
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked: terminal.inputTex(textInput.text + '\n')
                }

            }
        }


    }

}
