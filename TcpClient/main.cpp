#include "widget.h"    // 包含主窗口类头文件
#include <QApplication> // 包含Qt应用程序类头文件

// 程序主入口函数：所有Qt应用程序的起点
int main(int argc, char *argv[])
{
    // 创建Qt应用程序实例：管理应用程序的资源、事件处理等
    QApplication a(argc, argv);
    // 创建主窗口实例：程序的主要用户界面
    Widget w;
    // 显示主窗口：使窗口可见
    w.show();
    // 启动应用程序事件循环：等待并处理用户事件，保持程序运行
    return a.exec();
}
