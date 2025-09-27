#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_newConnection();
    void on_readyRead();
    void on_disconnected();
    void on_stateChanged();
    void on_ComboBox_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    QTcpServer *tcpServer;
};

#endif // WIDGET_H