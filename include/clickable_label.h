#pragma once

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class ClickableLabel : public QLabel
{
    Q_OBJECT
signals:
    void mousePressed( const QPoint& );

public:
    ClickableLabel( QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    ClickableLabel( const QString& text, QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

    void mousePressEvent( QMouseEvent* ev );
};
