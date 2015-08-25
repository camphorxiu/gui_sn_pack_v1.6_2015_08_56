#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QNetworkReply>

//#include "com1.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sleep(unsigned int msec);

//    MyThread threadA;

    //捕获按键或巴枪
    void keyPressEvent(QKeyEvent *);
    void setBackgroundColor(int,int,int);
    QString keyStr;
    QString keyStr1;
    QString keyStr2;

    QString scan_sn;


    //测试状态显示
    void test_status_change(QString text, QString bgcolor, QString font);

    //提示信息显示
    void notice_status_display(QString text);

private slots:
//    // 数据触发、接收
//    void displayRxData();

    void timerUpDate_read_sn();

//    // 串口开关
//    void on_pushButton_com_open_clicked();
//    void on_pushButton_com_close_clicked();
//    void on_pushButton_com_scan_clicked();

    //http
    void replyFinished(QNetworkReply* reply);
    void on_readyRead();

    //printer
    void slotPrint (QString data);

private:
    Ui::MainWindow *ui;

    int g_is_testing;               //0:未测试 1：正在测试
    int sn_scanned_num;             //0:non   1:RCar  2:BCar
    int g_fail_num;                 //失败后累加

    //需启动的外部exe文件的路径
    QString ExeRoute;
    //生成的彩盒码txt文件的路径
    QString TxtRoute;
    //SN码提交的目标服务器的url
    QString UrlServer;
    //.BTW File Name
    QString BTWFileName;
    //Lable Printer Name
    QString PrinterName;

    void test_begin(QString SN);

    //从config.ini文件中读取配置信息
    void readConfig();

    QTimer timer_read_sn;
};

#endif // MAINWINDOW_H
