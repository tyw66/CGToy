#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);
//    setAttribute(Qt::WA_DeleteOnClose);

    graphicWidget = new Viewer(this);
    layout()->addWidget(graphicWidget);

//    asciiViewer = new AsciiViewer(this);
//    layout()->addWidget(asciiViewer);

}

Dialog::~Dialog()
{
    delete ui;
}



