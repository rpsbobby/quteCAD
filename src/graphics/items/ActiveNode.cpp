//
// Created by robert on 02/10/2025.
//

#include "ActiveNode.h"
#include "BaseItem.h"

ActiveNode::~ActiveNode() {
    if (item && index >= 0) {
        item->releaseNode(index);
    }
}