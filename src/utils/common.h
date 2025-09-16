//
// Created by robert on 15/09/2025.
//

#ifndef QUTECAD_COMMON_H
#define QUTECAD_COMMON_H
#include <cmath>

inline double getEuclideanDistance2d(const QPointF &p1, const QPointF &p2)
{
    const double dx = p2.x() - p1.x();
    const double dy = p2.y() - p1.y();
    return std::sqrt(dx * dx + dy * dy);
}

#endif //QUTECAD_COMMON_H
