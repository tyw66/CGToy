#include "dialog.h"
#include "ui_dialog.h"

#include<QColor>
#include<QRgb>
#include<QTime>

#include "shader.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_time = 0;
    image = new QImage(W,H,QImage::Format_RGB32);

    setWindowFlags(Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setGeometry(0,0,W,H);


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::display()
{
    while(true){
        QTime t;
        t.start();


        //遍历像素点
        for(int i = 0; i < H; ++i){
            for(int j = 0; j < W; ++j){
                //获取颜色
                Color c = shader003((double)i/H, (double)j/W, m_time);
                //设置颜色
                image->setPixel(i,j,QColor::fromRgb((int)c.r, (int)c.g, (int)c.b).rgb());
            }
        }
        ui->label->setPixmap(QPixmap::fromImage(*image));
        m_time++;

        //0.1s刷新一次，并防止卡死
        while(t.elapsed() < 100){
            QCoreApplication::processEvents();
        }
    }
}


