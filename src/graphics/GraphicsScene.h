//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_GRAPHICSSCENE_H
#define QUTECAD_GRAPHICSSCENE_H

#include <QGraphicsScene>

#include "items/ItemTypes.h"

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

private:
    ItemType m_drawingMode = ItemType::None;
    QPointF m_startPoint;
    QGraphicsItem* m_previewItem = nullptr;
};

#endif // QUTECAD_GRAPHICSSCENE_H
