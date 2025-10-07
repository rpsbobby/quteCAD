#include "LineEntity.h"

#include "graphics/items/NodeItem.h"

EntityLine::EntityLine(const QPointF& p1, const QPointF& p2) : m_p1(p1), m_p2(p2) {
}

const QPointF& EntityLine::p1() const {
    return m_p1;
}

const QPointF& EntityLine::p2() const {
    return m_p2;
}

void EntityLine::setP1(const QPointF& p) {
    m_p1 = p;
    updateDependentNodes();
}

void EntityLine::setP2(const QPointF& p) {
    m_p2 = p;
    updateDependentNodes();
}

void EntityLine::setNode(const NodeItem* nodeRef, const QPointF& newPos) {
    for (auto* node : m_nodes) {
        if (node == nodeRef && nodeRef->isMovable()) {
            node->setPosition(newPos);
            break;
        }
    }
    updateDependentNodes();
}

void EntityLine::updateDependentNodes()
{
    if (m_nodes.size() == 3) {
        const QPointF& start = m_nodes.front()->position();
        const QPointF& end   = m_nodes.back()->position();

        // recompute midpoint
        m_nodes[1]->setPosition((start + end) * 0.5);
    }
}


std::vector<NodeItem*> const EntityLine::nodes() const {
    return m_nodes;
}