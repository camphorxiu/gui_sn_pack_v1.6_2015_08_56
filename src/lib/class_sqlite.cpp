#include "class_sqlite.h"

#include <QtSql>
#include <QMessageBox>

class_sqlite::class_sqlite(QObject *parent) :
    QObject(parent)
{

}

bool class_sqlite::sql_connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("host");
//    db.setDatabaseName("dbname");
//    db.setUserName("username");
//    db.setPassword("password");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              db.lastError().text());
        return false;
    }
    return true;
}


bool class_sqlite::sql_save_table1(QString sn,  QVariantList descs,  QVariantList scopes,QVariantList tvs, QVariantList statuss)
{
    QSqlQuery query;

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString time_str = time.toString("yyyy-MM-dd_hh:mm:ss"); //设置显示格式
    QString table_name = QString("TABLE_DETAIL_%1").arg(sn);

    QString create = QString("CREATE TABLE if not exists '%1'(id INTEGER PRIMARY KEY AUTOINCREMENT, desc VARCHAR, scope VARCHAR, tv INTEGER, status VARCHAR)").arg(table_name);
    if (!query.exec(create)) {
        QMessageBox::critical(0, QObject::tr("Database Create Error"),query.lastError().text());
        return false;
    }

    QString insert = QString("INSERT INTO '%1' (desc, scope, tv, status) VALUES (:desc, :scope, :tv, :status)").arg(table_name);
    query.prepare(insert);

    query.bindValue(":desc", descs);
    query.bindValue(":scope", scopes);
    query.bindValue(":tv", tvs);
    query.bindValue(":status", statuss);

    if (!query.execBatch()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),query.lastError().text());
        return false;
    }

    query.finish();



//    QString select = QString("SELECT desc, scope, tv, status FROM '%1'").arg(table_name);
//    query.exec(select);
//    while (query.next()) {
//        QString desc = query.value(0).toString();
//        QString scope = query.value(1).toString();
//        int tv = query.value(2).toInt();
//        QString status = query.value(3).toString();
//        qDebug() << desc << ": " << scope << ": " << tv << ": " << status;
//    }

    return true;
}


//存储点测电压
bool class_sqlite::sql_save_table2(QString sn, QString status,  QVariantList tvs)
{
    QString table_name = "TABLE_VOL_STATISTICAL";

    QDateTime time = QDateTime::currentDateTime();//获取系统当前时间
    QString time_str = time.toString("yyyy-MM-dd_hh:mm:ss"); //设置显示格式

    QSqlQuery query;
    QString create = QString("CREATE TABLE if not exists '%1'(id INTEGER PRIMARY KEY AUTOINCREMENT, sn VARCHAR, status VARCHAR, \
                             tp0 INTEGER, tp1 INTEGER,tp2 INTEGER,tp3 INTEGER,tp4 INTEGER,tp5 INTEGER, tp6 INTEGER,tp7 INTEGER,\
                             tp8 INTEGER,tp9 INTEGER,tp10 INTEGER,tp11 INTEGER,tp12 INTEGER,tp13 INTEGER,tp14 INTEGER,\
                             tp15 INTEGER,tp16 INTEGER,tp17 INTEGER,tp18 INTEGER,tp19 INTEGER,tp20 INTEGER,tp21 INTEGER,\
                             time VARCHAR)").arg(table_name);

    if (!query.exec(create)) {
        QMessageBox::critical(0, QObject::tr("Database Create Error"),query.lastError().text());
        return false;
    }


    QString insert = QString("INSERT INTO '%1' (sn,  status,  \
                                                tp0, tp1, tp2, tp3, tp4, tp5, tp6, tp7, tp8, tp9, tp10, tp11, \
                                                tp12, tp13, tp14, tp15, tp16, tp17, tp18, tp19, tp20, tp21,\
                                                time) \
                                                VALUES (:sn,:status, :tp0, :tp1, :tp2, :tp3,:tp4,:tp5,:tp6,:tp7,:tp8,:tp9,:tp10,\
                                                        :tp11,:tp12,:tp13,:tp14,:tp15,:tp16,:tp17,:tp18,:tp19,:tp20,:tp21,\
                                                        :time)").arg(table_name);
    query.prepare(insert);

    query.bindValue(":sn", sn);
    query.bindValue(":status", status);

    for(int i = 0; i < tvs.size(); i++) {
        query.bindValue(":tp" + QString::number(i, 10), tvs.at(i).toInt());
    }
    query.bindValue(":time", time_str);

    if (! query.exec()) {
        QMessageBox::critical(0, QObject::tr("Database exec Error"),query.lastError().text());
        return false;
    }

    return true;
}

//存储点测电压
bool class_sqlite::sql_save_table3(QVariantList tvs)
{
    QString table_name = "TABLE_TEST_VOL";

    QDateTime time = QDateTime::currentDateTime();//获取系统当前时间
    QString time_str = time.toString("yyyy-MM-dd_hh:mm:ss"); //设置显示格式

    QSqlQuery query;
    QString create = QString("CREATE TABLE if not exists '%1'(id INTEGER PRIMARY KEY AUTOINCREMENT,\
                             tp0 INTEGER, tp1 INTEGER,tp2 INTEGER,tp3 INTEGER,tp4 INTEGER,tp5 INTEGER, tp6 INTEGER,tp7 INTEGER,\
                             tp8 INTEGER,tp9 INTEGER,tp10 INTEGER,tp11 INTEGER,tp12 INTEGER,tp13 INTEGER,tp14 INTEGER,\
                             tp15 INTEGER,tp16 INTEGER,tp17 INTEGER,tp18 INTEGER,tp19 INTEGER,tp20 INTEGER,tp21 INTEGER,\
                             time VARCHAR)").arg(table_name);

    if (!query.exec(create)) {
        QMessageBox::critical(0, QObject::tr("Database Create Error"),query.lastError().text());
        return false;
    }


    QString insert = QString("INSERT INTO '%1' (tp0, tp1, tp2, tp3, tp4, tp5, tp6, tp7, tp8, tp9, tp10, tp11, \
                                                tp12, tp13, tp14, tp15, tp16, tp17, tp18, tp19, tp20, tp21,\
                                                time) \
                                                VALUES ( :tp0, :tp1, :tp2, :tp3,:tp4,:tp5,:tp6,:tp7,:tp8,:tp9,:tp10,\
                                                        :tp11,:tp12,:tp13,:tp14,:tp15,:tp16,:tp17,:tp18,:tp19,:tp20,:tp21,\
                                                        :time)").arg(table_name);
    query.prepare(insert);

    for(int i = 0; i < tvs.size(); i++) {
        query.bindValue(":tp" + QString::number(i, 10), tvs.at(i));
    }
    query.bindValue(":time", time_str);

    if (! query.exec()) {
        QMessageBox::critical(0, QObject::tr("Database exec Error"),query.lastError().text());
        return false;
    }

    return true;
}


//查询表2，得出统计数据
bool class_sqlite::sql_query_table2(struct sql_table2_statistic_data *data)
{
  QString table_name = "TABLE_VOL_STATISTICAL";

  QSqlQuery query;

  //总测试数
  QString select = QString("select * from %1").arg(table_name);
  if(query.exec(select)){

  }else{
    qDebug()<<"could not query!"<<endl;
  }
  query.last();
  data->num_total = query.at() + 1;
  qDebug() <<"num_total = " << data->num_total;


  //实测数
  select = QString("select distinct sn from %1").arg(table_name);   //去重查询
  if(query.exec(select)){

  }else{
    qDebug()<<"could not query!"<<endl;
  }

  query.last();
  data->num_real = query.at() + 1;
  qDebug() <<"num_real = " << data->num_real;

  //通过数
  select = QString("select distinct sn from %1 where status=\"ok\" ").arg(table_name);
  if(query.exec(select)){

  }else{
    qDebug()<<"could not query!"<<endl;
  }
  query.last();
  if (query.at() == QSql::AfterLastRow) {
    data->num_pass = 0;
  } else {
    data->num_pass = query.at() + 1;
  }
  qDebug() <<"num_pass = " << data->num_pass;

  //未通过数
  select = QString("select distinct sn from %1 where status=\"fail\" ").arg(table_name);
  if(query.exec(select)){

  }else{
    qDebug()<<"could not query!"<<endl;
  }
  query.last();
  data->num_not_pass = query.at() + 1;
  qDebug() <<"num_not_pass = " << data->num_not_pass;


    while (query.next()){
        qDebug()<<""<<query.value(0).toString()<<""<<query.value(1).toString()<<""<<query.value(2).toString()<<""<<query.value(3).toString()<<""<<query.value(4).toString()<<endl;
    }
}


//main ()
//{
//   //add QSQLITE driver
//   QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//   // if not exist, will create a new one
//   db.setDatabaseName("data.db");
//   if(!db.open()){
//       qDebug()<<"Could not open file!"<<endl;
//       QMessageBox::critical(0, QObject::tr("Database Error"),
//                                     db.lastError().text());
//       return -1;
//   }else{
//       qDebug()<<"Open file: "<<db.databaseName()<<" sucessfully!"<<endl;
//   }
//   // create a new table
//   QSqlQuery query;
//   if(query.exec("create table if not exists product (type TEXT, para1 REAL, para2 REAL, para3 REAL, timestamp NOT NULL DEFAULT  (datetime('now','localtime')))")){
//       qDebug()<<"creat table: product successfully!"<<endl;
//   }else{
//       qDebug()<<"could not creat table: product!"<<endl;
//   }
//   //insert product1
//   if(query.exec(" insert into product(type, para1, para2, para3)  values ('SN001', 30.00,10.00, 20.00)")){
//       qDebug()<<"insert  product successfully!"<<endl;
//   }else{
//       qDebug()<<"could not insert product!"<<endl;
//   }
//   //insert product2
//   if(query.exec("insert into product(type, para1, para2, para3)  values ('SN002', 29.01,15.00, 18.00)")){
//       qDebug()<<"insert  product successfully!"<<endl;
//   }else{
//       qDebug()<<"could not insert product!"<<endl;
//   }
//   //insert product3
//   if(query.exec("insert into product(type, para1, para2, para3)  values ('SN003', 35.10,10.01, 20.0111)")){
//       qDebug()<<"insert  product successfully!"<<endl;
//   }else{
//       qDebug()<<"could not insert product!"<<endl;
//   }
//   //query all data
//   if(query.exec("select * from product")){
//       qDebug()<<"begin query all!"<<endl;
//   }else{
//       qDebug()<<"could not query!"<<endl;
//   }
//   //output result
//   while (query.next()){
//       qDebug()<<""<<query.value(0).toString()<<""<<query.value(1).toString()<<""<<query.value(2).toString()<<""<<query.value(3).toString()<<""<<query.value(4).toString()<<endl;
//   }
//   db.close();

//}
