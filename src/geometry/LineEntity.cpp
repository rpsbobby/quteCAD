#include "LineEntity.h"

EntityLine::EntityLine(const QPointF& p1, const QPointF& p2) : m_p1(p1), m_p2(p2)
{
}

const QPointF& EntityLine::p1() const
{
    return m_p1;
}

const QPointF& EntityLine::p2() const
{
    return m_p2;
}

void EntityLine::setP1(const QPointF& p)
{
    m_p1 = p;
}

void EntityLine::setP2(const QPointF& p)
{
    m_p2 = p;
}

void EntityLine::setNode(int index, const QPointF& pos) {
    switch (index) {
        case 0:
            setP1(pos);
            break;
        case 1:
            setP2(pos);
            break;
        default:
            break;
    }
}

std::vector<QPointF> EntityLine::nodes() const
{
    std::vector<QPointF> result;
    result.push_back(m_p1);
    result.push_back(m_p2);

    // add midpoint
    result.push_back((m_p1 + m_p2) / 2.0);

    return result;
}
