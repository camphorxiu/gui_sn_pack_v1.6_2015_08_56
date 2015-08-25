#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPrinter>
#include <QPrintDialog>
#include <QJsonParseError>
#include <QJsonObject>
#include <QLibrary>
#include <QDir>
#include <QProcess>
#include <QSettings>
#include <QTextCodec>

#include "lib/class_string.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    g_is_testing = 0;
    sn_scanned_num = 0;

    this->test_status_change("<p>请扫描<br>条码 1 </p>",\
                             "rgb(255,0,0)", "color:rgb(10，10，10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
    setFocusPolicy(Qt::StrongFocus);    //Qt中keyPressEvent函数监听键盘输入

    /* 将一些选项可配置化 */
    readConfig();

    connect(&timer_read_sn,SIGNAL(timeout()),this,SLOT(timerUpDate_read_sn()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief 从config.ini文件中读取配置信息
 */
void MainWindow::readConfig()
{
    /* 读配置文件 */
    QSettings settings("config.ini",QSettings::IniFormat);
    /* 在此添加设置，即可读写ini文件中的中文 */
    settings.setIniCodec(QTextCodec::codecForName("UTF8"));
    /* 定位配置文件组 */
    settings.beginGroup("config");

    if(settings.allKeys().isEmpty()){
        QMessageBox::information(NULL,"OK","Settings File is Empty!");
        return;
    }

    //获取config信息
    //exe route
    QString cfg_info;
    QStringList cfg_list;
    cfg_info = settings.value("cfg" + QString::number(0,10)).toString();
    cfg_list = cfg_info.split("~");
    ExeRoute = cfg_list[1];
    qDebug() << "Exe Route:" + ExeRoute;

    //txt route
    cfg_info = settings.value("cfg" + QString::number(1,10)).toString();
    cfg_list = cfg_info.split("~");
    TxtRoute = cfg_list[1];
    qDebug() << "Txt Route:" + TxtRoute;

    //server url
    cfg_info     = settings.value("cfg" + QString::number(2,10)).toString();
    cfg_list= cfg_info.split("~");
    UrlServer = cfg_list[1];
    qDebug() << "Url Server:" + UrlServer;

    //BTW file name
    cfg_info     = settings.value("cfg" + QString::number(3,10)).toString();
    cfg_list= cfg_info.split("~");
    BTWFileName = cfg_list[1];
    qDebug() << ".BTW File Name:" + BTWFileName;

    //Lable printer name
    cfg_info     = settings.value("cfg" + QString::number(4,10)).toString();
    cfg_list= cfg_info.split("~");
    PrinterName = cfg_list[1];
    qDebug() << "Printer Name:" + PrinterName;
}

/********************
函数作用：读滚码超时处理
*********************/
void MainWindow::timerUpDate_read_sn()
{
    g_fail_num++;
    g_is_testing = 0;
    sn_scanned_num = 0;

    timer_read_sn.stop();

    this->test_status_change("<p>请扫描<br>条码 1 </p>",\
                             "rgb(255,0,0)", "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
}


//提示信息显示
void MainWindow::notice_status_display(QString text)
{
    ui->plainTextEdit_notice->setPlainText(text);
}

//测试总体状态显示
void MainWindow::test_status_change(QString text, QString bgcolor, QString font)
{
    ui->statusText->setStyleSheet(font);
    ui->statusText->setText(text);
}

void MainWindow::test_begin(QString SN)
{
    qDebug() << "Test Begin:";

    if(SN.isEmpty()){
        this->test_status_change("等待...", "rgb(255,255,0)",\
                                 "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
        notice_status_display("请重新扫描条形码");
    }else{
        this->test_status_change("等待...", "rgb(0,255,0)",\
                                 "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
        notice_status_display("正在等待服务器生成彩盒码...");

        /* http */
        //创建一个请求
        QNetworkRequest request;
        QString url;

        url = UrlServer + SN;
        request.setUrl(QUrl(url));
        //创建一个管理器
        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
        //发送GET请求
        QNetworkReply *reply = manager->get(request);
        //连接请求结束信号
        connect(manager, SIGNAL(finished(QNetworkReply*)), this, \
                SLOT(replyFinished(QNetworkReply*)));
        //连接响应时返回数据信号
        connect(reply, SIGNAL(readyRead()), this, SLOT(on_readyRead()));
    }
}

//http
void MainWindow::replyFinished(QNetworkReply* reply)
{
    QByteArray data = reply->readAll();

    //这里会输出服务器返回的数据
    qDebug() << data;

    /* Json 解析 */
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(data, &json_error);
    if(json_error.error == QJsonParseError::NoError)
    {
        if(parse_doucment.isObject())
        {
            QJsonObject obj = parse_doucment.object();
            bool code = false;
            QString  use_time;
            QString data;
            if(obj.contains("code"))
            {
                QJsonValue code_value = obj.take("code");
                if(code_value.isBool())
                {
                    code = code_value.toBool();
                    qDebug() << "code:" << code;
                }
            }
            if(obj.contains("use_time"))
            {
                QJsonValue use_time_value = obj.take("use_time");
                if(use_time_value.isDouble())
                {
                    use_time = use_time_value.toVariant().toString();
                    qDebug() << "use_time" << use_time;
                }
            }
            if(obj.contains("data"))
            {
                QJsonValue data_value = obj.take("data");
                if(data_value.isString())
                {
                    data = data_value.toString();
                    qDebug() << "data:" << data;
                }
            }
            if(code == false)
            {
                notice_status_display("彩盒码生成失败：" + data);
                ui->centralWidget->setStyleSheet("background-color: rgb(232, 86, 78)");
                this->test_status_change("失败", "rgb(255,0,0)",\
                                         "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
            }
            else //if(code == true)
            {
                notice_status_display("彩盒码生成成功：" + data + "。");
                ui->centralWidget->setStyleSheet("background-color: rgb(169, 239, 132)");
                this->test_status_change("成功", "rgb(0,255,0)",\
                                         "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
                /* printer */
                this->slotPrint(data);
            }
            timer_read_sn.start(3000);
         }
    }
    g_is_testing = 0;
    sn_scanned_num = 0;
}

void MainWindow::on_readyRead()
{
    //....
}

void MainWindow::slotPrint (QString data)
{
    QPrinter printer;
    QTextDocument doc;

    /* write data into color_box_code.txt */
    QFile file(TxtRoute);
    if (file.open(QFile::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "open color_box_code.txt success";
        QTextStream out(&file);
        out << data;
        /* 调用指定快捷方式 */
//        QProcess::startDetached(ExeRoute,QStringList());
        QStringList param;
        param.append("/AF=" + BTWFileName);
        param.append("/PRN=" + PrinterName);
        param.append("/P");
        param.append("/X");
        QProcess::startDetached(ExeRoute,param);
        qDebug() << "已启动外部被调用程序";
        notice_status_display("启动打印成功");
    }
    else{
        qDebug() << "open color_box_code.txt fail";
        notice_status_display("启动打印失败");
    }
}

/**
 * 捕获键盘或者巴枪的输入
 *
 * @brief MainWindow::keyPressEvent
 * @param keyValue
 */
void MainWindow::keyPressEvent(QKeyEvent *keyValue)
{
    if(!g_is_testing){
        if(keyValue->key() == 16777220){        //enter == 16777220
            qDebug() << "Enter: "<< keyStr;

            /* 正则表达式 */
            QString pattern("(.*)x0(.*)");
            QRegExp rx(pattern);
            int pos = keyStr.indexOf(rx);

            keyStr = keyStr.mid(2);             //去掉0x前缀
            qDebug() << "keyStr.mid(2):" <<keyStr;

            if (keyStr.size() == 8) {
                if (g_is_testing == 0) {
                    sn_scanned_num++;
                    qDebug() << "sn_scanned_num:" << sn_scanned_num;
                    if(sn_scanned_num == 1)
                    {
                       /* the event that generate file will trig the "commader" */
                       /* delete the file .txt */
                       QFile::remove(TxtRoute);
                       if(QFile::exists(TxtRoute))
                       {/* remove .txt file fail */
                         sn_scanned_num = 0;
                         this->test_status_change("<p>请扫描<br>条码 1 </p>",\
                                                  "rgb(255,0,0)", "color:rgb(10,10,10);font-size:48pt;font-size:60px;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
                         /* 清空条码显示区 */
                         ui->SNText->setText("");
                         ui->SNText_2->setText("");
                         QMessageBox::information(NULL,"OK","请手动删除文件"+TxtRoute);
                         return;
                       }

                       /* 设置背景为黄色 */
                       ui->centralWidget->setStyleSheet("background-color: rgb(255, 255, 127)");
                       ui->SNText->setText("");
                       ui->SNText_2->setText("");
                       /* Added judge for xTank's type,01-red,02-blue */
                       /* 正则表达式 */
//                       if(rx.cap(2).toInt()<2000000)

                           qDebug() << "rx.cap(2).toInt()" << rx.cap(2).toInt();
                           qDebug() << "red - right";
                           this->test_status_change("<p>请扫描<br>条码 2 </p>",\
                                                    "rgb(0,0,255)", "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
                           ui->SNText->setText(keyStr);//显示红车条码
                           notice_status_display("条码 1 扫描成功！");
                           keyStr1 = keyStr;

                    }
                    else if(sn_scanned_num == 2)
                    {
                        /* 正则表达式 */
//                        if(rx.cap(2).toInt()<2000000)


                            qDebug() << "rx.cap(2).toInt()" << rx.cap(2).toInt();
                            qDebug() << "blue - right";
                            g_is_testing = 1;
                            ui->SNText_2->setText(keyStr);//显示条码 2
                            keyStr2 = keyStr;
                            keyStr  = keyStr1 + "," + keyStr2;
                            qDebug() << "keyStr:" <<keyStr;
                            this->test_status_change("<p>请扫描<br>条码 1 </p>",\
                                                     "rgb(255,0,0)", "color:rgb(10,10,10);font-size:48pt;font-family:'微软雅黑', 'Microsoft Yahei', '黑体', STHeiti;");
                            notice_status_display("条码 2 扫描成功！");
                            this->test_begin(keyStr);

                    }
                } else {
                    qDebug() << g_is_testing;
                    notice_status_display("正在测试中，请等待测试完毕");
                }
            } else {
                qDebug() << "KeyStrSize: " << keyStr.size();
                notice_status_display("条码长度错误！请重新扫描条形码!");
            }
            keyStr.clear();
        } else {
            keyStr += keyValue->text();
            qDebug() << "Key: " << keyValue->key();
        }
    }else{
        qDebug() << "g_is_testing: " << g_is_testing;
    }
}
