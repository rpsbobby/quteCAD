#include "GraphicsScene.h"

#include "items/LineItem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "ItemFactory.h"
#include "items/NodeItem.h"


GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent) {
    setSceneRect(-500, -500, 1000, 1000); // example scene size
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (m_drawingMode != ItemType::None) {
        qDebug() << "Starting to draw item of type" << static_cast<int>(m_drawingMode);
        m_startPoint = findNearestNode(event->scenePos(), 30.0);
        m_previewItem = ItemFactory::create(m_drawingMode, m_startPoint);
        if (m_previewItem)
            addItem(m_previewItem);
        else
            qDebug() << "No preview item found";
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (m_previewItem) {
        dynamic_cast<BaseItem*>(m_previewItem)->updatePreview(m_startPoint, event->scenePos());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (m_previewItem) {
        qDebug() << "convert from preview (dashed) to final (solid)";
        if (auto* item = dynamic_cast<BaseItem*>(m_previewItem)) {
            auto endPoint = findNearestNode(event->scenePos(), 30.0);
            item->finalize(endPoint); // toggles from dashed to solid
        }
        m_previewItem = nullptr;
        m_drawingMode = ItemType::None; // Exit drawing mode after one item
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

QPointF GraphicsScene::findNearestNode(const QPointF& cursor, qreal snapRadius) {
    QPointF best{};
    qreal bestDist = snapRadius;

    for (auto* item : items()) {
        if (auto* base = dynamic_cast<BaseItem*>(item)) {
            for (auto const* node : base->nodes()) {
                qreal dist = QLineF(cursor, node->pos()).length();
                qDebug() << "Distance to node at" << node->pos() << "is" << dist;
                if (dist < bestDist) {
                    bestDist = dist;
                    best = node->pos();
                }
            }
        }
    }

    return (bestDist < snapRadius ? best : cursor);
}