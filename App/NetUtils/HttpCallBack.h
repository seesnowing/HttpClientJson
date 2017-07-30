#ifndef HTTPCALLBACK_H
#define HTTPCALLBACK_H
//定义 http get 回调接口
class HttpCallBack{
public:
    virtual void load(QString result)=0;
    virtual void loadError(QString error)=0;
};
#endif // HTTPCALLBACK_H
