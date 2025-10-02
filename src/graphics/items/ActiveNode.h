//
// Created by robert on 02/10/2025.
//

#ifndef QUTECAD_ACTIVENODE_H
#define QUTECAD_ACTIVENODE_H


class BaseItem;

struct ActiveNode {
    BaseItem* item = nullptr;
    int index = -1; // which node inside item->nodes()
    ~ActiveNode();
};



#endif //QUTECAD_ACTIVENODE_H