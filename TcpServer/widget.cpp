// 包含头文件
#include "widget.h"
#include "ui_widget.h"

// 包含额外的Qt类
#include <QMessageBox>
#include <QNetworkInterface>
#include "mycombobox.h"

// Widget构造函数
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);  // 初始化UI
    this->setLayout(ui->verticalLayout);  // 设置布局
    server = new QTcpServer(this);  // 创建TCP服务器对象

    // 连接信号与槽
    connect(ui->comboBoxChildren,&MyComboBox::on_ComboBox_clicked,this,&Widget::mComboBox_refresh);
    connect(server,SIGNAL(newConnection()),this,SLOT(on_newClient_connect()));
    
    // 初始化按钮状态
    ui->btnStartListen->setEnabled(true);
    ui->btnStopListen->setEnabled(false);
    ui->btnLineOut->setEnabled(false);
    ui->btnSend->setEnabled(false);

    // 获取所有网络接口的IP地址
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for(QHostAddress tmp : addresses){
        // 只添加IPv4地址到地址下拉框
        if(tmp.protocol() == QAbstractSocket::IPv4Protocol){
            ui->comboBoxAddr->addItem(tmp.toString());
        }
    }
}

// Widget析构函数
Widget::~Widget()
{
    delete ui;  // 释放UI资源
}

// 处理新客户端连接的槽函数
void Widget::on_newClient_connect()
{
    // 检查是否有等待连接的客户端
    if(server->hasPendingConnections()){
        // 获取下一个等待连接的客户端套接字
        QTcpSocket* connection = server->nextPendingConnection();
        // 输出客户端信息到调试窗口
        qDebug()<<"client Addr: "<<connection->peerAddress().toString()<<"port: "<<connection->peerPort();
        // 在接收文本框中显示客户端信息
        ui->textEditRev->insertPlainText("客户端地址："+connection->peerAddress().toString()+
                                         "\n客户端端口号："+QString::number(connection->peerPort())+"\n");
        
        // 连接信号与槽，处理数据接收
        connect(connection,SIGNAL(readyRead()),this,SLOT(on_readyRead_handler()));
        // 连接信号与槽，处理连接状态变化
        connect(connection, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                this, SLOT(mstateChanged(QAbstractSocket::SocketState)));

        // 将客户端端口号添加到组合框中
        ui->comboBoxChildren->addItem(QString::number(connection->peerPort()));
        // 设置当前显示文本的操作
        ui->comboBoxChildren->setCurrentText(QString::number(connection->peerPort()));

        // 启用发送按钮
        if(!ui->btnSend->isEnabled()){
            ui->btnSend->setEnabled(true);
        }
    }
}

// 开始监听按钮点击的槽函数
void Widget::on_btnStartListen_clicked()
{
    // 获取用户输入的端口号
    int port = ui->lineEditPort->text().toInt();
    // 开始监听指定的IP地址和端口号
    if(!server->listen(QHostAddress(ui->comboBoxAddr->currentText()),port)){
        qDebug()<<"listenError!";
        QMessageBox msgBox;
        msgBox.setWindowTitle("监听失败！");
        msgBox.setText("端口号被占用！");
        msgBox.exec();
        return;
    }
    // 更新按钮状态
    ui->btnStartListen->setEnabled(false);
    ui->btnStopListen->setEnabled(true);
    ui->btnLineOut->setEnabled(true);
}

// 接收客户端数据的槽函数
void Widget::on_readyRead_handler()
{
    // 获取发送信号的QTcpSocket对象
    QTcpSocket* tmpSock = qobject_cast<QTcpSocket*>(sender());
    // 读取所有可用数据
    QByteArray recvData = tmpSock->readAll();
    // 在接收文本框中显示收到的数据和客户端信息
    ui->textEditRev->insertPlainText("客户端("+QString::number(tmpSock->peerPort())+"):"+recvData);
    // 将光标移动到文本末尾
    ui->textEditRev->moveCursor(QTextCursor::End);
    // 确保光标可见
    ui->textEditRev->ensureCursorVisible();
}

// 客户端断开连接的槽函数
void Widget::mdisconnected()
{
    // 获取发送信号的QTcpSocket对象
    QTcpSocket* tmpSock = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<"client out!";
    // 释放套接字资源
    tmpSock->deleteLater();
}

// 客户端连接状态改变的槽函数
void Widget::mstateChanged(QAbstractSocket::SocketState socketState)
{
    int tmpIndex;
    // 获取发送信号的QTcpSocket对象
    QTcpSocket* tmpSock = qobject_cast<QTcpSocket*>(sender());
    qDebug()<<"client out In state"<<socketState;
    
    // 根据连接状态执行不同操作
    switch(socketState){
    case QAbstractSocket::UnconnectedState:
        // 客户端断开连接，在接收文本框中显示信息
        ui->textEditRev->insertPlainText("客户端("+QString::number(tmpSock->peerPort())+")断开！\n");
        // 从组合框中移除客户端
        tmpIndex = ui->comboBoxChildren->findText(QString::number(tmpSock->peerPort()));
        ui->comboBoxChildren->removeItem(tmpIndex);
        // 释放套接字资源
        tmpSock->deleteLater();
        // 如果没有客户端连接，禁用发送按钮
        if(ui->comboBoxChildren->count() == 0)
            ui->btnSend->setEnabled(false);
        break;
    case QAbstractSocket::ConnectedState:
    case QAbstractSocket::ConnectingState:
        // 客户端接入，在接收文本框中显示信息
        ui->textEditRev->insertPlainText("客户端接入！");
        break;
    }
}

// 刷新客户端列表组合框的槽函数
void Widget::mComboBox_refresh()
{
    // 清空组合框
    ui->comboBoxChildren->clear();
    // 查找所有客户端套接字
    QList<QTcpSocket*> tcpsocketClients = server->findChildren<QTcpSocket*>();
    // 将每个客户端的端口号添加到组合框
    for(QTcpSocket* tmp : tcpsocketClients){
        if(tmp!=nullptr)
            ui->comboBoxChildren->addItem(QString::number(tmp->peerPort()));
    }
    // 添加"all"选项，表示发送给所有客户端
    ui->comboBoxChildren->addItem("all");
}

// 发送按钮点击的槽函数
void Widget::on_btnSend_clicked()
{
    // 查找所有客户端套接字
    QList<QTcpSocket*> tcpsocketClients = server->findChildren<QTcpSocket*>();
    // 检查是否有客户端连接
    if(tcpsocketClients.isEmpty()){
        // 没有客户端连接，显示错误消息
        QMessageBox msgBox;
        msgBox.setWindowTitle("发送错误！");
        msgBox.setText("当前无法连接！");
        msgBox.exec();
        ui->btnSend->setEnabled(false);
        return;
    }
    // 判断是发送给特定客户端还是所有客户端
    if(ui->comboBoxChildren->currentText()!= "all"){
        // 发送给特定客户端
        QString currentName = ui->comboBoxChildren->currentText();
        for(QTcpSocket*tmp : tcpsocketClients){
            if(QString::number(tmp->peerPort()) == currentName){
                tmp->write((ui->textEditSend->toPlainText()+"\n").toStdString().c_str());
            }
        }
    }else{
        // 发送给所有客户端
        for(QTcpSocket* tmp : tcpsocketClients){
            QByteArray sendData = ui->textEditSend->toPlainText().toLocal8Bit();
            tmp->write(sendData);
        }
    }
}

// 停止监听按钮点击的槽函数
void Widget::on_btnStopListen_clicked()
{
    // 查找所有客户端套接字
    QList<QTcpSocket*> tcpsocketClients = server->findChildren<QTcpSocket*>();
    // 关闭所有客户端连接
    for(QTcpSocket* tmp : tcpsocketClients){
        tmp->close();
    }
    // 关闭服务器
    server->close();
    // 更新按钮状态
    ui->btnStartListen->setEnabled(true);
    ui->btnStopListen->setEnabled(false);
    ui->btnLineOut->setEnabled(false);
}

// 退出按钮点击的槽函数
void Widget::on_btnLineOut_clicked()
{
    // 先停止监听，关闭所有连接
    on_btnStopListen_clicked();
    // 释放服务器资源
    delete server;
    // 关闭窗口
    this->close();
}

