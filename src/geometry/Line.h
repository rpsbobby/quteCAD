//
// Created by robert on 15/09/2025.
//

#ifndef QUTECAD_LINE_H
#define QUTECAD_LINE_H
#include "utils/common.h"

class Line
{
    public:
    explicit Line(const Point &start, const Point &end);
    ~Line() = default;


    private:
        Point start;
        Point end;
};

#endif //QUTECAD_LINE_H
