#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DATABASE_FILENAME   "rxr.sqlite"

class Database
{
public:
    Database();
    ~Database();

private:
    QSqlDatabase conn;
    bool active_connection;
};

#endif // DATABASE_H
