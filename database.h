#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DATABASE_NAME "BD_Disney"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool openDatabase();
    void closeDatabase();
    bool restoreDatabase();

private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
