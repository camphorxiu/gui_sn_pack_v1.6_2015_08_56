#ifndef CLASS_STRING_H
#define CLASS_STRING_H

#include <QString>

class class_string
{
public:
    class_string();

    static QByteArray hexStringtoByteArray(QString hex);

    static QString hexDataToString(QByteArray hexData);

    static QString hexQStringDataToString(QString hexData);
};

#endif // CLASS_STRING_H
