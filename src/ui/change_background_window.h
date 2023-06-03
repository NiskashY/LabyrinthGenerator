#pragma once

#include <QDialog>
#include <flowlayout.h> // TODO:

namespace Ui {
class ChangeBackgroundWindow;
}

class ChangeBackgroundWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeBackgroundWindow(QWidget *parent = nullptr);
    ~ChangeBackgroundWindow();

private:
    Ui::ChangeBackgroundWindow *ui;
};
