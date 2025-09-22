#include "LineItem.h"
#include <QPainter>

#include "NodeItem.h"

LineItem::LineItem(const QPointF& start, QGraphicsItem* parent)
    : BaseItem(parent), m_entity(start, start) {
}

void LineItem::updatePreview(const QPointF& start, const QPointF& current) {
    m_entity = EntityLine(start, current);
    prepareGeometryChange();
}

void LineItem::finalize(const QPointF& endpoint) {
    m_preview = false;
    m_nodes.push_back(new NodeItem(m_entity.p1(), this));
    m_entity.setP2(endpoint);
    m_nodes.push_back(new NodeItem(endpoint, this));
    update();
}

QRectF LineItem::boundingRect() const {
    return QRectF(m_entity.p1(), m_entity.p2()).normalized();
}

void LineItem::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget*) {
    painter->setPen(stylePen(m_preview, isSelected()));
    painter->drawLine(m_entity.p1(), m_entity.p2());
    if (!m_preview && !isSelected()) {
        painter->setBrush(Qt::blue);
        painter->setPen(Qt::NoPen);

        for (const auto& node : m_entity.nodes()) {
            painter->drawEllipse(node, 3, 3);
        }
    }
}

QPainterPath LineItem::shape() const {
    if (m_preview || isSelected())
        return QGraphicsItem::shape();

    QPainterPath path;
    path.moveTo(m_entity.p1());
    path.lineTo(m_entity.p2());

    QPainterPathStroker stroker;
    stroker.setWidth(6.0); // thinner hit area
    return stroker.createStroke(path);
}

void LineItem::nodeMoved(NodeItem* node, const QPointF& newPos) {
    prepareGeometryChange();
    if (node == m_nodes[0]) {
        m_entity.setP1(newPos);
    } else if (node == m_nodes[1]) {
        m_entity.setP2(newPos);
    }
    update();
}

void LineItem::updateNode(int index, const QPointF& pos) {
    m_nodes[index]->setPos(pos);
    nodeMoved(m_nodes[index], pos);
}