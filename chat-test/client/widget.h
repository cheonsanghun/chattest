#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QtNetwork>
#include <QDialog>
#include <QFileDialog>
namespace Ui {
class Widget;
}
class QTcpSocket;
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent =0);
    ~Widget();
private slots:
    void readyRead(); //서버로부터 메시지가 온경우
    void connected(); //연결이 완료되었으면 서버에게 연결되었다고 알림
    void on_connectButton_clicked(); //연결 버튼을 누름
    void on_sendButton_clicked(); //채팅 메세지 전송 버튼을 누름
    void on_openFile_clicked(); // 파일 오픈 버튼 누름
    void on_sendFile_clicked();  // 파일 전송 버튼 누름
    void on_messageLineEdit_returnPressed();
private:
    Ui::Widget *ui;
    QTcpSocket* socket;  // 통신을 위해 사용될 소켓
    QString fileName;
};
#endif
