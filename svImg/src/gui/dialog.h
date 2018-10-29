#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "viewer.h"
#include "asciiviewer.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    Viewer * graphicWidget;
    AsciiViewer* asciiViewer;

};

#endif // DIALOG_H
