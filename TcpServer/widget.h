#ifndef WIDGET_H                  // 防止头文件重复包含的宏定义
#define WIDGET_H

#include <QWidget>                 // 包含QWidget头文件，QWidget是所有用户界面对象的基类
#include <QTcpServer>              // 包含QTcpServer头文件，用于创建TCP服务器
#include <QDebug>                  // 包含QDebug头文件，用于调试输出
#include <QTcpSocket>              // 包含QTcpSocket头文件，用于TCP通信

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget      // 主窗口类，继承自QWidget
{
    Q_OBJECT                      // Q_OBJECT宏，启用信号与槽机制

public:
    Widget(QWidget *parent = nullptr);  // 构造函数，parent为父窗口指针
    ~Widget();                          // 析构函数

    QTcpServer* server;                // TCP服务器指针
    
public slots:
    void on_newClient_connect();       // 新客户端连接时的槽函数
    void on_readyRead_handler();       // 接收客户端数据的槽函数
    void mdisconnected();              // 客户端断开连接的槽函数
    void mstateChanged(QAbstractSocket::SocketState socketState);  // 客户端连接状态改变的槽函数
    void mComboBox_refresh();          // 刷新组合框的槽函数

private slots:
    void on_btnStartListen_clicked();  // 开始监听按钮点击的槽函数
    void on_btnSend_clicked();         // 发送按钮点击的槽函数
    void on_btnStopListen_clicked();   // 停止监听按钮点击的槽函数
    void on_btnLineOut_clicked();      // 退出按钮点击的槽函数

private:
    Ui::Widget *ui;                    // UI界面对象指针
};
#endif // WIDGET_H
