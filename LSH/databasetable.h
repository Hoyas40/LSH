#ifndef DATABASETABLE_H
#define DATABASETABLE_H

#include <QString>
#include <QVector>

enum ENUM_DB_TABLES{ TABLE_CLIENT, TABLE_OPERATION, TABLE_CURL, TABLE_TYPE, TABLE_COLOR, TABLE_LENGTH, TABLE_NUMBER, TABLE_CONTACT, TABLE_NONE };

struct DB_TABLE_ITEM
{
    DB_TABLE_ITEM( const QString& _name = QString(""), const QString& _type = QString(""), const QString& _extra = QString("") )
        : name( _name ), type(_type), extra( _extra )
    {
    }
    void operator=( const DB_TABLE_ITEM& _item )
    {
        name = _item.name;
        type = _item.type;
        extra = _item.extra;

        //return *this;
    }

    QString name;
    QString type;
    QString extra;
};


struct DB_TABLE_CLIENT
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
    DB_TABLE_ITEM phoneNumber;
    DB_TABLE_ITEM contactWay;
//    DB_TABLE_ITEM hairLength;
//    DB_TABLE_ITEM hairNumber;
//    DB_TABLE_ITEM hairSag;
    DB_TABLE_ITEM info;
};

struct DB_TABLE_OPERATION
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM clientId;
    DB_TABLE_ITEM dateTime;
    DB_TABLE_ITEM curl;
    DB_TABLE_ITEM type;
    DB_TABLE_ITEM color;
    DB_TABLE_ITEM length;
    DB_TABLE_ITEM number;
    //DB_TABLE_ITEM style;
    DB_TABLE_ITEM price;
    DB_TABLE_ITEM shown;
};

struct DB_TABLE_CURL
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
};

struct DB_TABLE_TYPE
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
};

struct DB_TABLE_COLOR
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
};

struct DB_TABLE_LENGTH
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
};

struct DB_TABLE_NUMBER
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
};

struct DB_TABLE_CONTACT
{
    QString tableName;
    DB_TABLE_ITEM id;
    DB_TABLE_ITEM name;
};

#endif // DATABASETABLE_H
