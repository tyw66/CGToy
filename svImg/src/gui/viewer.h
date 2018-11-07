#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QObject>
#include <QWidget>
#include<QTime>
#include <QMouseEvent>
#include <QPainter>

#include "case.h"
#include "shader.h"

#include "scene.h"
class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);

    /**
     * @brief render
     * @param x 鼠标位置
     * @param y
     */
    void renderImg(int x = 0, int y = 0);

protected:
    void mouseMoveEvent(QMouseEvent* ev);

    void paintEvent(QPaintEvent* ev );


private:
    QImage* m_image;            //帧图像数据
    static unsigned int m_time;              //时间变量，动画用
    int mouse_posX, mouse_posY;


    QTime  temp_timer;          //测试用

    const int W = 256;
    const int H = 256;


    Scene *m_scene;

};

#endif // GRAPHICWIDGET_H
