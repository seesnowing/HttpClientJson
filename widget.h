#ifndef WIDGET_H
#define WIDGET_H
#include<QWidget>
#include<QPoint>
#include<QLineEdit>
#include<QRadioButton>
#include<QScrollArea>
#include<QPushButton>
#include<QTextEdit>
#include "App/NetUtils/httputils.h"
#include "App/Base/appbasewidget.h"
#include "App/NetUtils/HttpCallBack.h"
#include<QMessageBox>
#include<QSystemTrayIcon>
#include<QApplication>

namespace Ui {
class Widget;
}

class Widget : public AppBaseWidget,HttpCallBack
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent=0);
    ~Widget();
private:
    QLineEdit *requestUrl,*parmEdit;
    QTextEdit *displayEditText;
    QPushButton *doRequest;
    QPushButton *closeButton;
    QPushButton *minimButton;
    QRadioButton *selectForGet,*selectForPost;
public:
    void getTestResult();
    void postTestResult();
    virtual void initViews();
    virtual void initListeners();
    virtual void initData();
//重写拖动事件
public:
    bool isDrag=false;
    QPoint m_position;
    void Widget::mousePressEvent(QMouseEvent*);
    void Widget::mouseReleaseEvent(QMouseEvent*);
    void Widget::mouseMoveEvent(QMouseEvent*);
private:
     QSystemTrayIcon *trayIcon;
private slots:
    void on_doRequest_clicked();
    void on_mininum_button_clicked();
    void on_close_button_clicked();
    void on_recieveSysTrayIconEvent(QSystemTrayIcon::ActivationReason);
private:
    Ui::Widget *ui;
private:
    QObject *mContext;
public:
    void load(QString result);
    void loadError(QString error);
};

#endif // WIDGET_H
