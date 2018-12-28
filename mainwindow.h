#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddButtonClicked();
    void onRemoveButtonClicked();

private:
    Ui::MainWindow *ui;
    Database *db;
    QSqlTableModel *model;
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUi();
};

#endif // MAINWINDOW_H
