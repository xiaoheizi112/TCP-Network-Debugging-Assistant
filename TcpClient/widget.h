#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QTimer>
#include "error.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnConnect_clicked();

    void on_btnSend_clicked();

    void on_readyRead_handler();

    void on_btnDisconnect_clicked();

    void on_connected_handler();

    void on_error_handler(QAbstractSocket::SocketError);

private:
    Ui::Widget *ui;
    QTcpSocket* tcpSocket;
    QTimer* timer;
    void setInsertColor(QString str,QColor color);
};

#endif // WIDGET_H