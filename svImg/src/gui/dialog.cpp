#include "dialog.h"
#include "ui_dialog.h"

#include<QColor>
#include<QRgb>
#include "shader.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

time=1;
    image = new QImage(W,H,QImage::Format_RGB32);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    while (true) {
        time = -time;
        //    unsigned char img[W*H*3];
        //遍历像素点
        for(int i = 0; i < H; ++i){
            for(int j = 0; j < W; ++j){
                //像素点着色
                Color c = shader02((double)i/H,(double)j/W,time);

                QRgb rgb = QColor::fromRgb((int)c.r, (int)c.g, (int)c.b).rgb();
                image->setPixel(i,j,rgb);
                ui->label->setPixmap(QPixmap::fromImage(*image));
            }
        }

    }
}

void Dialog::on_pushButton_2_clicked()
{
    qApp->quit();
}
