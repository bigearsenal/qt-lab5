#ifndef DATABASE_H
#define DATABASE_H

#define DATABASE_HOSTNAME "ExampleDatabase"
#define DATABASE_NAME "Database.db"

#define TABLE "TableExample"
#define TABLE_I "Name"
#define TABLE_F "Surname"
#define TABLE_SB "Sr_Ball"
#define TABLE_NS "N_Stud"
#define TABLE_TEL "Tel"
#define TABLE_POCH "Pochta"
#define TABLE_GR "Gruppa"
#define TABLE_DR "Date_Of_Birth"

#include <QObject>
#include "qsqldatabase.h"

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();

    void connectToDatabase();
    bool insertIntoTable(const QVariantList &data);
    bool createTable();

private:
    QSqlDatabase db;

    bool openDatabase();
    bool restoreDatabase();
    void closeDatabase();
};

#endif // DATABASE_H
