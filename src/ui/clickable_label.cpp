#include <clickable_label.h>

void ClickableLabel::mousePressEvent( QMouseEvent* ev )
{
    const QPoint p = ev->pos();
    emit mousePressed( p );
}

ClickableLabel::ClickableLabel( QWidget * parent, Qt::WindowFlags f )
    : QLabel( parent, f ) {}

ClickableLabel::ClickableLabel( const QString& text, QWidget* parent, Qt::WindowFlags f )
    : QLabel( text, parent, f ) {}
