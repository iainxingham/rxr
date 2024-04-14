#include "database.h"

Database::Database()
{
    conn = QSqlDatabase::addDatabase("QSQLITE");
    conn.setDatabaseName(DATABASE_FILENAME);
    active_connection = conn.open();
}

Database::~Database()
{
    if(active_connection) conn.close();
}
