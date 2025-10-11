// 包含头文件
#include "mycombobox.h"
// 包含必要的Qt头文件
#include <QMouseEvent>

// MyComboBox构造函数
MyComboBox::MyComboBox(QWidget *parent) : QComboBox(parent)
{
    // 调用父类构造函数，无需额外初始化
}

// 重写鼠标按下事件
void MyComboBox::mousePressEvent(QMouseEvent *e)
{
    // 当左键点击时，发出自定义信号
    if(e->button() == Qt::LeftButton){
        emit on_ComboBox_clicked();
    }
    // 调用父类的鼠标按下事件，保持原有功能
    QComboBox::mousePressEvent(e);
}
