#ifndef TO_START_H
#define TO_START_H

#include <QWidget>
#include<QMouseEvent>
#include<QPixmap>
#include<QPalette>
#include<QIcon>
#include<QImage>
#include<QBitmap>
#include<QPainter>

namespace Ui {
class to_Start;
}

class to_Start : public QWidget
{
    Q_OBJECT

public:
    static QString WhoUsing;
    static QString UsingName;

    explicit to_Start(QWidget *parent = nullptr);
    ~to_Start();

private:
    QPoint mousePosition;
    bool mouseIsPressd=false;
    Ui::to_Start *ui;

private slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void on_pushButton_Exit_clicked();
    void on_pushButton_Regist_clicked();
    void on_pushButton_sure_clicked();
    void on_pushButton_Min_clicked();
    void on_pushButton_register_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_yes_clicked();
};

#endif // TO_START_H
