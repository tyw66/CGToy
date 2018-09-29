#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void display();


private:
    Ui::Dialog *ui;
    QImage* image;
    int m_time;

    const int W = 256;
    const int H = 256;

};

#endif // DIALOG_H
