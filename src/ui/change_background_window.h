#pragma once

#include <QDialog>
#include <unordered_map>
#include <QLabel>

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
    auto createImageLabel(QString) -> QLabel*;

private:

    Ui::ChangeBackgroundWindow *ui;
    std::unordered_map<QLabel*, QString> label_to_name;
};
