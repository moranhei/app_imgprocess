#ifndef QIMGGRAPHICSITEM_H
#define QIMGGRAPHICSITEM_H

#include <QGraphicsItem>

class QImgGraphicsItem : public QGraphicsItem
{
public:
    QImgGraphicsItem(QPixmap *pixMap);
    //! 下述两个函数继承自基类，且必须重写，不然在实例化自定义类时会提示不能实例化抽象类
    //! 这是因为这两个函数在类的new过程中会被自动调用将图像显示，所以必须重写
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    void resetItemPos();  //!< 将图像重置到窗口居中并自适应大小
    void setQGraphicsView(int widthView, int heightView); //!< 获得图像自适应窗口大小时的图像缩放比例scaleDefault
    qreal getScaleValue() const;
    qreal getScaleDefault() const;

private:
    qreal scaleValue;
    qreal scaleDefault;
    QPixmap pix;
    int zoomState;
    bool isMove;
    QPointF startPos;
};

#endif // QIMGGRAPHICSITEM_H
