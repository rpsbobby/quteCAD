//
// Created by robert on 20/09/2025.
//

#ifndef QUTECAD_NODEITEM_H
#define QUTECAD_NODEITEM_H
#include <qbrush.h>
#include <QGraphicsEllipseItem>


class NodeItem: public QGraphicsEllipseItem
{
public :
    explicit NodeItem(const QPointF& position, QGraphicsItem* parent = nullptr)
        : QGraphicsEllipseItem(-3, -3, 6, 6, parent)
    {
        setPos(position);
        setBrush(Qt::blue);
        setFlag(QGraphicsItem::ItemIsMovable);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }
};
#endif //QUTECAD_NODEITEM_H