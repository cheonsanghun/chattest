#include "widget.h"
#include "ui_widget.h"
#include <QRegExp>
#include <QTcpSocket>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);
    setWindowTitle("HOKAO TALK");
}
Widget::~Widget()
{
    delete ui;
    delete socket;
}
// 포트 연결 준비
void Widget::readyRead()
{
    while(socket->canReadLine())
    {
        QString line=QString::fromUtf8(socket->readLine());
        line=line.left(line.length()-1);
        ui->listWidget->addItem(QString("%2").arg(line));
    }
    ui->listWidget->scrollToBottom();
}

// 연결 시도
void Widget::connected()
{
    socket->write(QString("/me:"+ui->messageLineEdit->text()+"\n").toUtf8());  // 연결 시도
}
void Widget::on_connectButton_clicked()
{
    socket=new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    socket->connectToHost(ui->ipLineEdit->text(),ui->portLineEdit->text().toInt());
}

// 보내기 버튼 콜백 메소드
void Widget::on_sendButton_clicked()
{
    QString message=ui->messageLineEdit->text().trimmed(); // 글자를 가져온다.
    if(!message.isEmpty()) // 메시지가 빈게 아니라면
    {
        socket->write(QString(message+"\n").toUtf8());
        // utf8 인코딩 타입으로 변환하여 소켓 전송
    }
    ui->messageLineEdit->clear();  // 전송 창 초기화
    ui->messageLineEdit->setFocus(); // 포커스 두기
}
void Widget::on_messageLineEdit_returnPressed()
{
    on_sendButton_clicked();
}

// 전송할 파일 열기
void Widget::on_openFile_clicked()
{
    fileName = QFileDialog::getOpenFileName(this); // 전송할 파일의 경로 저장
    ui->messageFilePath->setText(fileName); // 경로를 ui에 출력
}
void Widget::on_sendFile_clicked()
{
}
