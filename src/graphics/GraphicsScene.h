//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_GRAPHICSSCENE_H
#define QUTECAD_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include  <QPointer>

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
    QPointF findNearestNode(const QPointF& cursor, qreal snapRadius, const BaseItem* activeItem = nullptr,
                            const NodeItem* activeNode = nullptr) const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private slots:
    void setItemsMovable(bool cond) const;
signals:
    void signalSetItemsMovable(bool cond);

private:
    ActiveNode m_activeNode;
    ItemType m_drawingMode = ItemType::Select;
    QPointF m_startPoint;
    QPointer<BaseItem> m_previewItem = {};
    QPointF m_currentNode = {};
};
#endif // QUTECAD_GRAPHICSSCENE_H