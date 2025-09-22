//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_GRAPHICSSCENE_H
#define QUTECAD_GRAPHICSSCENE_H

#include <QGraphicsScene>

#include "items/ItemTypes.h"

class BaseItem;

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:


    explicit GraphicsScene(QObject* parent = nullptr);

    void setDrawingMode(ItemType mode) { m_drawingMode = mode; }
    ItemType drawingMode() const { return m_drawingMode; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    QPointF findNearestNode(const QPointF& cursor, qreal snapRadius);

private:
    struct ActiveNode {
        BaseItem* item = nullptr;
        int index = -1;    // which node inside item->nodes()
    };

    ActiveNode m_activeNode;
    ItemType m_drawingMode = ItemType::None;
    QPointF m_startPoint;
    QGraphicsItem* m_previewItem = nullptr;
};

#endif // QUTECAD_GRAPHICSSCENE_H
