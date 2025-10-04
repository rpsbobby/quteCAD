//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_BASEITEM_H
#define QUTECAD_BASEITEM_H
#include <QGraphicsItem>
#include <QPen>

#include "ActiveNode.h"
#include "graphics/GraphicsScene.h"

class NodeItem;

class BaseItem : public QGraphicsObject {
    Q_OBJECT
public:

    explicit BaseItem(QGraphicsItem* parent = nullptr)
        : QGraphicsObject(parent)
    {}

    ~BaseItem() override = default;

    virtual void updatePreview(const QPointF& start, const QPointF& current) = 0;
    virtual void finalize(const QPointF& endpoint = {}) = 0;
    QRectF boundingRect() const override = 0;
    QPainterPath shape() const override = 0;
    virtual void nodeMoved(class NodeItem* node, const QPointF& newPos) = 0;
    [[nodiscard]] virtual std::vector<NodeItem*> nodes() const  = 0;
    virtual void updateNode(int index, const QPointF& pos) = 0;
    virtual ActiveNode findActiveNode(const QPointF& pointF) = 0;
    virtual void releaseNode(int index) = 0;
    virtual void setMovable(bool cond) = 0;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override = 0;
    virtual void updateEntityPosition() = 0;
    virtual void updateNodeGraphics() = 0;

protected:
    static QPen stylePen(bool preview, bool selected) {
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
