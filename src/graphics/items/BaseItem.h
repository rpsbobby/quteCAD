//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_BASEITEM_H
#define QUTECAD_BASEITEM_H
#include <QGraphicsItem>
#include <QPen>

class NodeItem;

class BaseItem : public QGraphicsItem {
public:

    explicit BaseItem(QGraphicsItem* parent = nullptr)
        : QGraphicsItem(parent)
    {
        setFlags(QGraphicsItem::ItemIsSelectable |
                 QGraphicsItem::ItemIsMovable);
    }

    virtual ~BaseItem() = default;

    virtual void updatePreview(const QPointF& start, const QPointF& current) = 0;
    virtual void finalize() = 0;
    virtual QRectF boundingRect() const = 0;
    virtual QPainterPath shape() const = 0;
    virtual void nodeMoved(class NodeItem* node, const QPointF& newPos) = 0;

protected:
    QPen stylePen(bool preview, bool selected) const {
        if (preview) {
            return QPen(Qt::black, 2, Qt::DashLine);
        }
        if (selected) {
            return QPen(Qt::red, 2, Qt::DashLine);
        }
        return QPen(Qt::black, 2, Qt::SolidLine);
    }
};
#endif //QUTECAD_BASEITEM_H
