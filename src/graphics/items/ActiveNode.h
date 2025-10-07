//
// Created by robert on 02/10/2025.
//

#ifndef QUTECAD_ACTIVENODE_H
#define QUTECAD_ACTIVENODE_H

class NodeItem;
class BaseItem;

struct ActiveNode {
    BaseItem* item = nullptr;
    NodeItem* node = nullptr; // which node inside item->nodes()
    ~ActiveNode();
};



#endif //QUTECAD_ACTIVENODE_H