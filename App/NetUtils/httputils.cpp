#include "httputils.h"
#include<QTextCodec>
#include<QJsonDocument>
#include<QJsonObject>
HttpUtils::HttpUtils(QObject *parent):QObject(parent){
    netWorkAcessManager=new QNetworkAccessManager(this);
    QObject::connect(netWorkAcessManager, SIGNAL(finished(QNetworkReply*)),this,SLOT(finishedSlot(QNetworkReply*)));
}

void HttpUtils::finishedSlot(QNetworkReply *netWorkReply){
    QVariant statusV=netWorkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(netWorkReply->error()==QNetworkReply::NoError){
        QByteArray bytes = netWorkReply->readAll();  // bytes
        QString string = QString::fromUtf8(bytes);
        QJsonDocument jsonDocument=QJsonDocument::fromJson(string.toLocal8Bit().data());
        if(!jsonDocument.isObject()){
           callBack->load(string);
           return;
        }
        callBack->load(QString(QJsonDocument(jsonDocument.object()).toJson()));
    }else{
        qDebug()<<"Request Error";
        qDebug("----->Error code %d,\n ErrorInfo %s",statusV.toInt(),netWorkReply->errorString().data());
        callBack->load("false");
        callBack->loadError(netWorkReply->errorString());
    }
    netWorkReply->deleteLater();
}

//启动一个异步线程去从网络上，获取数据。
class  GetAsyncThread:public QThread{
private:
    QNetworkAccessManager *netWorkAcessManager;
    QNetworkRequest *netWorkRequest;
public:
    GetAsyncThread(QNetworkAccessManager *manager,QNetworkRequest *request){
        this->netWorkAcessManager=manager;
        this->netWorkRequest=request;
    }

    void run(){
        netWorkAcessManager->get(*netWorkRequest);
    }
};

//启动一个异步线程去从网络上，获取数据。
class PostAsyncThread:public QThread{

private:
    QNetworkAccessManager *netWorkAcessManager;
    QNetworkRequest *netWorkRequest;
    QByteArray byteArrayData;
public:
    PostAsyncThread(QNetworkAccessManager *manager,QNetworkRequest *request,QByteArray byteArrayData){
        this->netWorkAcessManager=manager;
        this->netWorkRequest=request;
        this->byteArrayData=byteArrayData;
    }
   void run(){
       netWorkAcessManager->post(*netWorkRequest,byteArrayData);
   }
};


//do get
void HttpUtils::doGet(QString *url,HttpCallBack *callBack){
    this->callBack=callBack;
    QUrl requstUrl(*url);
    QNetworkRequest *netWorkRequest=new QNetworkRequest(requstUrl);
    GetAsyncThread *get=new GetAsyncThread(netWorkAcessManager,netWorkRequest);
    get->run();
}

//do post
void HttpUtils::doPost(QString *url,QString *value,HttpCallBack *callBack){
    this->callBack=callBack;
    QUrl requstUrl(*url);
    QNetworkRequest *netWorkRequest=new QNetworkRequest(requstUrl);
    QByteArray dataValue=(*value).toUtf8();
    PostAsyncThread *post=new PostAsyncThread(netWorkAcessManager,netWorkRequest,dataValue);
    post->run();
}







