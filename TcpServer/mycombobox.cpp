#include "mycombobox.h"

MyComboBox::MyComboBox(QWidget *parent)
    : QComboBox(parent)
{
}

void MyComboBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit on_ComboBox_clicked();
    }
    QComboBox::mousePressEvent(event);
}