#ifndef CIRECTSHAPE_H
#define CIRECTSHAPE_H

#include <QGraphicsItem>

#include "cishape.h"

namespace Modules {
class CIRectShape : public QGraphicsItem
{
public:
    CIRectShape(const QPointF &pt1, const QPointF &pt2, const QPointF &pt3, const QPointF &pt4, const QColor &penColor, qreal penWidth);

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
    void paintShape(const QPointF &point); //!< 形状绘制
    void scaleShape(const QPointF &mousePoint); //!< 形状缩放
    void moveShape(const QPointF &mousePoint); //!< 形状移动

    bool isPainterPressed; //!< 是否正在绘制
    bool isMovePressed; //!< 是否正在被移动
    bool isScalePressed; //!< 是否正在缩放大小
    //! 0:topLeft; 1:topMiddle; 2:topRight; 3:rightMiddlem; 4:bottomRight;
    //! 5:bottomMiddle; 6:bottomLeft; 7:leftMiddle; 8:center;
    QVector<QPoint> pointCoordinates = QVector<QPoint>(9, QPoint(0, 0)); //! 对任意形状按照顺时针定义了9个点位置
    EmDirection emCurDirection;
    myShape shapeType;
    QPen pen = QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brush = QBrush(QColor(0, 165, 240, 120));
//    QBrush brush = QBrush(QColor(0, 0, 200, 120));
    QFont font = QFont("Times", 10, QFont::Bold);
    QPointF paintStartPoint;
    QPointF moveStartPoint;
    QRectF rectBase; //!< 矩形数据格式，通常的矩形，正方形，椭圆，圆均可以由该数据生成

};
}
#endif // CIRECTSHAPE_H
