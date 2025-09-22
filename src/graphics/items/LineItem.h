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
    QPainterPath shape() const;
    void nodeMoved(NodeItem* node, const QPointF& newPos) override;
    [[nodiscard]] std::vector<NodeItem*> nodes() const override { return m_nodes; }
    void updateNode(int index, const QPointF& pos) override;
private:
    EntityLine m_entity;
    bool m_preview = true;
    std::vector<NodeItem*> m_nodes;
};
