#include "dialog.h"
#include "ui_dialog.h"

#include<QColor>
#include<QRgb>

#include <QPainter>
#include <QDebug>

int Dialog::m_time = 0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_paint, SIGNAL(clicked()), this,SLOT(onPlay()));
    ui->pushButton_paint->setVisible(false);
    setWindowFlags(Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setMinimumSize(W,H);
    setMaximumSize(W,H);
    setMouseTracking(true);

    m_image = new QImage(W,H,QImage::Format_RGB32);

    render(W/2,H/2);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::render(int x, int y)
{
    temp_timer.restart();
    #pragma omp parallel for
    //遍历像素点
    for(int i = 0; i < H; ++i){
        for(int j = 0; j < W; ++j){
            //获取颜色
            Color color = case002((double)j/W, (double)i/H, (double)x/W, (double)y/H, m_time);
            //设置颜色
            m_image->setPixel(j,i,QColor::fromRgb((int)color.r, (int)color.g, (int)color.b).rgb());
        }
    }
    update();
    //    m_time++;

    qDebug()<< temp_timer.elapsed();
}

void Dialog::mouseMoveEvent(QMouseEvent *ev)
{
    mouse_posX = ev->x();
    mouse_posY = ev->y();

    render(mouse_posX, mouse_posY);
}

void Dialog::paintEvent(QPaintEvent *ev)
{
    QPainter p(this);
    p.drawImage(ev->rect(),*m_image);
}




void Dialog::onPlay()
{
    while(true){
        m_timer.restart();
        render(mouse_posX, mouse_posY);

        //0.1s刷新一次，并防止卡死
        while(m_timer.elapsed() < 100){
            QCoreApplication::processEvents();
        }


    }
}

