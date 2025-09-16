//
// Created by robert on 15/09/2025.
//

#ifndef QUTECAD_LINE_ENTITY_H
#define QUTECAD_LINE_ENTITY_H
#include <QPointF>


class LineEntity
{
    public:
        LineEntity(const QPointF &start, const QPointF &end);

        QPointF start() const;

        QPointF end() const;

        double length() const;

        QPointF midpoint() const;

    private:
        QPointF m_start;
        QPointF m_end;
};
#endif //QUTECAD_LINE_ENTITY_H
