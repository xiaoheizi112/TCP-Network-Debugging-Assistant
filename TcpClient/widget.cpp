#include "widget.h"    // 包含主窗口类头文件
#include "ui_widget.h"  // 包含UI设计头文件

// 构造函数实现：初始化窗口界面和网络连接组件
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    // 初始化UI界面：加载设计器中设计的界面
    ui->setupUi(this);
    // 设置布局管理器：确保界面元素正确排列
    this->setLayout(ui->verticalLayout);
    // 初始状态：禁用断开连接按钮（连接前不可用）
    ui->btnDiscon->setEnabled(false);
    // 初始状态：禁用发送按钮（连接前不可用）
    ui->btnSend->setEnabled(false);

    // 创建TCP客户端套接字对象：用于与服务器建立网络连接
    client = new QTcpSocket(this);
    // 连接信号：当接收到服务器数据时，触发数据接收处理
    connect(client,SIGNAL(readyRead()),this,SLOT(mRead_Data_From_Server()));
    // 连接信号：当网络连接出现错误时，触发错误处理
    connect(client,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onError(QAbstractSocket::SocketError)));
}

// 析构函数实现
Widget::~Widget()
{
    // 释放UI对象占用的内存
    delete ui;
}

// 连接按钮点击事件处理函数：处理用户点击连接按钮的逻辑
void Widget::on_btnConnect_clicked()
{
    // 从界面获取IP地址和端口号，并尝试连接服务器
    client->connectToHost(ui->lineEditIPAddr->text(),ui->lineEditPort->text().toInt());

    // 创建连接超时检测定时器：用于处理连接超时情况
    timer = new QTimer(this);
    // 设置为单次触发模式：定时器只触发一次
    timer->setSingleShot(true);
    // 设置超时时间为5000毫秒（5秒）：超过此时间未连接成功则视为超时
    timer->setInterval(5000);
    // 连接定时器超时信号到处理函数：当超时时触发onTimerOut()
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimerOut()));
    // 禁用整个窗口，防止用户重复操作：在连接过程中不允许用户进行其他操作
    this->setEnabled(false);
    // 启动超时定时器：开始计时
    timer->start();
    // 断开旧的连接成功信号绑定（避免重复连接导致的问题）
    disconnect(client, &QTcpSocket::connected, this, nullptr);
    // 连接新的连接成功信号到处理函数：当连接成功时触发onConnected()
    connect(client,SIGNAL(connected()),this,SLOT(onConnected()));
}

// 接收服务器数据的槽函数：当接收到服务器发送的数据时自动触发
void Widget::mRead_Data_From_Server()
{
    // 读取所有从服务器发来的数据，并以黑色文本显示在接收框
    setInsertColor(Qt::black,client->readAll());
    // 将光标移动到文本末尾，方便查看最新数据
    ui->textEditRev->moveCursor(QTextCursor::End);
    // 确保光标可见：自动滚动到文本末尾
    ui->textEditRev->ensureCursorVisible();
}


// 发送按钮点击事件处理函数：处理用户点击发送按钮的逻辑
void Widget::on_btnSend_clicked()
{
    // 获取界面输入的文本，并添加换行符后转为UTF-8格式
    QByteArray sendData = (ui->textEditSend->toPlainText() + "\n").toUtf8();
    // 通过TCP套接字发送数据到服务器
    client->write(sendData);
    // 以红色文本在接收框中显示发送的内容（用于区分收发）
    setInsertColor(Qt::red,sendData);
    // 将光标移动到文本末尾：方便查看最新发送的数据
    ui->textEditRev->moveCursor(QTextCursor::End);
    // 确保光标可见：自动滚动到文本末尾
    ui->textEditRev->ensureCursorVisible();
}


// 断开连接按钮点击事件处理函数：处理用户点击断开连接按钮的逻辑
void Widget::on_btnDiscon_clicked()
{
    // 关闭TCP客户端套接字：断开与服务器的连接
    client->close();
    // 在接收框显示断开连接信息：告知用户连接已断开
    ui->textEditRev->append("中止连接\n");
    // 启用连接按钮，允许再次连接
    ui->btnConnect->setEnabled(true);
    // 启用端口输入框，允许修改端口：断开后可以更改连接参数
    ui->lineEditPort->setEnabled(true);
    // 启用IP地址输入框，允许修改IP：断开后可以更改连接参数
    ui->lineEditIPAddr->setEnabled(true);
    // 禁用断开连接按钮：断开后不可再次断开
    ui->btnDiscon->setEnabled(false);
    // 禁用发送按钮：断开后不可发送数据
    ui->btnSend->setEnabled(false);
}

// 连接成功回调函数：当与服务器成功建立连接时自动触发
void Widget::onConnected()
{
    // 停止连接超时定时器：连接已成功，无需继续计时
    timer->stop();
    // 启用整个窗口：恢复用户界面的可操作性
    this->setEnabled(true);
    // 在接收框显示连接成功信息：告知用户连接状态
    ui->textEditRev->append("连接成功！\n");
    // 禁用连接按钮，防止重复连接
    ui->btnConnect->setEnabled(false);
    // 禁用端口输入框，连接后不允许修改：防止连接参数被意外更改
    ui->lineEditPort->setEnabled(false);
    // 禁用IP地址输入框，连接后不允许修改：防止连接参数被意外更改
    ui->lineEditIPAddr->setEnabled(false);
    // 启用断开连接按钮：连接成功后可以断开
    ui->btnDiscon->setEnabled(true);
    // 启用发送按钮，允许发送数据：连接成功后可以发送数据
    ui->btnSend->setEnabled(true);
}


// 连接错误回调函数：当与服务器建立连接过程中出现错误时自动触发
void Widget::onError(QAbstractSocket::SocketError error)
{
    // 输出调试信息到控制台：方便开发人员调试问题
    qDebug()<<"连接错误："<< error;
    // 在接收框显示详细的错误信息：告知用户连接失败的具体原因
    ui->textEditRev->insertPlainText("连接出问题啦："+client->errorString());
    // 启用整个窗口：恢复用户界面的可操作性
    this->setEnabled(true);
    // 调用断开连接函数进行资源清理：确保连接相关资源被正确释放
    on_btnDiscon_clicked();
}

// 连接超时回调函数：当连接服务器的时间超过设定的超时时间时自动触发
void Widget::onTimerOut()
{
    // 在接收框显示连接超时信息：告知用户连接未能及时建立
    ui->textEditRev->insertPlainText("连接超时！");
    // 立即中止连接（不等待正常断开过程）：快速终止失败的连接尝试
    client->abort();
    // 启用整个窗口：恢复用户界面的可操作性
    this->setEnabled(true);
}

// 私有方法：设置文本颜色并插入到接收框
// 作用：在接收框中以指定颜色显示文本（用于区分发送和接收的数据）
void Widget::setInsertColor(Qt::GlobalColor color,QString str)
{
    // 获取接收框的当前文本光标：用于控制文本插入位置和格式
    QTextCursor cursor = ui->textEditRev->textCursor();
    // 创建文本格式对象：用于设置文本的显示格式
    QTextCharFormat format;

    // 设置文本的前景色（文字颜色）：根据传入的颜色参数设置
    format.setForeground(QBrush(QColor(color)));
    // 将设置好的格式应用到光标：使后续插入的文本使用该格式
    cursor.setCharFormat(format);
    // 使用设置了颜色的光标插入文本：将文本以指定颜色显示在接收框中
    cursor.insertText(str);
}

