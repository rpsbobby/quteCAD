//
// Created by robert on 20/09/2025.
//

#ifndef QUTECAD_NODEITEM_H
#define QUTECAD_NODEITEM_H

#include <QGraphicsEllipseItem>
#include <qbrush.h>

#include "BaseItem.h"


class NodeItem : public QGraphicsEllipseItem
{
public :
    explicit NodeItem(const QPointF& position, QGraphicsItem* parent = nullptr)
        : QGraphicsEllipseItem(-3, -3, 6, 6, parent)
    {
        setPos(position);
        setBrush(Qt::darkBlue);
        setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    }



    QPainterPath shape() const override
    {
        QPainterPath path;
        // Make selection area bigger than the painted circle
        path.addEllipse(-8, -8, 16, 16); // interactive area
        return path;
    }

    void setMovable(const bool movable) {
        setFlag(QGraphicsItem::ItemIsMovable, movable);
    }
};
#endif //QUTECAD_NODEITEM_H
