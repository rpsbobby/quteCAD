//
// Created by robert on 18/09/2025.
//

#include "GraphicsView.h"
#include "GraphicsView.h"
#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    constexpr double scaleFactor = 1.15;
    if ( event->angleDelta().y() > 0 ) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}
