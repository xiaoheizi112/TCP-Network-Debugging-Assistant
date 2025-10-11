// 包含主窗口头文件
#include "widget.h"
// 包含Qt应用程序头文件
#include <QApplication>

// 主函数，程序入口点
int main(int argc, char *argv[])
{
    // 创建应用程序对象
    QApplication a(argc, argv);
    // 创建主窗口对象
    Widget w;
    // 显示主窗口
    w.show();
    // 进入应用程序的事件循环
    return a.exec();
}
