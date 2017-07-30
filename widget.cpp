#include "widget.h"
#include "ui_widget.h"
#include<QMouseEvent>
Widget::Widget(QWidget *parent):AppBaseWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    mContext=this;
    //初始化数据
    initViews();
    initListeners();
    initData();
}

void Widget::initViews(){
    doRequest=ui->doRequest;
    requestUrl=ui->requestUrl;
    parmEdit=ui->parmEdit;
    displayEditText=ui->textEdit;
    selectForGet=ui->GetRequestView;
    selectForPost=ui->PostRequestView;
    closeButton=ui->close_button;
    minimButton=ui->mininum_button;
}

void Widget::initListeners(){
    //监听获取事件的信号
    connect(doRequest,SIGNAL(clicked()),SLOT(on_doRequest_clicked()));
    connect(minimButton,SIGNAL(clicked()),SLOT(on_mininum_button_clicked()));
    connect(closeButton,SIGNAL(clicked()),SLOT(on_close_button_clicked()));
}

void Widget::initData(){
    //初始化默认参数
}

/**
 * @brief Widget::mousePressEvent
 * @param e
 * 目的是为了，支持在无边框下支持窗口拖动程序。
 */

void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        isDrag = true;
        m_position = e->globalPos() - this->pos();
        e->accept();
    }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if(isDrag && (e->buttons() && Qt::LeftButton))
    {
        move(e->globalPos() - m_position);
        e->accept();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
    isDrag = false;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::loadError(QString error){
    QMessageBox::information(this,tr("Error"),error);
}

void Widget::load(QString result){
    displayEditText->setText(result);
}

void Widget::on_doRequest_clicked()
{
    if(selectForGet->isChecked())
    {
        getTestResult();
    }else
    {
        postTestResult();
    }
}


//get 测试
void Widget::getTestResult(){
    QString requestHeadUrl=requestUrl->text().trimmed();
    if(requestHeadUrl==NULL){
        return;
    }
    HttpUtils *request=new HttpUtils();
    //异步调用
    request->doGet(&requestHeadUrl,this);
}

//post 测试
void Widget::postTestResult(){
    QString requestHeadUrl=requestUrl->text().trimmed();
    QString requestParam=parmEdit->text().trimmed();
    if(requestHeadUrl==NULL){
        return;
    }

    HttpUtils *request=new HttpUtils;
    //异步调用
    request->doPost(&requestHeadUrl,&requestParam,this);
}

void Widget::on_recieveSysTrayIconEvent(QSystemTrayIcon::ActivationReason reson){
    switch(reson){
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    }
}

void Widget::on_mininum_button_clicked()
{
    this->hide();
    if(trayIcon==NULL){
        trayIcon=new QSystemTrayIcon();
    }
    QIcon icon=QIcon(":/drawable/jsonTest.ico");
    trayIcon->setToolTip(QString("Json 测试工具"));
    trayIcon->setIcon(icon);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(on_recieveSysTrayIconEvent(QSystemTrayIcon::ActivationReason)));
    trayIcon->show();
}

void Widget::on_close_button_clicked(){
    QApplication::exit(0);
}
