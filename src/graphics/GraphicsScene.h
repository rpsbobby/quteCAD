//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_GRAPHICSSCENE_H
#define QUTECAD_GRAPHICSSCENE_H

#include <QGraphicsScene>

#include "items/ActiveNode.h"
#include "items/ItemTypes.h"

class NodeItem;
class BaseItem;

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT

public:
    explicit GraphicsScene(QObject* parent = nullptr);

    void setDrawingMode(ItemType mode) { m_drawingMode = mode; }
    ItemType drawingMode() const { return m_drawingMode; }
    QPointF findNearestNode(const QPointF& cursor, qreal snapRadius, const BaseItem* activeItem = nullptr, int activeIndex = -1) const;

protected:
    void setItemsMovable(bool cond) const;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:


    ActiveNode m_activeNode;
    ItemType m_drawingMode = ItemType::Select;
    QPointF m_startPoint;
    QGraphicsItem* m_previewItem = nullptr;
    QPointF m_currentNode = {};
};

#endif // QUTECAD_GRAPHICSSCENE_H