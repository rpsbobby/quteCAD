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

constexpr float RADIUS{30.0};

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (m_drawingMode != ItemType::None) {
        qDebug() << "Starting to draw item of type" << static_cast<int>(m_drawingMode);
        m_startPoint = findNearestNode(event->scenePos(), RADIUS);
        m_previewItem = ItemFactory::create(m_drawingMode, m_startPoint);
        if (m_previewItem)
            addItem(m_previewItem);
        qDebug() << "No preview item found";
    }
    if (m_drawingMode == ItemType::None) {
        m_activeNode = findNodeAt(event->scenePos(), RADIUS);
    }

    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (m_previewItem) {
        dynamic_cast<BaseItem*>(m_previewItem)->updatePreview(m_startPoint, event->scenePos());
    }
    if (m_activeNode.item) {
        QPointF newPos = event->scenePos();
        m_activeNode.item->updateNode(m_activeNode.index, newPos);
    }

    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (m_previewItem) {
        qDebug() << "convert from preview (dashed) to final (solid)";
        if (auto* item = dynamic_cast<BaseItem*>(m_previewItem)) {
            auto endPoint = findNearestNode(event->scenePos(), RADIUS);
            item->finalize(endPoint); // toggles from dashed to solid
        }
        m_previewItem = nullptr;
        m_drawingMode = ItemType::None; // Exit drawing mode after one item
    }
    if (m_drawingMode == ItemType::None && m_activeNode.item) {
        const QPointF snapped = findNearestNode(event->scenePos(), RADIUS, m_activeNode.item, m_activeNode.index);
        m_activeNode.item->updateNode(m_activeNode.index, snapped);
        m_activeNode = {};
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

QPointF GraphicsScene::findNearestNode(const QPointF& cursor, qreal snapRadius, const BaseItem* activeItem,
                                       int activeIndex) const {
    QPointF best{};
    qreal bestDist = snapRadius;

    for (auto* item : items()) {
        if (const auto* base = dynamic_cast<BaseItem*>(item)) {
            auto nodes = base->nodes();
            for (int i = 0; i < nodes.size(); ++i) {
                // skip the node we’re actively moving
                if (base == activeItem && i == activeIndex)
                    continue;

                const qreal dist = QLineF(cursor, nodes[i]->scenePos()).length();
                qDebug() << "Distance to node at" << nodes[i]->scenePos() << "is" << dist;
                if (dist < bestDist) {
                    bestDist = dist;
                    best = nodes[i]->scenePos();
                }
            }
        }
    }

    if (bestDist < snapRadius)
        return best;

    return cursor;
}


GraphicsScene::ActiveNode GraphicsScene::findNodeAt(const QPointF& pos, qreal radius) const {
    ActiveNode result;
    qreal bestDist = radius;

    for (auto* item : items()) {
        if (auto* base = dynamic_cast<BaseItem*>(item)) {
            if (m_activeNode.item == base)
                continue;
            auto nodes = base->nodes();
            for (int i = 0; i < nodes.size(); ++i) {
                qreal dist = QLineF(pos, nodes[i]->scenePos()).length();
                if (dist < bestDist) {
                    bestDist = dist;
                    result = {base, i};
                }
            }
        }
    }

    return result;
}