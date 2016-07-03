#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QtSql>
#include "databasetable.h"





class DBManager
{    
public:
    DBManager();

    void Init();

    void SetDbFilename( const QString& _filename );


    QStringList SelectAllSubTable( ENUM_DB_TABLES _table );

    void InsertSubTable( ENUM_DB_TABLES _table, const QString & _id, const QString & _value );

    void DeleteSubTable( ENUM_DB_TABLES _table, const QString & _value );

    void UpdateSubTable( ENUM_DB_TABLES _table, const QString & _id, const QString & _value );

    QString GetTableName( ENUM_DB_TABLES _table );

    static QString GetTagName( ENUM_DB_TABLES _table );




private:
    void InitDbTables();

    void CreateTables();



private:
    QSqlDatabase * m_db;
    QTextCodec *   m_codec;
    QString        m_dbFilename;

    DB_TABLE_CLIENT      m_dbTableClient;
    DB_TABLE_OPERATION   m_dbTableOperation;
    DB_TABLE_CURL        m_dbTableCurl;
    DB_TABLE_TYPE        m_dbTableType;
    DB_TABLE_COLOR       m_dbTableColor;
    DB_TABLE_LENGTH      m_dbTableLength;
    DB_TABLE_NUMBER      m_dbTableNumber;
    DB_TABLE_CONTACT     m_dbTableContact;
};

#endif // DBMANAGER_H
