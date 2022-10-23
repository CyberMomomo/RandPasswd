#include "widget.h"
#include "ui_widget.h"

#include <iostream>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->Passwd->setText("Welcome!");
    ui->Passwd->setAlignment(Qt::AlignCenter);

    connect(ui->BtnGen,SIGNAL(clicked()),this,SLOT(outpasswd()));
}

Widget::~Widget()
{
    delete ui;
}

unsigned int Widget::rand_num(){
    std::random_device rd;
    std::mt19937 num(rd());
    return num();
}

void Widget::outpasswd(){
    if(init()){
        return;
    }
    do{
        generate();
    }while(!check());

    send_text(outstr);
}

void Widget::generate(){
    outstr = "";

    for(unsigned char i = 0; i < length; i++){
        outstr += c.at(rand_num()%c.length());
    }
}

unsigned char Widget::getc(){
    c = "";
    if(choose & 0b01000){
        c = c4;
        return 0;
    }
    if(choose & 0b00001){
        c += c1;
    }
    if(choose & 0b00010){
        c += c2;
    }
    if(choose & 0b00100){
        c += c3;
    }
    if(choose & 0b10000){
        c5 = ui->CustomInput->toPlainText();
        for(unsigned char i = 0; i < c5.length(); i++){
            if(!c.contains(c5.at(i))){
                c += c5.at(i);
            }
        }
    }
    if(c==""){
        return 1;
    }
    return 0;
}

void Widget::send_text(QString str){
    ui->Passwd->setText(str);
    ui->Passwd->setAlignment(Qt::AlignCenter);
}

unsigned char Widget::init(){
    length = ui->Length->toPlainText().toInt();
    if(!length){
        send_text("No Length!!");
        return 1;
    }
    if(length > 255){
        send_text("Too Long!!");
        return 2;
    }

    choose = 0b00000;
    if(ui->Check_Num->isChecked()) choose |= 0b00001;
    if(ui->Check_Cap->isChecked()) choose |= 0b00010;
    if(ui->Check_Low->isChecked()) choose |= 0b00100;
    if(ui->Check_All->isChecked()) choose |= 0b01000;
    if(ui->Check_Cus->isChecked()) choose |= 0b10000;
    unsigned char error = getc();
    if(error==1){
        send_text("No Chose!!");
        return 3;
    }

    return 0;
}

bool Widget::is_overlap(QString str1, QString str2){
    for(unsigned int i = 0; i < str1.length(); i++){
        if(str2.contains(str1.at(i))){
            return true;
        }
    }
    return false;
}

bool Widget::check(){
    if(choose & 0b00001){
        if(!is_overlap(outstr, c1)){
            return false;
        }
    }
    if(choose & 0b00010){
        if(!is_overlap(outstr, c2)){
            return false;
        }
    }
    if(choose & 0b00100){
        if(!is_overlap(outstr, c3)){
            return false;
        }
    }
    if(choose & 0b01000){
        if(!is_overlap(outstr, c4)){
            return false;
        }
    }
    if(choose & 0b10000){
        if(!is_overlap(outstr, c5)){
            return false;
        }
    }
    return true;
}
