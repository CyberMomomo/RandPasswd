#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>

#include <random>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    const QString c1 = "0123456789";
    const QString c2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const QString c3 = "abcdefghijklmnopqrstuvwxyz";
    const QString c4 = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    QString c5 = "";
    QString c = "";
    QString outstr = "";

    unsigned char method = 0;   //0: MT19937; 1: Mouse Move;
    unsigned char choose = 0b00000;  //xxxx_: 0~9; xxx_x: A~Z; xx_xx: a~z; x_xxx: all; _xxxx: custom;

    unsigned int length = 0;

private slots:
    unsigned int rand_num();
    void generate();
    unsigned char getc();
    void send_text(QString str);
    void outpasswd();
    unsigned char init();
    bool is_overlap(QString str1, QString str2);
    bool check();
};

#endif // WIDGET_H
