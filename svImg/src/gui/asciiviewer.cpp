#include "asciiviewer.h"
#include <QString>

int AsciiViewer::m_time = 0;
AsciiViewer::AsciiViewer(QWidget *parent) :  QTextEdit(parent)
{
//    setMinimumSize(W,H);
//    setMaximumSize(W,H);
    setMouseTracking(true);

    items = " -*=#@";
}

void AsciiViewer::appendAscii(int c)
{
    //    append(items[c]);
}

//void AsciiViewer::draw()
//{
//    setText(data);
//}

void AsciiViewer::renderImg(int x, int y)
{
    clear();

    Color color;
#pragma omp parallel for
    //遍历像素点
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            //获取颜色
            color = shader002((double)j/W, (double)i/H, (double)x/W, (double)y/H, m_time);
            //设置颜色
            int c = color.toLightness() *0.019 - 1;// *5/255 ;
//            append(items.at(c));
        }
        append("\n");
    }


}

void AsciiViewer::mouseMoveEvent(QMouseEvent *ev)
{
    mouse_posX = ev->x();
    mouse_posY = ev->y();

    renderImg(mouse_posX, mouse_posY);
}

