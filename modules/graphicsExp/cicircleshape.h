﻿#ifndef CICIRCLESHAPE_H
#define CICIRCLESHAPE_H

#include "cishape.h"

namespace Modules {
class CICircleShape : public CIShape
{
public:
    CICircleShape(const QPointF &cpt = QPointF(50, 50), qreal r = 50,
                  const QColor &penColor = Qt::green, qreal penWidth = 1.0);
protected:
    //! 该函数对Item进行绘制，且是不断的循环执行的
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //! 该函数在类的初始化时会被自动执行，其定义了Item所在的范围，该范围内会检测鼠标和按键的操作
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    int type() const;
private:
    EmDirection mouseDirection(const QPointF &point);
    void scaleShape(const QPointF &mousePoint); //!< 形状缩放
    void moveShape(const QPointF &mousePoint); //!< 形状移动

    bool isMovePressed; //!< 是否正在被移动
    bool isScalePressed; //!< 是否正在缩放大小
    EmDirection emCurDirection;
    myShape shapeType;
    QPen pen = QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brush = QBrush(QColor(0, 165, 240, 120));
    QFont font = QFont("Times", 10, QFont::Bold);
    QPointF paintStartPoint;
    QPointF moveStartPoint;
    QRectF rectBase; //!< 矩形数据格式，通常的矩形，正方形，椭圆，圆均可以由该数据生成
};
}
#endif // CICIRCLESHAPE_H
