#ifndef APPBASEWIDGET_H
#define APPBASEWIDGET_H
#include<QWidget>
class AppBaseWidget:public QWidget
{
public:
    AppBaseWidget(QWidget *parent=0);
    ~AppBaseWidget();
public:
    virtual void initViews()=0;
    virtual void initListeners()=0;
    virtual void initData()=0;
};

#endif // APPBASEWIDGET_H
