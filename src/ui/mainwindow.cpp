#include "mainwindow.h"
#include <QtWidgets>
#include <QGridLayout>
#include <QPixmap>

MainWidget::MainWidget(QWidget *parent) :QWidget(parent)
{
    button = std::make_shared<QPushButton>(tr("Push Me!"));
    textBrowser = std::make_shared<QTextBrowser>();

    auto v_layout_main = new QVBoxLayout(this);
    auto button_generate = new QPushButton("Generate");

    connect(button_generate, &QPushButton::clicked,
            this, &MainWidget::setupLabyrinthUi);


    v_layout_main->addLayout(new QGridLayout());
    v_layout_main->addStretch(1);
    v_layout_main->addLayout(createOpenSaveLayout());
    v_layout_main->addWidget(button_generate);
    v_layout_main->addLayout(createParametersLayout());

    setLayout(v_layout_main);
    setWindowTitle(tr("Connecting buttons to processes.."));
}


auto MainWidget::createParametersLayout() const -> QLayout* {
    auto params_layout = new QHBoxLayout();
    auto input_height = new QLineEdit();
    auto input_width  = new QLineEdit();

    input_height->setPlaceholderText(tr("Input height"));
    input_width->setPlaceholderText(tr("Input width"));

    params_layout->addStretch(1);
    params_layout->addWidget(input_height);
    params_layout->addStretch(1);
    params_layout->addWidget(input_width);
    params_layout->addStretch(1);

    return params_layout;
}

auto MainWidget::createOpenSaveLayout() const -> QLayout* {
    auto h_layout_open_save  = new QHBoxLayout();
    h_layout_open_save->addWidget(new QPushButton("Open"));
    h_layout_open_save->addWidget(new QPushButton("Save"));
    return h_layout_open_save;
}

auto MainWidget::setupLabyrinthUi() -> void {
    // TODO: move this to separate funciton
    static constexpr size_t kDemoSize = 5;
    maze.resize(kDemoSize, kDemoSize);
    maze.generate();

    auto g_layout_labyrinth = dynamic_cast<QGridLayout*>(
        this->layout()->itemAt(0)
    );

    for (int i = 0; i < maze.getRows(); ++i) {
        for (int j = 0; j < maze.getColumns(); ++j) {
            auto [right, bottom] = maze.get(i, j);
            auto frame = new QLabel(this);

            frame->setStyleSheet(createCellQss(bottom, i, j, right) + "background-color: #27074B;");
            frame->setFixedHeight(100); // TODO:     get current window height -> set cell parameters
            frame->setFixedWidth(100);  // TODO:     get current window width  -> set cell parameters
            
            g_layout_labyrinth->addWidget(frame, i, j);
        }
    }
}

auto MainWidget::createCellQss(bool bottom, int top, int left, bool right) const -> QString {
    // bootom, right -> depends on the algorithm parameters
    // top, left     -> depends on the cell position
    static const QString border_side = "border-%1: 2px solid white;";

    QString command;
    if (bottom)    command += border_side.arg("bottom");
    if (right)     command += border_side.arg("right");
    if (left == 0) command += border_side.arg("left");
    if (top == 0)  command += border_side.arg("top");

    return command;
}