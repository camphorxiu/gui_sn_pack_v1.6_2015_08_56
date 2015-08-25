#include "class_string.h"

#include <QStringList>

class_string::class_string()
{

}

/*************************************************
Function: formatString()
Description: 将十六进制字串每字节中间加空格分隔
Calls:
Called By:hexStringtoByteArray()
Input: org->待处理的字串
       n->间隔数默认为2
       ch->分隔标志，在此取空格
Output: NULL
Return: void
Others: NULL
*************************************************/
void formatString(QString &org, int n=2, const QChar &ch=QChar(' '))
{
    int size= org.size();
    int space= qRound(size*1.0/n+0.5)-1;
    if(space<=0)
        return;
    for(int i=0,pos=n;i<space;++i,pos+=(n+1))
    {
        org.insert(pos,ch);
    }
}

/*************************************************
Function: hexStringtoByteArray()
Description: 十六进制字串转化为十六进制编码
Calls: formatString()
Called By:
Input: hex->待转化的十六进制字串
Output: NULL
Return: QByteArray
Others: NULL
*************************************************/
QByteArray class_string::hexStringtoByteArray(QString hex)
{
    QByteArray ret;
    hex=hex.trimmed();
    formatString(hex,2,' ');
    QStringList sl=hex.split(" ");
    foreach(QString s,sl)
    {
        if(!s.isEmpty())
            ret.append((char)s.toInt(0,16)&0xFF);
    }
    return ret;
}

/*************************************************
Function: hexDataToString()
Description: 十六进制数转化为ASCII编码
Calls:
Called By:
Input: hex->待转化的十六进制数字
Output: NULL
Return: QString
Others: NULL
*************************************************/
QString class_string::hexDataToString(QByteArray hexData)
{
    QString msg;

    for (int i = 0; i < hexData.size(); i++)
    {
        qint8 outChar = hexData.data()[i];
        //这里前面是要转换的字符，后面是转换的长度为2，第三个参数是转成16进制的意思，最后一个参数是长度不够填充的字符
        QString str = QString("%1").arg(outChar&0xff, 2, 16, QLatin1Char('0'));
        msg += str;
    }

    return msg;
}

/*************************************************
Function: hexQStringDataToString()
Description: 十六进制数转化为ASCII编码
Calls:
Called By:
Input: hex->待转化的十六进制数字
Output: NULL
Return: QString
Others: NULL
*************************************************/
QString class_string::hexQStringDataToString(QString hexData)
{
    QString msg;

    for (int i = 0; i < hexData.size(); i++)
    {
        qint8 outChar = hexData.data()[i].toLatin1();
        //这里前面是要转换的字符，后面是转换的长度为2，第三个参数是转成16进制的意思，最后一个参数是长度不够填充的字符
        QString str = QString("%1").arg(outChar&0xff, 2, 16, QLatin1Char('0'));
        msg += str;
    }

    return msg;
}
