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
    QRectF rect(m_entity.p1(), m_entity.p2());
    // normalize (p1 could be right/bottom of p2)
    rect = rect.normalized();
    // add margin for stroke width
    rect.adjust(-30, -30, +30, +30);
    return rect;
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

    // --- DEBUG: draw shape outline ---
    QPainterPath s = shape();
    QPen debugPen(Qt::green, 1, Qt::DashLine);
    debugPen.setCosmetic(true); // always 1px, not zoom-dependent
    painter->setPen(debugPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(s);
}

QPainterPath LineItem::shape() const {
    if (m_preview || isSelected())
        return QGraphicsItem::shape();

    QPainterPath path;
    path.moveTo(m_entity.p1());
    path.lineTo(m_entity.p2());

    QPainterPathStroker stroker;
    stroker.setWidth(60.0); // thicker clickable area

    QPainterPath hitArea = stroker.createStroke(path);

    return hitArea;
}

void LineItem::nodeMoved(NodeItem* node, const QPointF& newPos) {
    prepareGeometryChange();
    node->setPos(newPos);
    if (node == m_nodes[0]) {
        m_entity.setP1(newPos);
    } else if (node == m_nodes[1]) {
        m_entity.setP2(newPos);
    }
    update();
}

void LineItem::updateNode(int index, const QPointF& pos) {
    nodeMoved(m_nodes[index], pos);
}

ActiveNode LineItem::findActiveNode(const QPointF& pos) {
    constexpr int RADIUS = 30;
    ActiveNode result;

    if (nodes().empty())
        return result;

    qreal bestDist = RADIUS;
    int bestIndex = -1;

    for (int i = 0; i < nodes().size(); ++i) {
        const auto* node = nodes()[i];
        const qreal dist = QLineF(pos, node->scenePos()).length();

        if (dist < bestDist) {
            bestDist = dist;
            bestIndex = i;
        }
    }

    if (bestIndex >= 0) {
        result.item = this;
        result.index = bestIndex;
        m_nodes[bestIndex]->setMovable(true);
    }

    return result;
}

void LineItem::releaseNode(int index) {
    if (index >= 0 && index < m_nodes.size()) {
        m_nodes[index]->setFlag(QGraphicsItem::ItemIsMovable, false);
    }
}
