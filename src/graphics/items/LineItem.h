#pragma once

#include "geometry/LineEntity.h"

#include <QGraphicsLineItem>
#include "BaseItem.h"

class NodeItem;

class LineItem : public BaseItem
{
public:
    LineItem(const QPointF& start, QGraphicsItem* parent = nullptr);

    void updatePreview(const QPointF& start, const QPointF& current) override;
    void finalize(const QPointF& endpoint = {}) override;
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
    void updateEntityPosition() override;
    void updateNodeGraphics() override;
    QPainterPath shape() const override;
    void nodeMoved(NodeItem* node, const QPointF& newPos) override;
    void setMovable(bool cond) override;
    [[nodiscard]] std::vector<NodeItem*> nodes() const override;
    void updateNode(int index, const QPointF& pos) override;
    ActiveNode findActiveNode(const QPointF& pointF) override;
    void releaseNode(int index) override;

private:
    EntityLine m_entity;
    bool m_preview = true;
    std::vector<NodeItem*> m_nodes;
};
