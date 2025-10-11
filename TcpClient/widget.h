// 防止头文件重复包含的宏定义
#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpSocket>    // TCP套接字类：用于网络通信
#include <QWidget>       // Qt基础窗口类：提供窗口功能
#include <QDebug>        // 调试输出工具：用于打印调试信息
#include <QTimer>        // 定时器类：用于实现超时检测
#include <error.h>       // 错误处理：提供错误信息处理功能

// Qt命名空间定义
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

// 主窗口类，继承自QWidget
class Widget : public QWidget
{
    Q_OBJECT // Qt信号槽机制宏

public:
    // 构造函数，parent为父窗口指针
    Widget(QWidget *parent = nullptr);
    // 析构函数
    ~Widget();

private slots:
    // 连接按钮点击事件处理
    void on_btnConnect_clicked();
    // 接收服务器数据的槽函数
    void mRead_Data_From_Server();
    // 发送按钮点击事件处理
    void on_btnSend_clicked();
    // 断开连接按钮点击事件处理
    void on_btnDiscon_clicked();
    // 连接成功回调函数
    void onConnected();
    // 连接错误回调函数
    void onError(QAbstractSocket::SocketError);
    // 连接超时回调函数
    void onTimerOut();

private:
    // UI对象指针，用于访问界面元素
    Ui::Widget *ui;
    // TCP客户端套接字
    QTcpSocket* client;
    // 连接超时定时器
    QTimer *timer;
    // 私有方法：设置文本颜色并插入到接收框
    void setInsertColor(Qt::GlobalColor color,QString str);
};

#endif // WIDGET_H
