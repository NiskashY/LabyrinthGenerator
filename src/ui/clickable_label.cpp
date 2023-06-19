#include <clickable_label.h>

ClickableLabel::ClickableLabel(QWidget * parent, Qt::WindowFlags f): QLabel(parent, f) {}

void ClickableLabel::mousePressEvent( QMouseEvent* ev ) {
    emit mousePressed(ev->position());
}
