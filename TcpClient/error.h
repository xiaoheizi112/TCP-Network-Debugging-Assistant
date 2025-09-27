#ifndef ERROR_H
#define ERROR_H

// 错误处理相关的头文件
// 用于TCP客户端的错误处理和调试

#include <QAbstractSocket>
#include <QString>

// 错误类型枚举
enum class NetworkError {
    ConnectionRefused,
    RemoteHostClosed,
    HostNotFound,
    SocketTimeout,
    NetworkError,
    UnknownError
};

// 错误处理工具类
class ErrorHandler {
public:
    static QString getErrorString(QAbstractSocket::SocketError error) {
        switch(error) {
            case QAbstractSocket::ConnectionRefusedError:
                return "连接被拒绝";
            case QAbstractSocket::RemoteHostClosedError:
                return "远程主机关闭连接";
            case QAbstractSocket::HostNotFoundError:
                return "主机未找到";
            case QAbstractSocket::SocketTimeoutError:
                return "连接超时";
            case QAbstractSocket::NetworkError:
                return "网络错误";
            default:
                return "未知错误";
        }
    }
};

#endif // ERROR_H