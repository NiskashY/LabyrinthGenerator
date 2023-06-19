#pragma once

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class ClickableLabel : public QLabel
{
    Q_OBJECT
signals:
    void mousePressed( const QPointF& );

public:
    ClickableLabel( QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void mousePressEvent(QMouseEvent* ev) override;
};
