#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    db->connectToDatabase();
    db->createTable();
    ui->setupUi(this);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveButtonClicked()));

    this->setupModel(TABLE,
                     QStringList()
                        << trUtf8("id")
                        << trUtf8("Имя")
                        << trUtf8("Фамилия")
                        << trUtf8("Дата рождения")
                        << trUtf8("Группа")
                        << trUtf8("№ Студ.")
                        << trUtf8("Ср. балл")
                        << trUtf8("Тел.")
                        << trUtf8("Почта")
                        << trUtf8("")
                     );
    this->createUi();
}

void MainWindow::setupModel(const QString &tableName, const QStringList &headers) {
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    int j = 0;
    for (int i = 0; i < model->columnCount() ; i++) {
        model->setHeaderData(i, Qt::Horizontal, headers[j]);
        j++;
    }

    model->setSort(0, Qt::AscendingOrder);
}

void MainWindow::createUi() {
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    model->select();
}

void MainWindow::onAddButtonClicked() {
    QVariantList data;
    QString i = "Chung";
    QString fam = "Tran";
    QString dat = "28-04-1993";
    QString gr = "ИКМО-01-17";
    QString ns = "14Л2341";
    double sb = 4.5;
    QString tel = "89606127993";
    QString poch = "chungtran@mail.ru";
    data.append(i);
    data.append(fam);
    data.append(dat);
    data.append(gr);
    data.append(ns);
    data.append(sb);
    data.append(tel);
    data.append(poch);
    db->insertIntoTable(data);

    model->select();
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::onRemoveButtonClicked() {
}

MainWindow::~MainWindow()
{
    delete ui;
}
