//
// Created by robert on 20/09/2025.
//

#ifndef QUTECAD_NODEITEM_H
#define QUTECAD_NODEITEM_H

#include <QPointF>

class NodeItem final {
    QPointF m_position;

public :
    explicit NodeItem(const QPointF& position);
    void setPosition(const QPointF& newPosition);
    QPointF position() const;
    bool isMovable() const;
};
#endif //QUTECAD_NODEITEM_H