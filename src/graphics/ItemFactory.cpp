//
// Created by robert on 18/09/2025.
//

#include "ItemFactory.h"

BaseItem* ItemFactory::create(ItemType type, const QPointF& start)
{
    switch (type) {
    case ItemType::Line:
        return new LineItem(start);
    default:
        return nullptr;
    }
}
