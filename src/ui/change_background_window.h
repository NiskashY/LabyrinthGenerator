#ifndef CHANGE_BACKGROUND_WINDOW_H
#define CHANGE_BACKGROUND_WINDOW_H

#include <QDialog>

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

#endif // CHANGE_BACKGROUND_WINDOW_H
