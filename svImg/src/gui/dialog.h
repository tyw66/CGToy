#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QTime>
#include <QMouseEvent>


#include "case.h"
#include "shader.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    /**
     * @brief render
     * @param x 鼠标位置
     * @param y
     */
    void render(int x = 0, int y = 0);

public slots:
    void onPlay();

protected:
    void mouseMoveEvent(QMouseEvent* ev);

    void paintEvent(QPaintEvent* ev );


private:
    Ui::Dialog *ui;

    QImage* m_image;            //帧图像数据
    static int m_time;              //时间变量，动画用
    int mouse_posX, mouse_posY;


    QTime m_timer;                  //动画用
    QTime  temp_timer;          //测试用

    const int W = 256;
    const int H = 256;


};

#endif // DIALOG_H
