#include "GraphicsScene.h"

#include "items/LineItem.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

#include "ItemFactory.h"


GraphicsScene::GraphicsScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(-500, -500, 1000, 1000); // example scene size
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_drawingMode != ItemType::None)
    {
        qDebug() << "Starting to draw item of type" << static_cast<int>(m_drawingMode);
        m_startPoint = event->scenePos();
        m_previewItem = ItemFactory::create(static_cast<ItemType>(m_drawingMode), m_startPoint);
        if (m_previewItem) addItem(m_previewItem);
        else
            qDebug() << "No preview item found";
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_previewItem) {
        dynamic_cast<BaseItem*>(m_previewItem)->updatePreview(m_startPoint, event->scenePos());
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_previewItem) {
        qDebug() << "convert from preview (dashed) to final (solid)";
        if (auto* item = dynamic_cast<BaseItem*>(m_previewItem)) {
            item->finalize();   // toggles from dashed to solid
        }
        m_previewItem = nullptr;
        m_drawingMode = ItemType::None; // Exit drawing mode after one item
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
