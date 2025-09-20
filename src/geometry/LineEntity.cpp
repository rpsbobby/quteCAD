#include "LineEntity.h"

#include "utils/common.h"

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
