#pragma once

#include "geometry/LineEntity.h"

#include <QGraphicsLineItem>
#include "BaseItem.h"

class NodeItem;

class LineItem : public BaseItem {
public:
    LineItem(const QPointF& start, QGraphicsItem* parent = nullptr);

    void updatePreview(const QPointF& start, const QPointF& current) override;
    void finalize() override;

    QRectF boundingRect() const override;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget) override;

private:
    EntityLine m_entity;
    bool m_preview = true;
    std::vector<NodeItem*> m_nodes;
};
