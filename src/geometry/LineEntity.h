//
// Created by robert on 15/09/2025.
//

#ifndef QUTECAD_LINE_ENTITY_H
#define QUTECAD_LINE_ENTITY_H
#include <QPointF>

class EntityLine {
public:
    EntityLine(const QPointF& p1, const QPointF& p2);

    [[nodiscard]] qreal length() const;
    [[nodiscard]] qreal angle() const;

    [[nodiscard]] const QPointF& p1() const;
    [[nodiscard]] const QPointF& p2() const;
    void setP2(const QPointF& p);

private:
    QPointF m_p1, m_p2;
};
#endif //QUTECAD_LINE_ENTITY_H
