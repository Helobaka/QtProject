#ifndef DATABASEPSQL_H
#define DATABASEPSQL_H

#include <QSqlRelationalTableModel>

class DataBasePSQL{
protected:
    static DataBasePSQL* _self;
    DataBasePSQL();
    ~DataBasePSQL();
public:
    static DataBasePSQL* Instance();
    static bool DeleteInstance();
    QSqlDatabase getDB();
private:
    QSqlDatabase db;
};

#endif // DATABASEPSQL_H
