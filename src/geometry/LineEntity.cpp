#include "LineEntity.h"

#include "utils/common.h"

LineEntity::LineEntity(const QPointF &start, const QPointF &end)
    : m_start(start)
    , m_end(end) {}

QPointF LineEntity::start() const
{
    return m_start;
}

QPointF LineEntity::end() const
{
    return m_end;
}

double LineEntity::length() const
{
    return getEuclideanDistance2d(m_start, m_end);
}

QPointF LineEntity::midpoint() const
{
    return QPointF((m_start.x() + m_end.x()) / 2.0, (m_start.y() + m_end.y()) / 2.0);
}
