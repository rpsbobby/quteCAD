//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_BASEITEM_H
#define QUTECAD_BASEITEM_H
#include <QGraphicsItem>


class BaseItem : public QGraphicsItem {
public:

    explicit BaseItem(QGraphicsItem* parent = nullptr)
        : QGraphicsItem(parent) {}

    virtual ~BaseItem() = default;

    virtual void updatePreview(const QPointF& start, const QPointF& current) = 0;
    virtual void finalize() = 0;
};
#endif //QUTECAD_BASEITEM_H
