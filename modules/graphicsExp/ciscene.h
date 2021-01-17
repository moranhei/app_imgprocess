#ifndef CISCENE_H
#define CISCENE_H

#include <QGraphicsScene>

#include "globalval.hpp"

namespace GraphicsExp {
class CIScene : public QGraphicsScene
{
public:
    CIScene();
    ~CIScene();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};
}

#endif // CISCENE_H
