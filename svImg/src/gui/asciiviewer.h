#ifndef ASCIIVIEWER_H
#define ASCIIVIEWER_H

#include <QTextEdit>
#include <QMouseEvent>

#include "case.h"
#include "shader.h"

class AsciiViewer : public QTextEdit
{
public:
    AsciiViewer(QWidget *parent = 0);

    void appendAscii(int c);

//    void draw();

    /**
     * @brief render
     * @param x 鼠标位置
     * @param y
     */
    void renderImg(int x = 0, int y = 0);

protected:
    void mouseMoveEvent(QMouseEvent* ev);


private:
    QString items;
    QString data;

    static int m_time;              //时间变量，动画用
    int mouse_posX, mouse_posY;
    const int W = 10;
    const int H = 10;

};

#endif // ASCIIVIEWER_H
