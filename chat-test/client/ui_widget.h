// ui_widget 헤더파일 QTCreator로 자동 생성
#ifndef UI_WIDGET_H
#define UI_WIDGET_H
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
QT_BEGIN_NAMESPACE
class Ui_Widget
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *sendFile;
    QLineEdit *ipLineEdit;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLineEdit *messageLineEdit;
    QPushButton *sendButton;
    QPushButton *connectButton;
    QListWidget *listWidget;
    QLineEdit *portLineEdit;
    QPushButton *openFile;
    QLabel *label_4;
    QLabel *messageFilePath;
    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1200, 1000);
        gridLayoutWidget =new QWidget(Widget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 587, 381));
        gridLayout =new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(10, 10, 10, 10);
        sendFile =new QPushButton(gridLayoutWidget);
        sendFile->setObjectName(QStringLiteral("sendFile"));
        gridLayout->addWidget(sendFile, 6, 0, 1, 2);
        ipLineEdit =new QLineEdit(gridLayoutWidget);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        ipLineEdit->setMinimumSize(QSize(400, 0));
        gridLayout->addWidget(ipLineEdit, 0, 1, 1, 3);
        label =new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        gridLayout->addWidget(label, 0, 0, 1, 1);
        label_3 =new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        gridLayout->addWidget(label_3, 1, 0, 1, 1);
        label_2 =new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        gridLayout->addWidget(label_2, 3, 0, 1, 1);
        messageLineEdit =new QLineEdit(gridLayoutWidget);
        messageLineEdit->setObjectName(QStringLiteral("messageLineEdit"));
        gridLayout->addWidget(messageLineEdit, 3, 1, 1, 2);
        sendButton =new QPushButton(gridLayoutWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        gridLayout->addWidget(sendButton, 3, 3, 1, 1);
        connectButton =new QPushButton(gridLayoutWidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        gridLayout->addWidget(connectButton, 2, 0, 1, 4);
        listWidget =new QListWidget(gridLayoutWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setAutoScroll(false);
        listWidget->setAutoScrollMargin(3);
        listWidget->setDefaultDropAction(Qt::IgnoreAction);
        listWidget->setMovement(QListView::Static);
        gridLayout->addWidget(listWidget, 8, 0, 1, 4);
        portLineEdit =new QLineEdit(gridLayoutWidget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setMinimumSize(QSize(400, 0));
        gridLayout->addWidget(portLineEdit, 1, 1, 1, 3);
        openFile =new QPushButton(gridLayoutWidget);
        openFile->setObjectName(QStringLiteral("openFile"));
        gridLayout->addWidget(openFile, 6, 2, 1, 2);
        label_4 =new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        gridLayout->addWidget(label_4, 4, 0, 1, 1);
        messageFilePath =new QLabel(gridLayoutWidget);
        messageFilePath->setObjectName(QStringLiteral("messageFilePath"));
        gridLayout->addWidget(messageFilePath, 4, 1, 1, 3);
        retranslateUi(Widget);
        QMetaObject::connectSlotsByName(Widget);
    } // setupUi
    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        sendFile->setText(QApplication::translate("Widget", "Send File", 0));
        ipLineEdit->setText(QApplication::translate("Widget", "127.0.0.1", 0));
        label->setText(QApplication::translate("Widget", "IP", 0));
        label_3->setText(QApplication::translate("Widget", "PORT:", 0));
        label_2->setText(QApplication::translate("Widget", "Message:", 0));
        sendButton->setText(QApplication::translate("Widget", "Send Chat", 0));
        connectButton->setText(QApplication::translate("Widget", "Connect", 0));
        openFile->setText(QApplication::translate("Widget", "Open File", 0));
        label_4->setText(QApplication::translate("Widget", "FilePath:", 0));
        messageFilePath->setText(QApplication::translate("Widget", "File is Empty", 0));
    } // retranslateUi
};
namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui
QT_END_NAMESPACE
#endif // UI_WIDGET_H
