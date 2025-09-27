#ifndef MYCOMBOBOX_H
#define MYCOMBOBOX_H

#include <QComboBox>
#include <QMouseEvent>

class MyComboBox : public QComboBox
{
    Q_OBJECT

public:
    MyComboBox(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void on_ComboBox_clicked();
};

#endif // MYCOMBOBOX_H