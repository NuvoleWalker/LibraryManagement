#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint);  //设置无菜单栏
    this->setWindowIcon(QIcon(":/sourses/mainImage/bookIcon.png"));
    this->setWindowTitle("Books Management");

    QPalette pale=this->palette();
    QPixmap pix(":/sourses/mainImage/colorVarious2.jfif");
    pale.setBrush(QPalette::Background,QBrush(pix));
    this->setPalette(pale);

    QImage *image=new QImage;
    image->load(":/sourses/mainImage/bookIcon.png");
    ui->label_bookIcon->setPixmap(QPixmap::fromImage(*image));

    model = new TableModel();
    model_myBorrow = new TableModel();
    model_request= new TableModel();
    model_returnBook= new TableModel();
    //model=new QSqlQueryModel;

    ui->pushButton_close->setIcon(QIcon(":/sourses/image/close.png"));
    ui->pushButton_min->setIcon(QIcon(":/sourses/image/min.png"));
    ui->pushButton_close->setStyleSheet("QPushButton{background-color:transparent;border:none;}"
                                         "QPushButton:hover{background-color: #FF3333;border:none;}");
    ui->pushButton_min->setStyleSheet("QPushButton{background-color:transparent;border:none;}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");

    ui->tableView->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableView->horizontalHeader()->setFixedHeight(70);  //表头行高
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#CCCCCC;border:none}");
    ui->tableView->verticalHeader()->setDefaultSectionSize(50);
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);  //不能选中
    ui->tableView->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    ui->tableView_2->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableView_2->horizontalHeader()->setFixedHeight(70);  //表头行高
    ui->tableView_2->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#CCCCCC;border:none}");
    ui->tableView_2->verticalHeader()->setDefaultSectionSize(50);
    ui->tableView_2->horizontalHeader()->setHighlightSections(false);
    ui->tableView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_2->setSelectionMode(QAbstractItemView::NoSelection);  //不能选中
    ui->tableView_2->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    ui->tableView_3->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableView_3->horizontalHeader()->setFixedHeight(70);  //表头行高
    ui->tableView_3->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#CCCCCC;border:none}");
    ui->tableView_3->verticalHeader()->setDefaultSectionSize(50);
    ui->tableView_3->horizontalHeader()->setHighlightSections(false);
    ui->tableView_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_3->setSelectionMode(QAbstractItemView::NoSelection);  //不能选中
    ui->tableView_3->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    ui->tableView_bookRequest->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableView_bookRequest->horizontalHeader()->setFixedHeight(70);  //表头行高
    ui->tableView_bookRequest->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#CCCCCC;border:none}");
    ui->tableView_bookRequest->verticalHeader()->setDefaultSectionSize(50);
    ui->tableView_bookRequest->horizontalHeader()->setHighlightSections(false);
    ui->tableView_bookRequest->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView_bookRequest->setSelectionMode(QAbstractItemView::NoSelection);  //不能选中
    ui->tableView_bookRequest->setFocusPolicy(Qt::NoFocus); //去除选中虚线框

    QFile file(":/sourses/qss/Style.qss");
    file.open(QFile::ReadOnly);
    ui->tableView->verticalScrollBar()->setStyleSheet(file.readAll());    //垂直滚动条
    file.close();

    QFile file_2(":/sourses/qss/Style _2.qss");
    file_2.open(QFile::ReadOnly);
    ui->tableView_2->verticalScrollBar()->setStyleSheet(file_2.readAll());    //垂直滚动条
    file_2.close();

    QFile file_3(":/sourses/qss/Style _2.qss");
    file_3.open(QFile::ReadOnly);
    ui->tableView_3->verticalScrollBar()->setStyleSheet(file_3.readAll());    //垂直滚动条
    file_3.close();

    QFile file_4(":/sourses/qss/Style _2.qss");
    file_4.open(QFile::ReadOnly);
    ui->tableView_bookRequest->verticalScrollBar()->setStyleSheet(file_4.readAll());    //垂直滚动条
    file_4.close();

    SetButtonStyle();
    buttonColorChange();

    ui->lineEdit_search->setPlaceholderText(QStringLiteral("请按书名或作者查找"));
    ui->lineEdit_search->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");

    ui->lineEdit_search_2->setPlaceholderText(QStringLiteral("请按书名或作者查找"));
    ui->lineEdit_search_2->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");

    ui->lineEdit_search_3->setPlaceholderText(QStringLiteral("请按书名或作者查找"));
    ui->lineEdit_search_3->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");

    connect(ui->stackedWidget,&QStackedWidget::currentChanged,this,&MainWindow::buttonColorChange);

    QPixmap successrpix(":/sourses/image/success.png");
    ui->label_success->setPixmap(successrpix);

    if(to_Start::WhoUsing=="管理员")
    {
        ui->pushButton_bookManage->setEnabled(true);
        ui->pushButton_RequestManage->setEnabled(true);
        ui->pushButton_resident->setEnabled(false);
    }
    else {
        ui->pushButton_bookManage->setEnabled(false);
        ui->pushButton_RequestManage->setEnabled(false);
        ui->pushButton_resident->setEnabled(true);
    }

    ui->lineEdit_usernew->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_userold->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_managenewpass->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_manageoldpass->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_managenewnameadd->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_managenewpassadd->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");

    ui->pushButton_agree->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_disagree->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_toReturn->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_AddManager->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_managechange->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_changePassword->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_newmanege->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");
    ui->pushButton_userchange->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");




    ui->lineEdit->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_2->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_3->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_4->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_5->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_6->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_7->setStyleSheet("QLineEdit{background-color: #F5F5DC;color:grey;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color:#F5F5DC;border:none;border-radius:16px;padding:4px 4px}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");


    on_pushButton_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
    ui->lineEdit_search->clear();
    //QSqlQueryModel *model = new QSqlQueryModel;
    //TableModel *model = new TableModel;
    model->setQuery("select * from books");//这里直接设置SQL语句，忽略最后一个参数 StudentInformation为要操作的表名
    ui->tableView->setModel(model);
    //以下是视觉方面的效果，不加也没影响
    //隔行变色
    //ui->tableView->setAlternatingRowColors(true);

    ui->tableView->setColumnWidth(0, 100);//设置固定宽度
    ui->tableView->setColumnWidth(1, 250);
    ui->tableView->setColumnWidth(2, 150);
    ui->tableView->setColumnWidth(3, 200);
    ui->tableView->setColumnWidth(4, 100);
    ui->tableView->setColumnWidth(5, 100);
    ui->tableView->setColumnWidth(6, 100);
    ui->tableView->setColumnWidth(7,60);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    QString sqled=QString("select * from %1").arg(to_Start::UsingName);
    model_myBorrow->setQuery(sqled);
    ui->tableView_2->setModel(model_myBorrow);

    ui->tableView_2->setColumnWidth(0, 100);//设置固定宽度
    ui->tableView_2->setColumnWidth(1, 200);
    ui->tableView_2->setColumnWidth(2, 150);
    ui->tableView_2->setColumnWidth(3, 200);
    ui->tableView_2->setColumnWidth(4, 150);
    ui->tableView_2->setColumnWidth(5, 150);
    ui->tableView_2->setColumnWidth(6, 60);
    ui->tableView_2->setColumnWidth(7, 60);
}

void MainWindow::on_pushButton_UserCenter_clicked()   //用户中心
{
    ui->stackedWidget->setCurrentWidget(ui->page_UerCenter);
    if(to_Start::WhoUsing=="管理员")
    {
        ui->stackedWidget_2->setCurrentWidget(ui->page_managerCenter);
        ui->lineEdit_managenewpass->clear();
        ui->lineEdit_manageoldpass->clear();
    }
    else {
        ui->stackedWidget_2->setCurrentWidget(ui->page_uerCenter);
        ui->lineEdit_usernew->clear();
        ui->lineEdit_userold->clear();
    }

}

void MainWindow::on_pushButton_bookManage_clicked()  //图书管理
{
     ui->stackedWidget->setCurrentWidget(ui->page_bookmanage);

     model->setQuery("select * from books");//这里直接设置SQL语句，忽略最后一个参数 StudentInformation为要操作的表名
     ui->tableView_3->setModel(model);

     ui->tableView_3->setColumnWidth(0, 100);//设置固定宽度
     ui->tableView_3->setColumnWidth(1, 250);
     ui->tableView_3->setColumnWidth(2, 150);
     ui->tableView_3->setColumnWidth(3, 200);
     ui->tableView_3->setColumnWidth(4, 100);
     ui->tableView_3->setColumnWidth(5, 100);
     ui->tableView_3->setColumnWidth(6, 100);
     ui->tableView_3->setColumnWidth(7,60);
}

void MainWindow::on_pushButton_search_clicked()  //查询
{
    QString sql=QString("select * from books where 作者='%1' or 书名='%1'").arg(ui->lineEdit_search->text());
    model->setQuery(sql);
    ui->tableView->setModel(model);

}

void MainWindow::on_pushButton_resident_clicked()    //借阅
{
    for(int i=0;i<model->check_state_map.size();i++)
    {
        if(model->check_state_map[i]==Qt::Checked)
        {
            QModelIndex index = model->index(i,0);
            QString num = model->data(index,2).toString();
            QModelIndex index_2 = model->index(i,5);
            int restNum=model->data(index_2,2).toInt();
            QSqlQuery query_2;

            query_2.exec("SET NAMES 'UTF8'");
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm");
            query_2.exec(QString("insert into %1 (编号,书名,作者,出版社) select 编号,书名,作者,出版社 from books where 编号='%2'").arg(to_Start::UsingName)
                         .arg(num));

            query_2.exec(QString("update books set 库存='%1' where 编号='%2'").arg(restNum-1).arg(num));

            query_2.exec(QString("update %1 set 借阅日期='%2',状态='审核中' where 编号='%3'").arg(to_Start::UsingName)
                         .arg(current_date).arg(num));

            query_2.exec(QString("select * from allusers where User='%1'").arg(to_Start::UsingName));
            QString xuehao;
            QString yonghuming;
            if(query_2.next())
            {
                xuehao=query_2.value(0).toString();
               yonghuming=query_2.value(1).toString();
            }
            query_2.exec(QString("insert into bookrequest (学号,用户名,编号) values('%1','%2','%3')").arg(xuehao).arg(yonghuming).arg(num));
            query_2.exec(QString("select * from %1 where 编号='%2'").arg(to_Start::UsingName).arg(num));
            if(query_2.next())
            {
                QString bookname=query_2.value(1).toString();
                QString writer=query_2.value(2).toString();
                QString date_1=query_2.value(4).toString();
                QString zhuangtai=query_2.value(6).toString();
                query_2.exec(QString("update bookrequest set 书名='%1',作者='%2',借阅日期='%3',状态='%4' where 编号='%5'").arg(bookname)
                             .arg(writer).arg(date_1).arg(zhuangtai).arg(num));
                qDebug()<<query_2.lastError();
            }

            model->check_state_map[i]=Qt::Unchecked;
        }
        on_pushButton_clicked();
    }
}

void MainWindow::SetButtonStyle()
{
    ui->pushButton->setStyleSheet("QPushButton{background-color:#9999FF;border:none;color:white;}"
                                         "QPushButton:hover{background-color:#5555FF;border:none;}");
    ui->pushButton_2->setStyleSheet("QPushButton{background-color:#9999FF;border:none;color:white;}"
                                         "QPushButton:hover{background-color:#5555FF;border:none;}");
    ui->pushButton_bookManage->setStyleSheet("QPushButton{background-color:#9999FF;border:none;color:white;}"
                                         "QPushButton:hover{background-color:#5555FF;border:none;}");
    ui->pushButton_UserCenter->setStyleSheet("QPushButton{background-color:#9999FF;border:none;color:white;}"
                                         "QPushButton:hover{background-color:#5555FF;border:none;}");
    ui->pushButton_RequestManage->setStyleSheet("QPushButton{background-color:#9999FF;border:none;color:white;}"
                                         "QPushButton:hover{background-color:#5555FF;border:none;}");
}
void MainWindow::buttonColorChange()
{
    SetButtonStyle();
    if(ui->stackedWidget->currentWidget()==ui->page)
    {
        ui->pushButton->setStyleSheet("QPushButton{background-color:#4682B4;border:none;color:white;}");
    }
    else if(ui->stackedWidget->currentWidget()==ui->page_2)
    {
        ui->pushButton_2->setStyleSheet("QPushButton{background-color:#4682B4;border:none;color:white;}");
    }
    else if(ui->stackedWidget->currentWidget()==ui->page_bookmanage)
    {
        ui->pushButton_bookManage->setStyleSheet("QPushButton{background-color:#4682B4;border:none;color:white;}");
    }
    else if(ui->stackedWidget->currentWidget()==ui->page_UerCenter)
    {
        ui->pushButton_UserCenter->setStyleSheet("QPushButton{background-color:#4682B4;border:none;color:white;}");
    }
}

//窗口移动 //窗口移动 //窗口移动 //窗口移动 //窗口移动
void MainWindow::mousePressEvent(QMouseEvent *event)  //鼠标按下
{
    mousePosition=event->pos();
    if(mousePosition.x()<=0)    //位置横坐标小于0
        return;
    if(mousePosition.x()>=this->width())  //位置大于窗口宽
        return;
    if(mousePosition.y()<=0)    //位置纵坐标小于零
        return;
    if(mousePosition.y()>=this->height())  //位置纵坐标大于窗口高
        return;
    mouseIsPressd=true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)  //鼠标移动
{
    if(mouseIsPressd)
    {
        QPoint DialogMove=event->globalPos()-mousePosition;
        move(DialogMove);
    }
}

void MainWindow::mouseReleseEvent(QMouseEvent *)  //鼠标松开
{
    mouseIsPressd=false;
}

void MainWindow::on_pushButton_close_clicked()
{
    close();
}

void MainWindow::on_pushButton_min_clicked()
{
    showMinimized();
}




void MainWindow::on_pushButton_cancelR_clicked()   //取消借阅
{
    QSqlQuery query_cancel;
    QVector<QString> Nums;
    for(int i=0;i<model_myBorrow->check_state_map.size();i++)
    {
        if(model_myBorrow->check_state_map[i]==Qt::Checked)
        {
            QModelIndex index = model_myBorrow->index(i,6);
            QString isDealing = model_myBorrow->data(index,2).toString();
            if(isDealing=="审核中")
            {
                QModelIndex index = model_myBorrow->index(i,0);
                QString num = model_myBorrow->data(index,2).toString();
                Nums.push_back(num);
            }
            model_myBorrow->check_state_map[i]=Qt::Unchecked;
        }
    }
    for(int i=0;i<Nums.size();i++)
    {
        query_cancel.exec(QString("delete from %1 where 编号='%2'").arg(to_Start::UsingName).arg(Nums[i]));
        query_cancel.exec(QString("delete from bookrequest where 编号='%1'").arg(Nums[i]));
        query_cancel.exec(QString("select 库存 from books where 编号='%1'").arg(Nums[i]));
        if(query_cancel.next())
        {
            int restnum=query_cancel.value(0).toInt();
            query_cancel.exec(QString("update books set 库存='%1' where 编号='%2'").arg(restnum+1).arg(Nums[i]));
        }
    }
    on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_search_2_clicked()   // 我的
{
    QString sql=QString("select * from %1 where 作者='%2' or 书名='%2'").arg(to_Start::UsingName).arg(ui->lineEdit_search_2->text());
    model_myBorrow->setQuery(sql);
    ui->tableView_2->setModel(model_myBorrow);
}



void MainWindow::on_pushButton_seach_3_clicked()
{
    QString sql=QString("select * from books where 作者='%1' or 书名='%1'").arg(ui->lineEdit_search_3->text());
    model->setQuery(sql);
    ui->tableView_2->setModel(model);

}

void MainWindow::on_pushButton_RequestManage_clicked()   //请求管理
{
    ui->stackedWidget->setCurrentWidget(ui->page_Request);
    QString sql=QString("select * from bookrequest");
    model_request->setQuery(sql);
    ui->tableView_bookRequest->setModel(model_request);
    currentRequest=true;

    ui->tableView_bookRequest->setColumnWidth(0, 150);//设置固定宽度
    ui->tableView_bookRequest->setColumnWidth(1, 250);
    ui->tableView_bookRequest->setColumnWidth(2, 150);
    ui->tableView_bookRequest->setColumnWidth(3, 200);
    ui->tableView_bookRequest->setColumnWidth(4, 100);
    ui->tableView_bookRequest->setColumnWidth(5, 100);
    ui->tableView_bookRequest->setColumnWidth(6, 100);
    ui->tableView_bookRequest->setColumnWidth(7,60);
}

void MainWindow::on_pushButton_changePassword_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_managerCenter);
}

void MainWindow::on_pushButton_AddManager_clicked()
{
    ui->stackedWidget_2->setCurrentWidget(ui->page_AddManager);
}

void MainWindow::on_pushButton_newmanege_clicked()   //添加管理员
{
    ui->lineEdit_managenewnameadd->clear();
    ui->lineEdit_managenewpassadd->clear();
    QSqlQuery query_add;
    query_add.exec(QString("insert into manager(User,Password) values('%1','%2')").arg(ui->lineEdit_managenewnameadd->text())
                   .arg(ui->lineEdit_managenewpassadd->text()));
    query_add.exec(QString("create table %1 (编号 smallint(30) primary key,书名 varchar(255),作者 varchar(30),出版社 varchar(30),借阅日期 char(255), 归还日期 char(255),状态 varchar(10),选中 varchar(10))")
                        .arg(ui->lineEdit_managenewnameadd->text()));
    ui->stackedWidget_2->setCurrentWidget(ui->page_Ok);
}

void MainWindow::on_pushButton_managechange_clicked()  //修改管理员密码
{
    QSqlQuery query_change;
    query_change.exec(QString("select * from manager where User='%1'").arg(to_Start::UsingName));
    if(query_change.next())
    {
        QString Password_old=query_change.value(1).toString();
        if(ui->lineEdit_manageoldpass->text()==Password_old)
        {
            query_change.exec(QString("update manager set Password='%1' where User='%2'").arg(ui->lineEdit_managenewpass->text())
                              .arg(to_Start::UsingName));
            ui->stackedWidget_2->setCurrentWidget(ui->page_Ok);
        }
    }
}

void MainWindow::on_pushButton_userchange_clicked()   //修改用户密码
{
    QSqlQuery query_change;
    query_change.exec(QString("select * from allusers where User='%1'").arg(to_Start::UsingName));
    if(query_change.next())
    {
        QString Password_old=query_change.value(1).toString();
        if(ui->lineEdit_userold->text()==Password_old)
        {
            query_change.exec(QString("update allusers set Password='%1' where User='%2'").arg(ui->lineEdit_usernew->text())
                              .arg(to_Start::UsingName));
            ui->stackedWidget_2->setCurrentWidget(ui->page_Ok);
        }
    }
}

void MainWindow::on_pushButton_yes_clicked()
{
    on_pushButton_UserCenter_clicked();
}

void MainWindow::on_pushButton_return_clicked()  //归还图书
{
    QSqlQuery query_return;
    QVector<QString> Nums;
    for(int i=0;i<model_myBorrow->check_state_map.size();i++)
    {
        if(model_myBorrow->check_state_map[i]==Qt::Checked)
        {
            QModelIndex index = model_myBorrow->index(i,0);
            QString num = model_myBorrow->data(index,2).toString();
            query_return.exec(QString("select * from %1 where 编号='%2'").arg(to_Start::UsingName).arg(num));
            if(query_return.next())
            {
                QString zhuangtai=query_return.value(6).toString();
                if(zhuangtai=="借阅成功")
                {
                    query_return.exec(QString("update %1 set 状态='归还中' where 编号='%2'").arg(to_Start::UsingName).arg(num));

                    QString xuehao;
                    QString yonghuming;
                    query_return.exec(QString("select * from bookrequest where 编号='%1'").arg(num));
                    if(query_return.next())
                    {
                       xuehao=query_return.value(0).toString();
                       yonghuming=query_return.value(1).toString();
                       QString bookname=query_return.value(2).toString();
                       QString writer=query_return.value(3).toString();
                       QString zhuangtai="归还中";
                       QDateTime current_date_time = QDateTime::currentDateTime();
                       QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm");

                       query_return.exec(QString("insert into bookreturn (学号,用户名,编号,书名,作者,归还日期,状态) values('%1','%2','%3','%4','%5','%6','%7')")
                                         .arg(xuehao).arg(yonghuming).arg(num).arg(bookname).arg(writer).arg(current_date).arg(zhuangtai));

                    }

                }
            }

            model_myBorrow->check_state_map[i]=Qt::Unchecked;
        }
    }
    on_pushButton_2_clicked();
}

void MainWindow::on_pushButton_deleteManage_clicked()   //管理员删除图书
{
    QSqlQuery query_return;
    QVector<QString> Nums;
    for(int i=0;i<model->check_state_map.size();i++)
    {
        if(model->check_state_map[i]==Qt::Checked)
        {
            QModelIndex index = model->index(i,0);
            QString num = model->data(index,2).toString();
            Nums.push_back(num);
        }
    }
    for(int i=0;i<Nums.size();i++)
    {
        query_return.exec(QString("select * from books where 编号='%1'").arg(Nums[i]));
        if(query_return.next())
        {
            QString kucun=query_return.value(5).toString();
            QString Allbook=query_return.value(6).toString();
            if(kucun==Allbook)
            {
                query_return.exec(QString("delete from books where 编号='%1'").arg(Nums[i]));
            }
        }
        model->check_state_map[i]=Qt::Unchecked;
    }
    on_pushButton_bookManage_clicked();
}

void MainWindow::on_pushButton_agree_clicked()    //同意
{
    QSqlQuery query_return;
    QVector<QString> Nums;
    QString num;
    QString username;
    if(currentRequest==true)  //借书
    {
        for(int i=0;i<model_request->check_state_map.size();i++)
        {
            if(model_request->check_state_map[i]==Qt::Checked)
            {
                QModelIndex index = model_request->index(i,2);
                num = model_request->data(index,2).toString();
                Nums.push_back(num);
            }
            model_request->check_state_map[i]=Qt::Unchecked;
        }
        for(int i=0;i<Nums.size();i++)
        {
            query_return.exec(QString("select *from bookrequest where 编号='%1'").arg(Nums[i]));
            if(query_return.next())
            {
                username=query_return.value(1).toString();
            }
            query_return.exec(QString("update %1 set 状态='借阅成功' where 编号='%2'").arg(username).arg(Nums[i]));
            query_return.exec(QString("update bookrequest set 状态='借阅成功' where 编号='%1'").arg(Nums[i]));


        }
        on_pushButton_RequestManage_clicked();
    }
    else{   //归还
        for(int i=0;i<model_returnBook->check_state_map.size();i++)
        {
            if(model_returnBook->check_state_map[i]==Qt::Checked)
            {
                QModelIndex index = model_returnBook->index(i,2);
                num = model_returnBook->data(index,2).toString();
                Nums.push_back(num);
            }
            model_returnBook->check_state_map[i]=Qt::Unchecked;
        }
        for(int i=0;i<Nums.size();i++)
        {
            query_return.exec(QString("select * from books where 编号='%1'").arg(Nums[i]));
            if(query_return.next())
            {
                int rest=query_return.value(5).toInt();
                query_return.exec(QString("select *from bookrequest where 编号='%1'").arg(num));
                if(query_return.next())
                {
                    username=query_return.value(1).toString();
                }
                query_return.exec(QString("update books set 库存='%1' where 编号='%2'").arg(rest+1).arg(Nums[i]));
                query_return.exec(QString("update bookreturn set 状态='归还成功' where 编号='%1'").arg(Nums[i]));
                query_return.exec(QString("update %1 set 状态='归还成功' where 编号='%2'").arg( username).arg(Nums[i]));
            }
        }
        currentRequest=true;
        on_pushButton_toReturn_clicked();
    }


}

void MainWindow::on_pushButton_toReturn_clicked()
{
    if(currentRequest==true)
    {
        QString sql=QString("select * from bookretrun");
        model_request->setQuery(sql);
        ui->tableView_bookRequest->setModel(model_request);
        currentRequest=false;
    }
    else{
        on_pushButton_RequestManage_clicked();
    }

    ui->tableView_bookRequest->setColumnWidth(0, 160);//设置固定宽度
    ui->tableView_bookRequest->setColumnWidth(1, 250);
    ui->tableView_bookRequest->setColumnWidth(2, 150);
    ui->tableView_bookRequest->setColumnWidth(3, 200);
    ui->tableView_bookRequest->setColumnWidth(4, 100);
    ui->tableView_bookRequest->setColumnWidth(5, 100);
    ui->tableView_bookRequest->setColumnWidth(6, 100);
    ui->tableView_bookRequest->setColumnWidth(7,60);
}

void MainWindow::on_pushButton_disagree_clicked()
{
    QSqlQuery query_return;
    QVector<QString> Nums;
    QString num;
    QString username;
    if(currentRequest==true)  //借书
    {
        for(int i=0;i<model_request->check_state_map.size();i++)
        {
            if(model_request->check_state_map[i]==Qt::Checked)
            {
                QModelIndex index = model_request->index(i,2);
                num = model_request->data(index,2).toString();
                Nums.push_back(num);
            }
            model_request->check_state_map[i]=Qt::Unchecked;
        }
        for(int i=0;i<Nums.size();i++)
        {
            query_return.exec(QString("select * from books where 编号='%1'").arg(Nums[i]));
            if(query_return.next())
            {
                int rest=query_return.value(5).toInt();
                query_return.exec(QString("update books set 库存='%1' where 编号='%2'").arg(rest+1).arg(Nums[i]));
            }
            query_return.exec(QString("select *from bookrequest where 编号='%1'").arg(Nums[i]));
            if(query_return.next())
            {
                username=query_return.value(1).toString();
            }
            query_return.exec(QString("update %1 set 状态='失败' where 编号='%2'").arg(username).arg(Nums[i]));
            query_return.exec(QString("update bookrequest set 状态='失败' where 编号='%1'").arg(Nums[i]));
            query_return.exec(QString("delete from bookrequest where 编号='%1'").arg(Nums[i]));

        }
        on_pushButton_RequestManage_clicked();
    }
    else{   //归还
        for(int i=0;i<model_returnBook->check_state_map.size();i++)
        {
            if(model_returnBook->check_state_map[i]==Qt::Checked)
            {
                QModelIndex index = model_returnBook->index(i,2);
                num = model_returnBook->data(index,2).toString();
                Nums.push_back(num);
            }
            model_returnBook->check_state_map[i]=Qt::Unchecked;
        }
        for(int i=0;i<Nums.size();i++)
        {
            query_return.exec(QString("select * from books where 编号='%1'").arg(Nums[i]));
            if(query_return.next())
            {
                int rest=query_return.value(5).toInt();
                query_return.exec(QString("select *from bookrequest where 编号='%1'").arg(Nums[i]));
                if(query_return.next())
                {
                    username=query_return.value(1).toString();
                }
                query_return.exec(QString("update books set 库存='%1' where 编号='%2'").arg(rest+1).arg(Nums[i]));
                query_return.exec(QString("update bookreturn set 状态='失败' where 编号='%1'").arg(Nums[i]));
                query_return.exec(QString("update %1 set 状态='失败' where 编号='%2'").arg( username).arg(Nums[i]));
                query_return.exec(QString("delete from bookrequest where 编号='%1'").arg(Nums[i]));
            }
        }
        currentRequest=true;
        on_pushButton_toReturn_clicked();
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery add_query;
    add_query.exec(QString("insert into books(编号,书名,作者,出版社,价格,库存,总数) values('%1','%2','%3','%4','%5','%6','%7')").arg(ui->lineEdit->text())
                   .arg(ui->lineEdit_2->text()).arg(ui->lineEdit_3->text()).arg(ui->lineEdit_4->text())
                   .arg(ui->lineEdit_5->text()).arg(ui->lineEdit_6->text())
                   .arg(ui->lineEdit_7->text()));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
}

void MainWindow::on_pushButton_addbooks_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_ADDbooks);
}
