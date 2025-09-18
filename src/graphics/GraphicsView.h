//
// Created by robert on 18/09/2025.
//

#ifndef QUTECAD_GRAPHICSVIEW_H
#define QUTECAD_GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
        Q_OBJECT public:
        explicit GraphicsView(QWidget *parent = nullptr);

    protected:
        void wheelEvent(QWheelEvent *event) override;
};

#endif //QUTECAD_GRAPHICSVIEW_H
