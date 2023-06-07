#include "database.h"
#include <QDebug>

Database::Database()
{

}

bool Database::openDatabase()
{
    qDebug() << "J'ouvre la bd" << Qt::endl;
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);

    return (mydb.open());
}

void Database::closeDatabase()
{
    qDebug() << "Je ferme la bd" << Qt::endl;
    mydb.close();
}

bool Database::restoreDatabase()
{
    qDebug() << "La base de données existe" << Qt::endl;
     //Tentative de créer la table
    return false;
}
