#include "mainwindow.h"

MainWidget::MainWidget(QWidget *parent) :QWidget(parent)
{
    setLayout(createMainLayout());
    this->setFixedSize(QSize(1000, 720));
    this->findChild<QPushButton*>("button_generate")->click();
    setWindowTitle(tr("Connecting buttons to processes.."));
}

auto MainWidget::createMainLayout() const -> QVBoxLayout* {
    auto v_layout_main = new QVBoxLayout();

    v_layout_main->addStretch(1);
    v_layout_main->addLayout(createMazeLayout(), 4);
    v_layout_main->addStretch(1);
    v_layout_main->addLayout(createOpenSaveLayout());
    v_layout_main->addWidget(createGenerateButton());
    v_layout_main->addLayout(createParametersLayout());

    return v_layout_main;
}

auto MainWidget::createMazeLayout() const -> QLayout* {
    auto h_layout_maze = new QHBoxLayout();
    auto g_layout_maze = new QGridLayout(); g_layout_maze->setObjectName("g_layout_maze");
    g_layout_maze->setSpacing(0);

    h_layout_maze->addStretch(1);
    h_layout_maze->addLayout(g_layout_maze, 4);
    h_layout_maze->addStretch(1);

    return h_layout_maze;
}
auto MainWidget::createGenerateButton() const -> QPushButton* {
    auto button_generate = new QPushButton("Generate");
    button_generate->setObjectName(STR_NAME(button_generate));
    connect(button_generate, &QPushButton::clicked,
            this, &MainWidget::setupLabyrinthUi);
    return button_generate;
}

auto MainWidget::createParametersLayout() const -> QLayout* {
    auto params_layout = new QHBoxLayout();
    auto input_height = new QLineEdit("50"); input_height->setObjectName("input_height");
    auto input_width  = new QLineEdit("50"); input_width->setObjectName("input_width");

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
    h_layout_open_save->addWidget(new QPushButton(tr("Open")));
    h_layout_open_save->addWidget(new QPushButton(tr("Save")));
    return h_layout_open_save;
}

auto MainWidget::hide(QGridLayout* gl, size_t row, size_t col) const -> void {
    auto rows = gl->rowCount();
    auto cols = gl->columnCount();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            const auto& item = gl->itemAtPosition(i, j);
            if (item && item->widget()) {
                item->widget()->hide();
            }
        }
    }
}

auto MainWidget::setupLabyrinthUi() -> void {
    // TODO: create validator
    auto str_height = this->findChild<QLineEdit*>("input_height")->text();
    auto str_width  = this->findChild<QLineEdit*>("input_width")->text();

    if (str_height.isEmpty() || str_width.isEmpty()) {
        return;
    }

    maze.create(str_height.toInt(), str_width.toInt());

    auto g_layout_labyrinth = this->findChildren<QGridLayout*>("g_layout_maze")[0];
    //  hide(g_layout_labyrinth, maze.getRows(), maze.getColumns());    TODO: (?) может разделить на потоки, чтобы быстрее было?

    for (int i = 0; i < maze.getRows(); ++i) {
        for (int j = 0; j < maze.getColumns(); ++j) {
            auto [right, bottom] = maze.get(i, j);
            auto item = g_layout_labyrinth->itemAtPosition(i, j);
            if (item == nullptr) {
                auto frame = new QLabel();
                frame->setStyleSheet(createCellQss(bottom, i, j, right));
                g_layout_labyrinth->addWidget(frame, i, j);
            } else {
                item->widget()->show();
                item->widget()->setStyleSheet(createCellQss(bottom, i, j, right));
            }
        }
    }

}

auto MainWidget::createCellQss(bool bottom, int top, int left, bool right) const -> QString {
    // bootom, right -> depends on the algorithm parameters
    // top, left     -> depends on the cell position
    static const QString border_side = "border-%1: 2px solid white;";

    QString command = "background-color: #27074B;";
    if (bottom)    command += border_side.arg("bottom");
    if (right)     command += border_side.arg("right");
    if (left == 0) command += border_side.arg("left");
    if (top == 0)  command += border_side.arg("top");

    return command;
}