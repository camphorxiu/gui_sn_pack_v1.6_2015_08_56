#ifndef CLASS_SQLITE_H
#define CLASS_SQLITE_H

#include <QObject>

struct sql_table2_statistic_data {
    int num_total;              //已测总数
    int num_real;               //实测数
    int num_pass;               //已通过数
    int num_not_pass;           //未通过数
};


class class_sqlite : public QObject
{
    Q_OBJECT
public:
    explicit class_sqlite(QObject *parent = 0);

    bool sql_connect(const QString &dbName);

    //数据库单板详细点测表
    bool sql_save_table1(QString sn,  QVariantList descs,  QVariantList scopes,
                   QVariantList tvs, QVariantList statuss);

    //数据库多板点测表
    bool sql_save_table2(QString sn, QString status, QVariantList tvs);
    //查询多板点测表，取出统计数据
    bool sql_query_table2(struct sql_table2_statistic_data *data);


    //统计测试点取值范围
    bool sql_save_table3(QVariantList tvs);




signals:

public slots:

};

#endif // CLASS_SQLITE_H
