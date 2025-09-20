#include "LineItem.h"
#include <QPainter>

#include "NodeItem.h"

LineItem::LineItem(const QPointF& start, QGraphicsItem* parent)
    : BaseItem(parent), m_entity(start, start)
{
}

void LineItem::updatePreview(const QPointF& start, const QPointF& current)
{
    m_entity = EntityLine(start, current);
    prepareGeometryChange();
}

void LineItem::finalize()
{
    m_preview = false;
    m_nodes.push_back(new NodeItem(m_entity.p1(), this));
    m_nodes.push_back(new NodeItem(m_entity.p2(), this));
    update();
}

QRectF LineItem::boundingRect() const
{
    return QRectF(m_entity.p1(), m_entity.p2()).normalized();
}

void LineItem::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem*,
                     QWidget*)
{
    painter->setPen(stylePen(m_preview, isSelected()));
    painter->drawLine(m_entity.p1(), m_entity.p2());
}
