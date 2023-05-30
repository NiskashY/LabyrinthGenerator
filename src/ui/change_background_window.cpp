#include "change_background_window.h"
#include "ui_change_background_window.h"

ChangeBackgroundWindow::ChangeBackgroundWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBackgroundWindow)
{
    ui->setupUi(this);
}

ChangeBackgroundWindow::~ChangeBackgroundWindow()
{
    delete ui;
}
