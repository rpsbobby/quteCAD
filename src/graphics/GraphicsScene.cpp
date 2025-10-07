#include "GraphicsScene.h"

#include "items/LineItem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "ItemFactory.h"
#include "items/NodeItem.h"

constexpr float RADIUS{30.0};

GraphicsScene::GraphicsScene(QObject* parent)
    : QGraphicsScene(parent) {
    setSceneRect(-500, -500, 1000, 1000); // example scene size
    connect(this, &GraphicsScene::signalSetItemsMovable, this, &GraphicsScene::setItemsMovable);
}

QPointF GraphicsScene::findNearestNode(const QPointF& cursor, qreal snapRadius, const BaseItem* activeItem,
                                       const NodeItem* activeNode ) const {
    QPointF best{};
    qreal bestDist = snapRadius;

    for (auto* item : items()) {
        if (const auto* base = dynamic_cast<BaseItem*>(item)) {
            auto nodes = base->nodes();
            for (int i = 0; i < nodes.size(); ++i) {
                // skip the node we’re actively moving
                if (base == activeItem && nodes[i] == activeNode)
                    continue;

                const qreal dist = QLineF(cursor, nodes[i]->position()).length();
                qDebug() << "Distance to node at" << nodes[i]->position() << "is" << dist;
                if (dist < bestDist) {
                    bestDist = dist;
                    best = nodes[i]->position();
                }
            }
        }
    }

    if (bestDist < snapRadius)
        return best;

    return cursor;
}

void GraphicsScene::setItemsMovable(bool cond) const {
    for (auto* item : items()) {
        if (auto* base = dynamic_cast<BaseItem*>(item)) {
            base->setMovable(cond);
        }
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mousePressEvent(event);
    if (m_drawingMode != ItemType::Select) {
        setItemsMovable(false);
        qDebug() << "Starting to draw item of type" << static_cast<int>(m_drawingMode);
        m_startPoint = findNearestNode(event->scenePos(), RADIUS);
        m_previewItem = ItemFactory::create(m_drawingMode, m_startPoint);
        if (m_previewItem)
            addItem(m_previewItem);

        // convert the start point into item-local coordinates
        if (m_previewItem)
            m_startPoint = m_previewItem->mapFromScene(m_startPoint);
    }
    if (m_drawingMode == ItemType::Select) {
        if (!this->selectedItems().isEmpty()) {
            for (auto* item : this->selectedItems()) {
                if (auto* base = qgraphicsitem_cast<BaseItem*>(item)) {
                    m_activeNode = base->findActiveNode(event->scenePos());
                }
            }
            if (m_activeNode.item) {
                m_activeNode.item->setSelected(false);
                m_activeNode.item->setFlag(QGraphicsItem::ItemIsMovable, false);
                m_activeNode.item->updateNode(m_activeNode.node, m_activeNode.item->mapFromScene(event->scenePos()));
            }
        }
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (m_previewItem) {
        m_previewItem->updatePreview(m_startPoint, m_previewItem->mapFromScene(event->scenePos()));
    }
    if (m_activeNode.item) {
        QPointF newPos = m_activeNode.item->mapFromScene(event->scenePos());
        m_activeNode.item->updateNode(m_activeNode.node, newPos);
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (m_previewItem) {
        qDebug() << "convert from preview (dashed) to final (solid)";
        auto endPoint = findNearestNode(event->scenePos(), RADIUS);
        m_previewItem->finalize(m_previewItem->mapFromScene(endPoint)); // toggles from dashed to solid

        m_previewItem.clear();
    }
    if (m_drawingMode == ItemType::Select && m_activeNode.item) {
        const QPointF snapped = findNearestNode(event->scenePos(), RADIUS, m_activeNode.item, m_activeNode.node);
        m_activeNode.item->updateNode(m_activeNode.node, snapped);
        m_activeNode.item->setFlag(QGraphicsItem::ItemIsMovable, true);
        m_activeNode = {};
    }
    m_drawingMode = ItemType::Select; // Exit drawing mode after one item
    emit signalSetItemsMovable(true); //setItemsMovable(true);
    QGraphicsScene::mouseReleaseEvent(event);
}