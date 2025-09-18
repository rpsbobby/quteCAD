//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_ITEMFACTORY_H
#define QUTECAD_ITEMFACTORY_H

#include "items/ItemTypes.h"
#include "items/LineItem.h"

class ItemFactory
{
public:
    static BaseItem* create(ItemType type, const QPointF& start);
};


#endif //QUTECAD_ITEMFACTORY_H