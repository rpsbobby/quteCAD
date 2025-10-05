
#include "NodeItem.h"

NodeItem::NodeItem(const QPointF& position) : m_position(position) {
}

void NodeItem::setPosition(const QPointF& newPosition) {
    m_position = newPosition;
}

QPointF NodeItem::position() const {
    return m_position;
}