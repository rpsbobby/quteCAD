//
// Created by robert on 15/09/2025.
//

#ifndef QUTECAD_LINE_ENTITY_H
#define QUTECAD_LINE_ENTITY_H
#include <QPointF>
#include <vector>

class NodeItem;

class EntityLine {
public:
    EntityLine(const QPointF& p1, const QPointF& p2);

    [[nodiscard]] qreal length() const;
    [[nodiscard]] qreal angle() const;

    [[nodiscard]] const QPointF& p1() const;
    [[nodiscard]] const QPointF& p2() const;
    void setP1(const QPointF& p);
    void setP2(const QPointF& p);
    void setNode(const NodeItem*, const QPointF& newPos);
    void updateDependentNodes();
    [[nodiscard]] std::vector<NodeItem *> const nodes() const;
private:
    QPointF m_p1, m_p2; // kept for reference (for now)
    std::vector<NodeItem *> m_nodes;
};
#endif //QUTECAD_LINE_ENTITY_H
