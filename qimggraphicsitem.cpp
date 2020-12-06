#include "qimggraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QPointF>
#include <QKeyEvent>
#include <QDebug>

QImgGraphicsItem::QImgGraphicsItem(QPixmap *pixMap)
{
    pix = *pixMap;
    scaleValue = 1;
    scaleDefault = 1;
    isMove = false;
}

QRectF QImgGraphicsItem::boundingRect() const
{
    //! 根据左上角点和宽高定义一个矩形
    return QRectF(-pix.width() / 2, -pix.height() / 2,
                  pix.width(), pix.height());
}

void QImgGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //! 左上角点，即其值是相对于scene坐标系，scene的中心点居中，故如果想让图像中心与scene中心点重合
    //! 则图像绘制的左上角起点为(-pix.width() / 2, -pix.height() / 2)
    painter->drawPixmap(-pix.width() / 2, -pix.height() / 2, pix);
}

void QImgGraphicsItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    //! 大于0表示滚轮往原理用户方向滚动，即放大图像
    if ((event->delta() > 0) && (scaleValue >= 50)) { //!< 最大放大到原图的50倍
        return;
    } else if ((event->delta() < 0) && (scaleValue <= scaleDefault)) {
        resetItemPos(); //!< 重置图片大小和位置，使其自适应控件窗口大小
    } else {
        qreal originScale = scaleValue;
        if (event->delta() > 0) { //!< 滚轮远离用户，即放大图像
            scaleValue *= 1.1;
            // this->setTransformOriginPoint(event->pos()); //!< 设置尺度变换中心（图元坐标系）
            setScale(scaleValue); //!< 该函数为当前类继承自QGraphicsItem类的函数，用于对图元的尺寸进行相关设置
            //! 下述函数等同于setPos(pos() + QPointF(dx, dy)).用于移动图元,实现以鼠标位置进行放大和缩小的效果
            //! 即先将图像以默认中心放大，然后将图像偏移指定像素值
            moveBy(-event->pos().x() * (originScale * 0.1), -event->pos().y() * (originScale * 0.1));

        } else {
            scaleValue *= 0.9;
            setScale(scaleValue);
            moveBy(event->pos().x() * (originScale * 0.1), event->pos().y() * (originScale * 0.1));
        }
    }
}

void QImgGraphicsItem::resetItemPos()
{
    scaleValue = scaleDefault; //!< 缩放比例回到一开始的自适应比例
    setScale(scaleDefault); //!< 缩放到一开始自适应大小
    setPos(0, 0); //!< 0,0以scene为坐标系
    qDebug() << u8"默认比例参数:" << scaleDefault;
}

void QImgGraphicsItem::setQGraphicsView(int widthView, int heightView)
{
    qreal tempWidth = widthView * 1.0 / pix.width();
    qreal tempHeight = heightView * 1.0 / pix.height();
    if (tempWidth > tempHeight) {
        scaleDefault = tempHeight;
    } else {
        scaleDefault = tempWidth;
    }
//    setScale(scaleDefault); //!< 默认是以图元的中心坐标（图元坐标系）进行尺度变换
    scaleValue = scaleDefault;
}

qreal QImgGraphicsItem::getScaleValue() const
{
    return scaleValue;
}

qreal QImgGraphicsItem::getScaleDefault() const
{
    return scaleDefault;
}
