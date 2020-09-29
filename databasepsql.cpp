#include "databasepsql.h"

DataBasePSQL* DataBasePSQL ::_self = 0;

DataBasePSQL::DataBasePSQL(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5433);
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12347");
    db.open();
}

DataBasePSQL::~DataBasePSQL(){
    if(db.isOpen())
        db.close();
}

DataBasePSQL* DataBasePSQL::Instance()
{
    if(!_self){
        _self = new DataBasePSQL();
    }
    return _self;
}

bool DataBasePSQL::DeleteInstance(){
    if(_self)
    {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}

QSqlDatabase DataBasePSQL::getDB(){
    return db;
}
