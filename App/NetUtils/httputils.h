#ifndef HTTPUTILS_H
#define HTTPUTILS_H
#include <QThread>
#include<QRunnable>
#include<QThreadPool>
#include <QSettings>
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "QtNetwork/QNetworkRequest"
#include <QUrl>
#include "HttpCallBack.h"
enum REQUEST_TYPE{
    GET,POST
};

class HttpUtils:public QObject
{
    Q_OBJECT
private:
    //请求超时代码 8 秒超时
    int REQUEST_TIME_OUT=8;
    QVariant RESULT_CODE=0;
    QNetworkAccessManager *netWorkAcessManager;
public:
    explicit HttpUtils(QObject *parent = 0);

public:
    //重载获取json str 字符串 的 get 请求
    void doGet(QString*,HttpCallBack *);
    //发送get 请求
    void doPost(QString*,QString*,HttpCallBack*);
    //携带进度的get请求
    void doGetForProgress();
    //携带参数的post请求
    void doPostForProgress();
public:
    //回调
    HttpCallBack *callBack;
public slots:
    void finishedSlot(QNetworkReply *netWorkReply);
signals:
private:
};

#endif // HTTPUTILS_H
