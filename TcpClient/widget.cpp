#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QTextCursor>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setLayout(ui->verticalLayout);
    tcpSocket = new QTcpSocket(this);
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(5000);
    
    // 连接信号与槽
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(on_readyRead_handler()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(on_error_handler(QAbstractSocket::SocketError)));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(on_connected_handler()));
    
    // 初始化按钮状态
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->btnSend->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnConnect_clicked()
{
    QString serverAddr = ui->lineEditAddr->text();
    int serverPort = ui->lineEditPort->text().toInt();
    
    tcpSocket->connectToHost(serverAddr,serverPort);
    
    // 启动连接超时定时器
    timer->start();
    connect(timer, &QTimer::timeout, [this](){
        if(tcpSocket->state() != QAbstractSocket::ConnectedState){
            tcpSocket->abort();
            QMessageBox::warning(this, "连接超时", "连接服务器超时，请检查网络连接！");
            ui->btnConnect->setEnabled(true);
            ui->btnDisconnect->setEnabled(false);
            ui->btnSend->setEnabled(false);
        }
    });
    
    ui->btnConnect->setEnabled(false);
}

void Widget::on_btnSend_clicked()
{
    QByteArray sendData = ui->textEditSend->toPlainText().toLocal8Bit();
    tcpSocket->write(sendData);
    setInsertColor("客户端:"+ui->textEditSend->toPlainText(),QColor(0,0,255));
    ui->textEditSend->clear();
}

void Widget::on_readyRead_handler()
{
    QByteArray recvData = tcpSocket->readAll();
    setInsertColor("服务端:"+recvData,QColor(0,0,0));
}

void Widget::on_btnDisconnect_clicked()
{
    tcpSocket->close();
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->btnSend->setEnabled(false);
}

void Widget::on_connected_handler()
{
    timer->stop(); // 停止超时定时器
    ui->btnConnect->setEnabled(false);
    ui->btnDisconnect->setEnabled(true);
    ui->btnSend->setEnabled(true);
    setInsertColor("连接服务器成功！",QColor(0,255,0));
}

void Widget::on_error_handler(QAbstractSocket::SocketError)
{
    timer->stop(); // 停止超时定时器
    ui->btnConnect->setEnabled(true);
    ui->btnDisconnect->setEnabled(false);
    ui->btnSend->setEnabled(false);
    setInsertColor("连接服务器失败！",QColor(255,0,0));
}

void Widget::setInsertColor(QString str, QColor color)
{
    ui->textEditRev->setTextColor(color);
    ui->textEditRev->insertPlainText(str+"\n");
    ui->textEditRev->moveCursor(QTextCursor::End);
    ui->textEditRev->ensureCursorVisible();
}