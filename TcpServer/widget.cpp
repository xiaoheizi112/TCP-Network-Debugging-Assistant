#include "widget.h"
#include "ui_widget.h"
#include "mycombobox.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>
#include <QTextCursor>
#include <QScrollBar>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    tcpServer = new QTcpServer(this);
    
    // 连接信号和槽
    connect(tcpServer, &QTcpServer::newConnection, this, &Widget::on_newConnection);
    connect(ui->comboBox_2, &MyComboBox::on_ComboBox_clicked, this, &Widget::on_ComboBox_clicked);
    
    // 初始化IP地址列表
    on_ComboBox_clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_newConnection()
{
    QTcpSocket *socket = tcpServer->nextPendingConnection();
    
    // 连接客户端的信号和槽
    connect(socket, &QTcpSocket::readyRead, this, &Widget::on_readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Widget::on_disconnected);
    connect(socket, &QTcpSocket::stateChanged, this, &Widget::on_stateChanged);
    
    // 添加客户端到下拉框
    QString clientInfo = QString("%1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    ui->comboBox_2->addItem(clientInfo, QVariant::fromValue(socket));
    
    // 显示连接信息
    QString msg = QString("[%1] 客户端连接: %2\n")
                  .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                  .arg(clientInfo);
    ui->textEdit->append(msg);
}

void Widget::on_readyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;
    
    QByteArray data = socket->readAll();
    QString clientInfo = QString("%1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    
    QString msg = QString("[%1] 收到来自 %2 的数据: %3\n")
                  .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                  .arg(clientInfo)
                  .arg(QString::fromUtf8(data));
    
    ui->textEdit->append(msg);
    
    // 自动滚动到底部
    QScrollBar *scrollBar = ui->textEdit->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void Widget::on_disconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;
    
    QString clientInfo = QString("%1:%2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    
    // 从下拉框中移除客户端
    for (int i = 0; i < ui->comboBox_2->count(); ++i) {
        QTcpSocket *itemSocket = ui->comboBox_2->itemData(i).value<QTcpSocket*>();
        if (itemSocket == socket) {
            ui->comboBox_2->removeItem(i);
            break;
        }
    }
    
    // 显示断开连接信息
    QString msg = QString("[%1] 客户端断开: %2\n")
                  .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                  .arg(clientInfo);
    ui->textEdit->append(msg);
    
    socket->deleteLater();
}

void Widget::on_stateChanged()
{
    // 状态变化处理
}

void Widget::on_ComboBox_clicked()
{
    ui->comboBox->clear();
    
    // 获取所有网络接口
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    
    for (const QNetworkInterface &interface : interfaces) {
        if (interface.flags() & QNetworkInterface::IsUp &&
            interface.flags() & QNetworkInterface::IsRunning &&
            !(interface.flags() & QNetworkInterface::IsLoopBack)) {
            
            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            for (const QNetworkAddressEntry &entry : entries) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol) {
                    ui->comboBox->addItem(entry.ip().toString());
                }
            }
        }
    }
    
    // 添加本地回环地址
    ui->comboBox->addItem("127.0.0.1");
}

void Widget::on_pushButton_clicked()
{
    // 开始监听
    QString ip = ui->comboBox->currentText();
    quint16 port = ui->lineEdit->text().toUShort();
    
    if (tcpServer->listen(QHostAddress(ip), port)) {
        QString msg = QString("[%1] 服务器开始监听: %2:%3\n")
                      .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                      .arg(ip)
                      .arg(port);
        ui->textEdit->append(msg);
        
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
    } else {
        QMessageBox::warning(this, "错误", QString("无法绑定端口 %1: %2")
                            .arg(port)
                            .arg(tcpServer->errorString()));
    }
}

void Widget::on_pushButton_2_clicked()
{
    // 停止监听
    tcpServer->close();
    
    // 断开所有客户端连接
    for (int i = ui->comboBox_2->count() - 1; i >= 0; --i) {
        QTcpSocket *socket = ui->comboBox_2->itemData(i).value<QTcpSocket*>();
        if (socket) {
            socket->disconnectFromHost();
        }
    }
    
    ui->comboBox_2->clear();
    
    QString msg = QString("[%1] 服务器停止监听\n")
                  .arg(QDateTime::currentDateTime().toString("hh:mm:ss"));
    ui->textEdit->append(msg);
    
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
}

void Widget::on_pushButton_3_clicked()
{
    // 发送数据
    QString data = ui->textEdit_2->toPlainText();
    if (data.isEmpty()) return;
    
    int currentIndex = ui->comboBox_2->currentIndex();
    if (currentIndex < 0) {
        QMessageBox::information(this, "提示", "没有连接的客户端");
        return;
    }
    
    QString currentText = ui->comboBox_2->currentText();
    
    if (currentText == "全部客户端") {
        // 发送给所有客户端
        for (int i = 1; i < ui->comboBox_2->count(); ++i) { // 从1开始，跳过"全部客户端"
            QTcpSocket *socket = ui->comboBox_2->itemData(i).value<QTcpSocket*>();
            if (socket && socket->state() == QTcpSocket::ConnectedState) {
                socket->write(data.toUtf8());
            }
        }
        
        QString msg = QString("[%1] 发送给全部客户端: %2\n")
                      .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                      .arg(data);
        ui->textEdit->append(msg);
    } else {
        // 发送给指定客户端
        QTcpSocket *socket = ui->comboBox_2->itemData(currentIndex).value<QTcpSocket*>();
        if (socket && socket->state() == QTcpSocket::ConnectedState) {
            socket->write(data.toUtf8());
            
            QString msg = QString("[%1] 发送给 %2: %3\n")
                          .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                          .arg(currentText)
                          .arg(data);
            ui->textEdit->append(msg);
        } else {
            QMessageBox::warning(this, "错误", "客户端连接已断开");
        }
    }
    
    ui->textEdit_2->clear();
}