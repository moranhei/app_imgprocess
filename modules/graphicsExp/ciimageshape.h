#ifndef CIIMAGESHAPE_H
#define CIIMAGESHAPE_H

#include <QGraphicsItem>
#include "cishape.h"
#include "globalval.hpp"

namespace GraphicsExp {
class CIImageShape : public CIShape
{
public:
    CIImageShape(QPixmap *pixMap);
    //! 下述两个函数继承自基类，且必须重写，不然在实例化自定义类时会提示不能实例化抽象类
    //! 这是因为这两个函数在类的new过程中会被自动调用将图像显示，所以必须重写
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
    qreal scaleValue = 1.0;
    QPixmap pix;
    int zoomState;
    bool isMove;
    QPointF startPos;
};
}



#endif // CIIMAGESHAPE_H
