#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"to_start.h"
#include <QMainWindow>
#include<QMouseEvent>
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMessageBox>
#include<QDebug>
#include<QPalette>
#include<QPixmap>
#include<QScrollBar>
#include<QTableWidgetItem>
#include<QItemDelegate>
#include<QVector>
#include "tablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVariant data(const QModelIndex &index, int role) const;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SetButtonStyle();
    TableModel *model;
    TableModel *model_myBorrow;
    TableModel *model_request;
    TableModel *model_returnBook;
    //QSqlQueryModel *model;
    QPoint mousePosition;
    bool mouseIsPressd=false;

    bool currentRequest=true;
    Ui::MainWindow *ui;

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void on_pushButton_close_clicked();
    void on_pushButton_min_clicked();
    void on_pushButton_clicked();
    void on_pushButton_search_clicked();

    void buttonColorChange();
    void on_pushButton_2_clicked();
    void on_pushButton_resident_clicked();
    void on_pushButton_cancelR_clicked();
    void on_pushButton_search_2_clicked();
    void on_pushButton_UserCenter_clicked();
    void on_pushButton_bookManage_clicked();
    void on_pushButton_seach_3_clicked();
    void on_pushButton_RequestManage_clicked();
    void on_pushButton_changePassword_clicked();
    void on_pushButton_AddManager_clicked();
    void on_pushButton_newmanege_clicked();
    void on_pushButton_managechange_clicked();
    void on_pushButton_userchange_clicked();
    void on_pushButton_yes_clicked();
    void on_pushButton_return_clicked();
    void on_pushButton_deleteManage_clicked();
    void on_pushButton_agree_clicked();
    void on_pushButton_toReturn_clicked();
    void on_pushButton_disagree_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_addbooks_clicked();
};
#endif // MAINWINDOW_H
