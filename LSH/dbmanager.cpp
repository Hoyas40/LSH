#include "dbmanager.h"
#include <algorithm>

#include <QTextCodec>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QFile>
#include <QMessageBox>


#include <QDebug>


DBManager::DBManager()
    : m_db( nullptr )
    , m_codec( nullptr )
{
    QDir dir;
    SetDbFilename( dir.currentPath() + QString("/db.db") );
}

void DBManager::Init()
{
    qDebug() << __FUNCTION__;


    if( m_db == nullptr )
    {
        m_db = new QSqlDatabase( QSqlDatabase::addDatabase("QSQLITE") );

        m_db->setDatabaseName( m_dbFilename );


        if( !m_db->open() )
        {
            // show error message
            // quit the application
            QString msg = QString("Database file cannot be opened, %1").arg( m_db->lastError().text() );
            QMessageBox::critical( NULL , "Error", msg, QMessageBox::Ok );
            exit( 0 );
        }

        CreateTables();
    }
}

void DBManager::SetDbFilename(const QString &_filename)
{
    m_dbFilename = _filename;
    qDebug() << __FUNCTION__ << " |  Db file : " <<  m_dbFilename;
}

QStringList DBManager::SelectAllSubTable(ENUM_DB_TABLES _table)
{
    qDebug() << __FUNCTION__;

    QStringList res;
    if( _table == TABLE_CLIENT || _table == TABLE_OPERATION || _table == TABLE_NONE )
        return QStringList();


    QString tableName = GetTableName( _table );
    if( false == tableName.isEmpty() )
    {
        QSqlQuery query;
        QString queryStr = QString( "SELECT * FROM %1" ).arg( tableName );
        query.prepare( queryStr );
        query.exec();

        while( query.next() )
        {
            QString tmp = QString( "%1|%2" ).arg( query.value(0).toString() ).arg( query.value(1).toString() );
            res << tmp;
        }
    }

    return res;

}

QString DBManager::SelectSubTableWithId(ENUM_DB_TABLES _table, const QString &_value)
{
    QString res;

    QString tableName = GetTableName( _table );
    if( false == tableName.isEmpty() )
    {
        QSqlQuery query;
        QString queryStr = QString( "SELECT * FROM %1 WHERE ID = '%2'" ).arg( tableName ).arg( _value );
        query.prepare( queryStr );
        query.exec();

        while( query.next() )
        {
            res = QString( "%1|%2" ).arg( query.value(0).toString() ).arg( query.value(1).toString() );
        }
    }

    return res;
}

void DBManager::InsertSubTable(ENUM_DB_TABLES _table, const QString &_id, const QString & _name )
{
    if( _table == TABLE_CLIENT || _table == TABLE_OPERATION || _table == TABLE_NONE )
        return;

    QString tableName = GetTableName( _table );

    if( false == tableName.isEmpty() )
    {        

        QSqlQuery query;
        QString queryStr = QString("INSERT INTO %1 VALUES( '%2', '%3' )").arg( tableName ).arg( _id ).arg( _name  );
        query.prepare( queryStr );
        query.exec();
    }
}

void DBManager::DeleteSubTable(ENUM_DB_TABLES _table, const QString &_value )
{
    if( _table == TABLE_CLIENT || _table == TABLE_OPERATION || _table == TABLE_NONE )
        return;

    QString tableName = GetTableName( _table );

    if( false == tableName.isEmpty() )
    {
        QSqlQuery query;
        QString queryStr = QString("DELETE FROM %1 WHERE ID = '%2'").arg( tableName ).arg( _value );
        query.prepare( queryStr );
        query.exec();
    }
}

void DBManager::UpdateSubTable(ENUM_DB_TABLES _table, const QString &_id, const QString &_value)
{
    if( _table == TABLE_CLIENT || _table == TABLE_OPERATION || _table == TABLE_NONE )
        return;

    QString tableName = GetTableName( _table );

    if( false == tableName.isEmpty() )
    {
        QSqlQuery query;
        QString queryStr = QString("UPDATE %1 SET NAME = '%3' WHERE ID = '%2'").arg( tableName ).arg( _id ).arg( _value  );
        query.prepare( queryStr );
        query.exec();
    }
}

QString DBManager::GetTableName(ENUM_DB_TABLES _table)
{
    QString tableName = "";

    switch( _table )
    {
        case TABLE_CURL :
            tableName = m_dbTableCurl.tableName;
            break;

        case TABLE_TYPE :
            tableName = m_dbTableType.tableName;
            break;

        case TABLE_COLOR :
            tableName = m_dbTableColor.tableName;
            break;

        case TABLE_LENGTH :
            tableName = m_dbTableLength.tableName;
            break;

        case TABLE_NUMBER :
            tableName = m_dbTableNumber.tableName;
            break;
        case TABLE_CONTACT :
            tableName = m_dbTableContact.tableName;
            break;

        case TABLE_CLIENT :
            tableName = m_dbTableClient.tableName;
            break;

        case TABLE_OPERATION :
            tableName = m_dbTableOperation.tableName;
            break;

    }

    return tableName;
}

QString DBManager::GetTagName(ENUM_DB_TABLES _table)
{
    switch( _table )
    {
        case TABLE_CURL :
            return "CU";

        case TABLE_TYPE :
            return "TY";

        case TABLE_COLOR :
            return "CL";

        case TABLE_LENGTH :
            return "LE";

        case TABLE_NUMBER :
            return "NU";

        case TABLE_CONTACT :
            return "CN";

        default:
            return "";
    }
}

void DBManager::InsertClient(const QString &_name, const QString &_phoneNumber, const QString &_contactWay, const QString &_info)
{
    // get new ID;
    QSqlQuery query;
    QString queryStr = QString( "SELECT %1 FROM %2" ).arg( m_dbTableClient.id.name ).arg( m_dbTableClient.tableName );
    query.prepare( queryStr );
    query.exec();

    int ID = -1;

    while( query.next() )
    {
        int tmpID = query.value(0).toInt();

        ID = std::max( ID, tmpID );
    }

    ID++;

    queryStr = QString("INSERT INTO %1 VALUES( %2, '%3', '%4', '%5', '%6' )").arg( m_dbTableClient.tableName )
            .arg( ID )
            .arg( _name  )
            .arg( _phoneNumber )
            .arg( _contactWay )
            .arg( _info );


    query.prepare( queryStr );
    query.exec();
}

void DBManager::InsertClient(const QString &_id, const QString &_name, const QString &_phoneNumber, const QString &_contactWay, const QString &_info)
{
    QSqlQuery query;
    QString queryStr;

    queryStr = QString("INSERT INTO %1 VALUES( %2, '%3', '%4', '%5', '%6' )").arg( m_dbTableClient.tableName )
            .arg( _id.toInt() )
            .arg( _name  )
            .arg( _phoneNumber )
            .arg( _contactWay )
            .arg( _info );


    query.prepare( queryStr );
    query.exec();
}

void DBManager::InsertOperation(const QString &_clientID,
                                const QString &_dateTime,
                                const QString &_curl,
                                const QString &_type,
                                const QString &_color,
                                const QString &_length,
                                const QString &_number,
                                const QString &_price,
                                const QString& _option )
{
    QSqlQuery query;
    QString queryStr = QString( "SELECT %1 FROM %2" ).arg( m_dbTableOperation.id.name ).arg( m_dbTableOperation.tableName );
    query.prepare( queryStr );
    query.exec();

    int ID = -1;

    while( query.next() )
    {
        int tmpID = query.value(0).toInt();

        ID = std::max( ID, tmpID );
    }

    ID++;


    queryStr = QString("INSERT INTO %1 VALUES( %2, %3, '%4', '%5', '%6', '%7', '%8', '%9', %10, %11 )").arg( m_dbTableOperation.tableName )
            .arg( ID )
            .arg( _clientID.toInt()  )
            .arg( _dateTime )
            .arg( _curl )
            .arg( _type )
            .arg( _color )
            .arg( _length )
            .arg( _number )
            .arg( _price )
            .arg( _option.toInt() );


    query.prepare( queryStr );
    query.exec();
}

void DBManager::InsertOperation(const QString &_ID, const QString &_clientID, const QString &_dateTime, const QString &_curl, const QString &_type, const QString &_color, const QString &_length, const QString &_number, const QString &_price, const QString &_option)
{
    QSqlQuery query;
    QString queryStr;

    queryStr = QString("INSERT INTO %1 VALUES( %2, %3, '%4', '%5', '%6', '%7', '%8', '%9', %10, %11 )").arg( m_dbTableOperation.tableName )
            .arg( _ID.toInt() )
            .arg( _clientID.toInt()  )
            .arg( _dateTime )
            .arg( _curl )
            .arg( _type )
            .arg( _color )
            .arg( _length )
            .arg( _number )
            .arg( _price )
            .arg( _option.toInt() );


    query.prepare( queryStr );
    query.exec();
}

QStringList DBManager::SelectClientAll()
{
    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 ORDER BY %2 ASC" )
            .arg( m_dbTableClient.tableName )
            .arg( m_dbTableClient.name.name );
    query.prepare( queryStr );
    query.exec();

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
        {
            tmp += query.value(i).toString() + "|";
        }
        tmp += query.value( numberColomns - 1).toString();

        res << tmp;
    }

    return res;
}

QStringList DBManager::SelectClientWithName(const QString &_value)
{
    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 WHERE %2 LIKE '%%4%' ORDER BY %3 ASC" )
            .arg( m_dbTableClient.tableName )
            .arg( m_dbTableClient.name.name )
            .arg( m_dbTableClient.name.name )
            .arg(_value);
    query.prepare( queryStr );
    query.exec();
    qDebug() << queryStr;

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
        {
            tmp += query.value(i).toString() + "|";
        }
        tmp += query.value( numberColomns - 1).toString();

        res << tmp;
    }

    return res;

}

QStringList DBManager::SelectClientWithPhoneNumber(const QString &_value)
{
    qDebug() << __FUNCTION__;
    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 WHERE %2 LIKE '%%4%' ORDER BY %3 ASC" )
            .arg( m_dbTableClient.tableName )
            .arg( m_dbTableClient.phoneNumber.name )
            .arg( m_dbTableClient.name.name )
            .arg(_value );

    query.prepare( queryStr );
    query.exec();

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
            tmp += query.value(i).toString() + "|";

        tmp += query.value( numberColomns - 1).toString();

        res << tmp;
    }    


    return res;
}

QString DBManager::SelectClientWithId(const QString &_id)
{
    qDebug() << __FUNCTION__;

    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 WHERE %2 IS %3" )
            .arg( m_dbTableClient.tableName )
            .arg(m_dbTableClient.id.name)
            .arg(_id);
    query.prepare( queryStr );
    query.exec();

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
            tmp += query.value(i).toString() + "|";

        tmp += query.value( numberColomns - 1).toString();

        res << tmp;
    }

    return res[0];
}

void DBManager::UpdateClient(const QString &_id, const QString &_name, const QString &_phoneNumber, const QString &_contactWay, const QString &_info)
{
    QSqlQuery query;
    QString queryStr = QString("UPDATE %1 SET %2 = '%3', %4 = '%5',"
                               "%6 = '%7', %8 = '%9'"
                               "WHERE %10 = %11" )
            .arg( m_dbTableClient.tableName )
            .arg( m_dbTableClient.name.name )
            .arg( _name )
            .arg( m_dbTableClient.phoneNumber.name ) // 04
            .arg( _phoneNumber )
            .arg( m_dbTableClient.contactWay.name )
            .arg( _contactWay )
            .arg( m_dbTableClient.info.name )        // 08
            .arg( _info )
            .arg( m_dbTableClient.id.name )
            .arg( _id );    // 11

    query.prepare( queryStr );
    query.exec();
}

QStringList DBManager::SelectOperationAll()
{
    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1" ).arg( m_dbTableOperation.tableName );
    query.prepare( queryStr );
    query.exec();

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
        {
            tmp += query.value(i).toString() + "|";
        }
        tmp += query.value( numberColomns - 1).toString();

        res << tmp;
    }

    return res;
}

QStringList DBManager::SelectOperationBetweenTwoDates(const QString &_firstTime, const QString &_lastTime)
{
    qDebug() << __FUNCTION__;

    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 WHERE %2 >= datetime('%3') AND %4 <= datetime('%5') ORDER BY %6 ASC" )
            .arg( m_dbTableOperation.tableName )
            .arg( m_dbTableOperation.dateTime.name )
            .arg( _firstTime )
            .arg( m_dbTableOperation.dateTime.name )
            .arg( _lastTime )
            .arg( m_dbTableOperation.dateTime.name );


    query.prepare( queryStr );
    query.exec();

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
            tmp += query.value(i).toString() + "|";

        tmp += query.value( numberColomns - 1).toString();
        res << tmp;
    }

    return res;
}

QStringList DBManager::SelectOperationWithClientID(const QString &_value)
{
    qDebug() << __FUNCTION__;

    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 WHERE %2 = '%3' ORDER BY %4 ASC" )
            .arg( m_dbTableOperation.tableName )
            .arg( m_dbTableOperation.clientId.name )
            .arg( _value )
            .arg( m_dbTableOperation.dateTime.name );


    query.prepare( queryStr );
    query.exec();

    QStringList res;
    int numberColomns = query.record().count();

    while( query.next() )
    {
        QString tmp;

        for( int i = 0; i < numberColomns - 1; ++i )
            tmp += query.value(i).toString() + "|";

        tmp += query.value( numberColomns - 1).toString();
        res << tmp;
    }

    return res;
}

QString DBManager::SelectOperationWithID(const QString &_value)
{
    qDebug() << __FUNCTION__;

    QString queryStr;
    QSqlQuery query;
    queryStr = QString( "SELECT * FROM %1 WHERE %2 = '%3' ORDER BY %4 ASC" )
            .arg( m_dbTableOperation.tableName )
            .arg( m_dbTableOperation.id.name )
            .arg( _value )
            .arg( m_dbTableOperation.dateTime.name );


    query.prepare( queryStr );
    query.exec();

    QString res;
    int numberColomns = query.record().count();

    while( query.next() )
    {

        for( int i = 0; i < numberColomns - 1; ++i )
            res += query.value(i).toString() + "|";

        res += query.value( numberColomns - 1).toString();
    }

    return res;
}

void DBManager::UpdateOperation( const QString& _operationID, const QString &_clientID, const QString &_dateTime, const QString &_curl, const QString &_type, const QString &_color, const QString &_length, const QString &_number, const QString &_price, const QString &_option)
{
    QSqlQuery query;
    QString queryStr = QString("UPDATE %1 SET %2 = %3, %4 = '%5', "
                               "%6 = '%7', %8 = '%9', "
                               "%10 = '%11', %12 = '%13',"
                               "%14 = '%15', %16 = %17,"
                               "%18 = %19 WHERE %20 = %21" )
            .arg( m_dbTableOperation.tableName )
            .arg( m_dbTableOperation.clientId.name )
            .arg( _clientID.toInt() )
            .arg( m_dbTableOperation.dateTime.name )
            .arg( _dateTime )
            .arg( m_dbTableOperation.curl.name ) //6
            .arg( _curl )
            .arg( m_dbTableOperation.type.name )
            .arg( _type )
            .arg( m_dbTableOperation.color.name ) // 10
            .arg( _color )
            .arg( m_dbTableOperation.length.name )
            .arg( _length )
            .arg( m_dbTableOperation.number.name ) // 14
            .arg( _number )
            .arg( m_dbTableOperation.price.name )
            .arg( _price )
            .arg( m_dbTableOperation.shown.name ) // 18
            .arg( _option.toInt() )
            .arg( m_dbTableOperation.id.name )  // 20
            .arg( _operationID );

    query.prepare( queryStr );
    query.exec();
}

void DBManager::DeleteOperation(const QString &_operationId)
{
    QSqlQuery query;
    QString queryStr = QString("DELETE FROM %1 WHERE %2 = %3")
            .arg( m_dbTableOperation.tableName )
            .arg( m_dbTableOperation.id.name )
            .arg( _operationId );
    query.prepare( queryStr );
    query.exec();
}

void DBManager::DeleteClient(const QString &_clientId)
{
    // extra work
    // delete all operations of this client!!!

    QStringList queryRes = SelectOperationWithClientID( _clientId );

    foreach( const QString& str, queryRes )
    {
        QStringList itemList = str.split('|');

        QString operationID = itemList[0];

        DeleteOperation( operationID );
    }


    QSqlQuery query;
    QString queryStr = QString("DELETE FROM %1 WHERE %2 = %3")
            .arg( m_dbTableClient.tableName )
            .arg( m_dbTableClient.id.name )
            .arg( _clientId );
    query.prepare( queryStr );
    query.exec();
}

void DBManager::DeleteAllTable()
{
    QSqlQuery query;
    QString queryStr;

    // client
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableClient.tableName );
    query.prepare( queryStr );
    query.exec();

    // operation
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableOperation.tableName );
    query.prepare( queryStr );
    query.exec();

    // curl
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableCurl.tableName );
    query.prepare( queryStr );
    query.exec();

    // type
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableType.tableName );
    query.prepare( queryStr );
    query.exec();

    // color
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableColor.tableName );
    query.prepare( queryStr );
    query.exec();

    // length
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableLength.tableName );
    query.prepare( queryStr );
    query.exec();

    // number
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableNumber.tableName );
    query.prepare( queryStr );
    query.exec();

    // contact way
    queryStr = QString("DELETE FROM %1")
            .arg( m_dbTableContact.tableName );
    query.prepare( queryStr );
    query.exec();
}



void DBManager::InitDbTables()
{
    // client table
    m_dbTableClient.tableName   = QString( "CLIENT" );
    m_dbTableClient.id          = DB_TABLE_ITEM( "CLIENT_ID",           "INTEGER",     "PRIMARY KEY NOT NULL" );
    m_dbTableClient.name        = DB_TABLE_ITEM( "CLIENT_NAME",         "VARCHAR(20)", "NOT NULL" );
    m_dbTableClient.phoneNumber = DB_TABLE_ITEM( "CLIENT_PHONE_NUMBER", "VARCHAR(15)", "NOT NULL" );
    m_dbTableClient.contactWay  = DB_TABLE_ITEM( "CLIENT_CONTACY_WAY",  "VARCHAR(10)" );
    m_dbTableClient.info        = DB_TABLE_ITEM( "CLIENT_INFO",  "VARCHAR(100)" );
//    m_dbTableClient.hairLength  = DB_TABLE_ITEM( "CLIENT_HAIR_LENGTH",  "VARCHAR(10)" );
//    m_dbTableClient.hairNumber  = DB_TABLE_ITEM( "CLIENT_HAIR_NUMBER",  "VARCHAR(10)" );
//    m_dbTableClient.hairSag     = DB_TABLE_ITEM( "CLIENT_HAIR_SAG",     "VARCHAR(10)" );
//    m_dbTableClient.hairDamage  = DB_TABLE_ITEM( "CLIENT_HAIR_DAMAGE",  "VARCHAR(10)" );


    // operation table
    m_dbTableOperation.tableName = QString( "OPERATION" );
    m_dbTableOperation.id        = DB_TABLE_ITEM( "OP_ID",       "INTEGER",      "PRIMARY KEY NOT NULL");
    m_dbTableOperation.clientId  = DB_TABLE_ITEM( "CLIENT_ID",   "INTEGER",      "NOT NULL" );
    m_dbTableOperation.dateTime  = DB_TABLE_ITEM( "OP_DATETIME", "TEXT",         "NOT NULL" );
    m_dbTableOperation.curl      = DB_TABLE_ITEM( "OP_CURL",     "VARCHAR(10)" );
    m_dbTableOperation.type      = DB_TABLE_ITEM( "OP_TYPE",     "VARCHAR(10)" );
    m_dbTableOperation.color     = DB_TABLE_ITEM( "OP_COLOR",    "VARCHAR(10)" );
    m_dbTableOperation.length    = DB_TABLE_ITEM( "OP_LENGTH",   "VARCHAR(10)" );
    m_dbTableOperation.number    = DB_TABLE_ITEM( "OP_NUMBER",   "VARCHAR(10)" );
    //m_dbTableOperation.style     = DB_TABLE_ITEM( "OP_STYLE",    "VARCHAR(10)" );
    m_dbTableOperation.price     = DB_TABLE_ITEM( "OP_PRICE",    "INTEGER" );
    m_dbTableOperation.shown     = DB_TABLE_ITEM( "OP_SHOWN",    "INTEGER" );


    // curl table
    m_dbTableCurl.tableName = QString( "CURL" );
    m_dbTableCurl.id   = DB_TABLE_ITEM( "ID",   "VARCHAR(10)",   "PRIMARY KEY NOT NULL" );
    m_dbTableCurl.name = DB_TABLE_ITEM( "NAME", "VARCHAR(30)",  "NOT NULL" );


    // type table
    m_dbTableType.tableName = QString( "TYPE" );
    m_dbTableType.id   = DB_TABLE_ITEM( "ID",   "VARCHAR(10)",  "PRIMARY KEY NOT NULL" );
    m_dbTableType.name = DB_TABLE_ITEM( "NAME", "VARCHAR(30)", "NOT NULL" );


    // color table
    m_dbTableColor.tableName = QString( "COLOR" );
    m_dbTableColor.id   = DB_TABLE_ITEM( "ID",   "VARCHAR(10)",  "PRIMARY KEY NOT NULL" );
    m_dbTableColor.name = DB_TABLE_ITEM( "NAME", "VARCHAR(30)", "NOT NULL" );


    // length table
    m_dbTableLength.tableName = QString( "LENGTH" );
    m_dbTableLength.id   = DB_TABLE_ITEM( "ID",   "VARCHAR(10)",  "PRIMARY KEY NOT NULL" );
    m_dbTableLength.name = DB_TABLE_ITEM( "NAME", "VARCHAR(30)", "NOT NULL" );


    // number table
    m_dbTableNumber.tableName = QString( "NUMBER" );
    m_dbTableNumber.id   = DB_TABLE_ITEM( "ID",   "VARCHAR(10)",  "PRIMARY KEY NOT NULL" );
    m_dbTableNumber.name = DB_TABLE_ITEM( "NAME", "VARCHAR(30)", "NOT NULL" );


    // contact way table
    m_dbTableContact.tableName = QString( "CONTACT" );
    m_dbTableContact.id   = DB_TABLE_ITEM( "ID",   "VARCHAR(10)",  "PRIMARY KEY NOT NULL" );
    m_dbTableContact.name = DB_TABLE_ITEM( "NAME", "VARCHAR(30)", "NOT NULL" );
}




void DBManager::CreateTables()
{
    qDebug() << __FUNCTION__;

    InitDbTables();


    if( m_db == nullptr )
        return;


    QSqlQuery query;

    QString queryStr;

    // client table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableClient.tableName )
                                                                     .arg( m_dbTableClient.id.name )
                                                                     .arg( m_dbTableClient.id.type )
                                                                     .arg( m_dbTableClient.id.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableClient.name.name )
            .arg( m_dbTableClient.name.type )
            .arg( m_dbTableClient.name.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableClient.phoneNumber.name )
            .arg( m_dbTableClient.phoneNumber.type )
            .arg( m_dbTableClient.phoneNumber.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableClient.contactWay.name )
            .arg( m_dbTableClient.contactWay.type )
            .arg( m_dbTableClient.contactWay.extra );
    queryStr += QString( "%1 %2 %3) " ).arg( m_dbTableClient.info.name )
            .arg( m_dbTableClient.info.type )
            .arg( m_dbTableClient.info.extra );


//    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableClient.hairLength.name )
//            .arg( m_dbTableClient.hairLength.type )
//            .arg( m_dbTableClient.hairLength.extra );
//    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableClient.hairNumber.name )
//            .arg( m_dbTableClient.hairNumber.type )
//            .arg( m_dbTableClient.hairNumber.extra );
//    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableClient.hairSag.name )
//            .arg( m_dbTableClient.hairSag.type )
//            .arg( m_dbTableClient.hairSag.extra );
//    queryStr += QString( "%1 %2 %3) " ).arg( m_dbTableClient.hairDamage.name )
//            .arg( m_dbTableClient.hairDamage.type )
//            .arg( m_dbTableClient.hairDamage.extra );


    query.prepare( queryStr );
    query.exec();


    // operation table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableOperation.tableName )
                                                                     .arg( m_dbTableOperation.id.name )
                                                                     .arg( m_dbTableOperation.id.type )
                                                                     .arg( m_dbTableOperation.id.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.clientId.name )
            .arg( m_dbTableOperation.clientId.type )
            .arg( m_dbTableOperation.clientId.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.dateTime.name )
            .arg( m_dbTableOperation.dateTime.type )
            .arg( m_dbTableOperation.dateTime.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.curl.name )
            .arg( m_dbTableOperation.curl.type )
            .arg( m_dbTableOperation.curl.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.type.name )
            .arg( m_dbTableOperation.type.type )
            .arg( m_dbTableOperation.type.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.color.name )
            .arg( m_dbTableOperation.color.type )
            .arg( m_dbTableOperation.color.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.length.name )
            .arg( m_dbTableOperation.length.type )
            .arg( m_dbTableOperation.length.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.number.name )
            .arg( m_dbTableOperation.number.type )
            .arg( m_dbTableOperation.number.extra );
//    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.style.name )
//            .arg( m_dbTableOperation.style.type )
//            .arg( m_dbTableOperation.style.extra );
    queryStr += QString( "%1 %2 %3, " ).arg( m_dbTableOperation.price.name )
            .arg( m_dbTableOperation.price.type )
            .arg( m_dbTableOperation.price.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableOperation.shown.name )
            .arg( m_dbTableOperation.shown.type )
            .arg( m_dbTableOperation.shown.extra );


    query.prepare( queryStr );
    query.exec();


    // curl table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableCurl.tableName )
                                                                     .arg( m_dbTableCurl.id.name )
                                                                     .arg( m_dbTableCurl.id.type )
                                                                     .arg( m_dbTableCurl.id.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableCurl.name.name )
            .arg( m_dbTableCurl.name.type )
            .arg( m_dbTableCurl.name.extra );


    query.prepare( queryStr );
    query.exec();



    // type table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableType.tableName )
                                                                     .arg( m_dbTableType.id.name )
                                                                     .arg( m_dbTableType.id.type )
                                                                     .arg( m_dbTableType.id.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableType.name.name )
            .arg( m_dbTableType.name.type )
            .arg( m_dbTableType.name.extra );


    query.prepare( queryStr );
    query.exec();


    // color table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableColor.tableName )
                                                                     .arg( m_dbTableColor.id.name )
                                                                     .arg( m_dbTableColor.id.type )
                                                                     .arg( m_dbTableColor.id.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableColor.name.name )
            .arg( m_dbTableColor.name.type )
            .arg( m_dbTableColor.name.extra );


    query.prepare( queryStr );
    query.exec();



    // length table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableLength.tableName )
                                                                     .arg( m_dbTableLength.id.name )
                                                                     .arg( m_dbTableLength.id.type )
                                                                     .arg( m_dbTableLength.id.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableLength.name.name )
            .arg( m_dbTableLength.name.type )
            .arg( m_dbTableLength.name.extra );


    query.prepare( queryStr );
    query.exec();


    // number table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableNumber.tableName )
                                                                     .arg( m_dbTableNumber.id.name )
                                                                     .arg( m_dbTableNumber.id.type )
                                                                     .arg( m_dbTableNumber.id.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableNumber.name.name )
            .arg( m_dbTableNumber.name.type )
            .arg( m_dbTableNumber.name.extra );



    query.prepare( queryStr );
    query.exec();


    // contact table
    queryStr = QString( "CREATE TABLE IF NOT EXISTS %1 (%2 %3 %4, " ).arg( m_dbTableContact.tableName )
                                                                     .arg( m_dbTableContact.id.name )
                                                                     .arg( m_dbTableContact.id.type )
                                                                     .arg( m_dbTableContact.id.extra );
    queryStr += QString( "%1 %2 %3 )" ).arg( m_dbTableContact.name.name )
            .arg( m_dbTableContact.name.type )
            .arg( m_dbTableContact.name.extra );



    query.prepare( queryStr );
    query.exec();
}
