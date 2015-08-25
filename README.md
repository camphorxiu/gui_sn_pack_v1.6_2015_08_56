# GUI_SN_PACK 彩盒码包装站上位机程序

## 2015-08-25 @Letain V1.6 

* 因配合 C\D 款试产，彩盒包装程序取消红车、蓝车限制，仅输入8位 SN 号即可；
* 增加 config.ini 配置内容，可配置打印条码模板文件名和打印机名；
* 使用 windeployqt 打包应用程序依赖关系。

## 2015-07-16 @Eppo V1.5.1 

* 因为打印程序设置参数固化在程序中，所以标签名称固定为“彩盒码标签.btw”，并且标签文件必须放在与可执行文件的同级目录中。

## 2015-07-16 @Eppo V1.2

打印程序Bartender检测生成文件并自动打印文件服务过期，
生成彩盒码文件后主动调用外部打印程序并调用其若干参数。
QStringList param;
param.append("/AF=中箱标签6pcs.btw");
param.append("/PRN=TSC TTP-342E Pro");
param.append("/P");
param.append("/X");
QProcess::startDetached(ExeRoute,param);

## 2015-07-02

1. 当部署到win8笔记本时出现src不能运行，提示缺少*.dll，
在该台笔记本上装上QT后此问题解决；
2. 当发送HttpRequest时出现QSslSocket:cannot resolve TLSv1_1_client_method的问题，暂时还没有解决


## 2015-07-01 @Eppo V1.5

添加部署所需的.dll文件
文件夹ColorBoxCodeGen_v1.5为部署好的文件夹

paul-v1.2
---
为配合工厂部署软件版本管理(工厂部署版本叫v1.4),
强行从分支eppo-v1.2分出分支eppo-v1.4。
代码没有任何改变。

## 2015-06-30

需求：
添加功能：
添加外部可配置文件，使若干选项对用户可配置化
1.将启动的外部可执行程序可配置化；
2.将彩盒码的生成路径可配置化；
3.将SN码提交的目标服务器url可配置化。

## 2015-06-25 @Eppo V1.2:

需求：
之前版本生成的彩盒码打印是调用BarTender程序的Commander组件直接打印，
但是因为Commander无破解版本，在试用1个月后过期。
所以这次改由彩盒码上位机直接运行BarTender主程序打印。

描述说明

修改原Commander 服务触发 Bartender 主程序打印的流程为直接运行Bartender 主程序打印；
上位机程序调用指定快捷方式，Bartender 运行参数在上位机程序部署时做预配置。
原彩盒码/中箱码保存文件由 .md 改为 .txt （不再由 Commander 服务触发修改）；
附：程序调用参数说明
"[Bartender 主程序 bartender.exe]" /AF="[打印标签模版 *.btw]" /PRN="[打印机名称]" /P
如："C:\Program Files (x86)\Seagull\BarTender Suite\bartend.exe"

测试SN码：
红车：0x01803803
蓝车：0x02815815

更改：

1. 生成的文件由于不需要Commander调用，所以改为.txt文件类型；
2. 生成.txt文件后启动软件IAR，"C:/Program Files (x86)/IAR Systems/Embedded
  Workbench 6.4/common/bin/IarIdePm.exe"；
3. 添加整个程序流程图。

## 2015-05-13 @Eppo V1.1-Font 

软件界面字体（大小，颜色）的设置：

1. 各个控件（QLabel,QPlainTextEdit）下整体的字体（大小，颜色）直接在ui编辑器中设置；
2. 控件下单个字符的字体（大小，颜色）可通过嵌入html语句实现。

## 2015-05-12

需求：

1. 添加对删除前一次生成的.txt文件的动作结果进行判断，若删除失败则弹出提示框提示用户手动删除；
2. 去掉2000ms后显示前一次SN码区域清除的动作，以便用户可以人工比对SN码；
3. 运行程序后默认全屏，并居中排版；
4. 主提示框区域去掉红色/蓝色背景，转为将“红车”/“蓝车”两字的颜色改为红色/蓝色；
5. 下部分提示框内的字体放大；
6. 最终检测成功/失败时整个背景颜色调整为绿色/红色，以起到明显的指示作用。


