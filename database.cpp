#include "database.h"
#include "qfile.h"
#include "qcoreapplication.h"
#include "qdebug.h"
#include "qsqlquery.h"
#include "qsqlerror.h"

Database::Database(QObject *parent) : QObject(parent)
{

}

void Database::connectToDatabase() {
    QString dbPath = QCoreApplication::applicationDirPath() + "/" + DATABASE_NAME;

    qDebug() << dbPath;
    if (!QFile(dbPath).exists()) {
        this->restoreDatabase();
    } else {
        this->openDatabase();
    }
}

bool Database::restoreDatabase() {
    if (this->openDatabase()) {
        if (!this->createTable()) return false;
        return true;
    }

    qDebug() << "Не удалось восстановить базу данных";
    return false;
}

bool Database::openDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);

    QString dbPath = QCoreApplication::applicationDirPath() + "/" + DATABASE_NAME;
    db.setDatabaseName(dbPath);
    return db.open();
}

void Database::closeDatabase() {
    db.close();
}

bool Database::createTable() {
    QSqlQuery query;
    QString queryString = "CREATE TABLE " TABLE " ("
            "id"        " INTEGER PRIMARY KEY AUTOINCREMENT, "
            TABLE_I     " VARCHAR(10)       NOT NULL,"
            TABLE_F     " VARCHAR(20)       NOT NULL,"
            TABLE_DR    " VARCHAR           NOT NULL,"
            TABLE_GR    " VARCHAR(10)       NOT NULL,"
            TABLE_NS    " VARCHAR           NOT NULL,"
            TABLE_SB    " DOUBLE            NOT NULL,"
            TABLE_TEL   " VARCHAR(15)       NOT NULL,"
            TABLE_POCH  " VARCHAR(50)       NOT NULL"
            " )";

    if (!query.exec(queryString)) {
        qDebug() << "Ошибка при создание таблицы: " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::insertIntoTable(const QVariantList &data) {
    QSqlQuery query;
    QString queryString = "INSERT INTO " TABLE " ( "
            TABLE_I ", "
            TABLE_F ", "
            TABLE_DR ", "
            TABLE_GR ", "
            TABLE_NS ", "
            TABLE_SB ", "
            TABLE_TEL ", "
            TABLE_POCH " ) "
            "VALUES (:Name, :Surname, :Date_Of_Birth, :Gruppa, :N_Stud, :Sr_Ball, :Tel, :Pochta)";

    query.prepare(queryString);
    query.bindValue(":Name",                data[0].toString());
    query.bindValue(":Surname",             data[1].toString());
    query.bindValue(":Date_Of_Birth",       data[2].toString());
    query.bindValue(":Gruppa",              data[3].toString());
    query.bindValue(":N_Stud",              data[4].toString());
    query.bindValue(":Sr_Ball",             data[5].toDouble());
    query.bindValue(":Tel",                 data[6].toString());
    query.bindValue(":Pochta",              data[7].toString());

    if (!query.exec()) {
        qDebug() << "Ошибка при добавление данных в таблицу: " << query.lastError().text();
        return false;
    }
    return true;
}

Database::~Database() {

}
