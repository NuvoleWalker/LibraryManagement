#include "to_start.h"
#include "ui_to_start.h"
#include "mainwindow.h"

QString to_Start::WhoUsing=" ";
QString to_Start::UsingName=" ";

to_Start::to_Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::to_Start)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    this->setWindowIcon(QIcon(":/sourses/image/Title.png"));
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint);  //设置无菜单栏
    QPixmap pix(":/sourses/image/background.jpg");
    //pix.scaled(this->size());
    QPalette pa=this->palette();
    pa.setBrush(QPalette::Background,QBrush(pix));
    this->setPalette(pa);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");  //连接数据库
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("test");
    db.setUserName("root");
    db.setPassword("");

    if (!db.open())  //打开错误条件下
    {
        QMessageBox::critical(0,qApp->tr("Cannot open database"),
                              db.lastError().databaseText(),
                              QMessageBox::Cancel);
    }

    QSqlQuery query_register;
    query_register.exec("select * from books");
    if(!query_register.next())
    {
        query_register.exec("create table books (编号 varchar(20)  primary key,书名 varchar(255) ,作者 varchar(20),出版社 varchar(255),价格 varchar(20),库存 varchar(20),总数 varchar(20),选中 varchar(20)");
    }


    query_register.exec("select * from manager");
    if(!query_register.next())
    {
        query_register.exec("create table manager (User varchar(18) primary key,Password varchar(18))");
        query_register.exec("create table bookRequest (学号 varchar(30) ,用户名 varchar(255) ,编号 varchar(30) primary key,书名 varchar(30),作者 varchar(30),借阅日期 varchar(255),状态 varchar(10),选中 varchar(10))");  //学生借阅请求
        query_register.exec("create table bookReturn (学号 varchar(30) ,用户名 varchar(255) ,编号 varchar(30) primary key,书名 varchar(30),作者 varchar(30),归还日期 varchar(255),状态 varchar(10),选中 varchar(10))");  //学生借阅请求
        query_register.exec("insert into manager (User,Password) values('admin','123456')");
        query_register.exec("create table allusers (学号 varchar(30) primary key,User varchar(255) ,Password varchar(18))");
        query_register.exec("create table admin (编号 smallint(30) primary key,书名 varchar(255),作者 varchar(30),出版社 varchar(30),借阅日期 varchar(255), 归还日期 varchar(255),状态 varchar(10),选中 varchar(10))");
    }

//    QSqlQuery query;
//    query.exec("select * from allusers");
//    if(!query.next())
//    {

//    }

    QBitmap bmp(this->size());   //设置窗口圆角
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),30,30);
    setMask(bmp);

    QImage *image=new QImage;
    image->load(":/sourses/image/Title.png");
    ui->label_Title->setPixmap(QPixmap::fromImage(*image));

    ui->label->setStyleSheet("QLabel{background-color: rgba(0, 0, 0, 0.5);"
                             "border-radius:24px;padding:4px 4px}");

    QPixmap puser(":/sourses/image/user.png");
    ui->label_user->setPixmap(puser);
    QPixmap ppass(":/sourses/image/password.png");
    ui->label_password->setPixmap(ppass);
    QPixmap managerpix(":/sourses/image/Manager.png");
    ui->label_manager->setPixmap(managerpix);
    QPixmap successrpix(":/sourses/image/success.png");
    ui->label_success->setPixmap(successrpix);

    ui->lineEdit_user->setPlaceholderText(QStringLiteral("请输入用户名"));
    ui->lineEdit_password->setPlaceholderText(QStringLiteral("请输入密码"));
    ui->lineEdit_user_2->setPlaceholderText(QStringLiteral("请输入用户名"));
    ui->lineEdit_password_2->setPlaceholderText(QStringLiteral("请输入密码"));
    ui->lineEdit_Xuehao->setPlaceholderText(QStringLiteral("请输入学号"));

    ui->lineEdit_user->setStyleSheet("QLineEdit{background-color: rgba(255,255,255,0.3);color:white;font:18px;"
                                     "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_password->setStyleSheet("QLineEdit{background-color: rgba(255,255,255,0.3);color:white;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");

    ui->lineEdit_user_2->setStyleSheet("QLineEdit{background-color: rgba(255,255,255,0.3);color:white;font:18px;"
                                     "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_password_2->setStyleSheet("QLineEdit{background-color: rgba(255,255,255,0.3);color:white;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->lineEdit_Xuehao->setStyleSheet("QLineEdit{background-color: rgba(255,255,255,0.3);color:white;font:18px;"
                                         "border-radius:16px;padding:4px 4px}");

    ui->pushButton_Exit->setIcon(QIcon(":/sourses/image/close.png"));
    ui->pushButton_Min->setIcon(QIcon(":/sourses/image/min.png"));
    ui->pushButton_Exit->setStyleSheet("QPushButton{background-color:transparent;border:none;}"
                                         "QPushButton:hover{background-color: #FF3333;border:none;}");
    ui->pushButton_Min->setStyleSheet("QPushButton{background-color:transparent;border:none;}"
                                         "QPushButton:hover{background-color: #00BBFF;border:none;}");

    ui->pushButton_sure->setStyleSheet("QPushButton:hover{background-color: #3399FF;border:none;}"
                                        "QPushButton{background-color:white;border:none;"
                                       "border-radius:16px;padding:4px 4px}");
    ui->pushButton_register->setStyleSheet("QPushButton:hover{background-color: #77FFEE;border:none;}"
                                        "QPushButton{background-color:white;border:none;"
                                       "border-radius:16px;padding:4px 4px}");
    ui->pushButton_Regist->setStyleSheet("QPushButton:hover{background-color: #99FF66;border:none;}"
                                         "QPushButton{background-color:white;border:none;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->pushButton_cancel->setStyleSheet("QPushButton:hover{background-color: #FF0033;border:none;}"
                                         "QPushButton{background-color:white;border:none;"
                                         "border-radius:16px;padding:4px 4px}");
    ui->pushButton_yes->setStyleSheet("QPushButton:hover{background-color:#3399FF;border:none;}"
                                         "QPushButton{background-color:#77FFEE;border:none;"
                                         "border-radius:30px;padding:4px 4px}");

    QLineEdit *lineEdit = new QLineEdit;
    //lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignCenter);
    ui->comboBox->setLineEdit(lineEdit);

    ui->comboBox->setStyleSheet("QComboBox{background-color:rgba(255,255,255,0.3);color:white;font:18px;"
                                " border:noe;border-radius:16px;padding:4px 4px}"
                                "QComboBox QAbstractItemView{border:none;background-color:rgba(255,255,255,0.3);"
                                "border:noe;border-radius:16px;padding:4px 4px}"
                                "QComboBox::drop-down{border-top-right-radius: 3px;border-bottom-right-radius: 3px;subcontrol-origin: padding;"
                                "subcontrol-position: top right; width:40px;}"
                                "QComboBox::down-arrow{image:url(:/sourses/image/pushdown.png)}"
                                "QComboBox::down-arrow:hover{image:url(:/sourses/image/pushdown2.png)}"
                                "QComboBox::down-arrow:pressed{image:url(:/sourses/image/pushDown3.png)}");

    ui->comboBox->addItem(QString::asprintf("管理员",0));
    ui->comboBox->addItem(QString::asprintf("普通用户",1));

    ui->stackedWidget->setCurrentWidget(ui->page);

}

to_Start::~to_Start()
{
    delete ui;
}


//窗口移动 //窗口移动 //窗口移动 //窗口移动 //窗口移动
void to_Start::mousePressEvent(QMouseEvent *event)  //鼠标按下
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

void to_Start::mouseMoveEvent(QMouseEvent *event)  //鼠标移动
{
    if(mouseIsPressd)
    {
        QPoint DialogMove=event->globalPos()-mousePosition;
        move(DialogMove);
    }
}

void to_Start::mouseReleseEvent(QMouseEvent *)  //鼠标松开
{
    mouseIsPressd=false;
}


void to_Start::on_pushButton_Exit_clicked()
{
    close();
}

void to_Start::on_pushButton_Regist_clicked()   //取消按钮
{
    ui->lineEdit_user->clear();
    ui->lineEdit_password->clear();

    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void to_Start::on_pushButton_sure_clicked()    //登录按钮
{
    to_Start::WhoUsing=ui->comboBox->currentText();
    to_Start::UsingName=ui->lineEdit_user->text();
    QString password=ui->lineEdit_password->text();
    QString sqlPassword;
    QSqlQuery query;
    QString sql;
    if(to_Start::WhoUsing=="管理员")
    {
        sql=QString("select * from manager where User='%1'").arg(to_Start::UsingName);
    }
    else {
        sql=QString("select * from allusers where User='%1'").arg(to_Start::UsingName);
    }
    query.exec(sql);

    while(query.next())
    {
        if(to_Start::WhoUsing=="管理员")
        {
            sqlPassword=query.value(1).toString();
        }
        else{
            sqlPassword=query.value(2).toString();
        }
        if(password==sqlPassword)
        {
            this->close();
            MainWindow *mainwin=new MainWindow();
            mainwin->show();
            return;
        }
        else
        {
            ui->lineEdit_user->clear();
            ui->lineEdit_password->clear();
            ui->lineEdit_user->setPlaceholderText(QStringLiteral("用户名或密码错误"));
            return;
        }
    }
    ui->lineEdit_user->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_user->setPlaceholderText(QStringLiteral("用户名或密码错误"));
    return;


}

void to_Start::on_pushButton_Min_clicked()
{
    showMinimized();
}

//void QPasswordLineEdit::slotTextEdited(const QString& text)
//{
//    if(text.count()>mLastCharCount)//输入
//    {
//        mLineEditText.append(text.right(1));
//    }
//    else if(text.count()<mLastCharCount)//删除
//    {
//        mLineEditText.remove(mLineEditText.count()-1,1);
//    }
//    mLastCharCount = mLineEditText.count();
//}


void to_Start::on_pushButton_register_clicked()
{
    QSqlQuery query_register;
    query_register.exec(QString("create table %1 (编号 smallint(30) primary key,书名 varchar(255),作者 varchar(30),出版社 varchar(30),借阅日期 char(255), 归还日期 char(255),状态 varchar(10),选中 varchar(10))")
                        .arg(ui->lineEdit_user_2->text()));

//    query_register.exec(QString("insert into %1(User,Password,Name) values('%2','%3'.'%4)").arg(ui->lineEdit_user_2->text())
//                        .arg(ui->lineEdit_user_2->text())
//                        .arg(ui->lineEdit_password_2->text())
//                        .arg(ui->lineEdit_Name->text()));

    query_register.exec(QString("insert into allusers(学号,User,Password) values('%1','%2','%3')").arg(ui->lineEdit_Xuehao->text()).arg(ui->lineEdit_user_2->text())
                        .arg(ui->lineEdit_password_2->text()));
//    if(!query_register.next())
//    {
//        qDebug()<<query_register.lastError();
//    }
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void to_Start::on_pushButton_cancel_clicked()
{
    ui->lineEdit_Xuehao->clear();
    ui->lineEdit_user_2->clear();
    ui->lineEdit_password_2->clear();
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void to_Start::on_pushButton_yes_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}
