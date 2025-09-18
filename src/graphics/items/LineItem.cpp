#include "LineItem.h"
#include <QPainter>

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
    QPen pen(Qt::black, 2, m_preview ? Qt::DashLine : Qt::SolidLine);
    painter->setPen(pen);
    painter->drawLine(m_entity.p1(), m_entity.p2());
}
