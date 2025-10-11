#ifndef MYCOMBOBOX_H                // 防止头文件重复包含的宏定义
#define MYCOMBOBOX_H

#include <QComboBox>                // 包含QComboBox头文件

class MyComboBox : public QComboBox // 自定义组合框类，继承自QComboBox
{
    Q_OBJECT                      // 启用信号与槽机制

public:
    explicit MyComboBox(QWidget *parent = nullptr);  // 构造函数

protected:
    void mousePressEvent(QMouseEvent *e) override;   // 重写鼠标按下事件

signals:
    void on_ComboBox_clicked();   // 自定义信号，当组合框被点击时发出

};

#endif // MYCOMBOBOX_H
