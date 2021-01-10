#ifndef CIFEATURE_H
#define CIFEATURE_H

#include <QPen>
#include <QGraphicsItem>
#include <QFont>
#include <QGraphicsSceneMouseEvent>

#include "globalval.hpp"

namespace Modules {

class CIFeature : public QGraphicsItem
{
public:
    //! 对于大多数形状利用矩形数据都可以绘制，但是多边形不可，建议此处参数采用
    explicit CIFeature(const QVector<QPointF> &pts = QVector<QPointF>());
    explicit CIFeature(const QString &str, const QPointF &pt = QPointF());


protected:
    //! 该函数对Item进行绘制，且是不断的循环执行的
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //! 该函数在类的初始化时会被自动执行，其定义了Item所在的范围，该范围内会检测鼠标和按键的操作
    QRectF boundingRect() const;

public:
    void setShapeType(myShape inShapeType);
    void setPenWidth(qreal penWidth);
    void setPenColor(QColor penColor);
    void setTextFont(QFont textFont);

private:
    QRectF rectBase; //!< 矩形数据格式，通常的矩形，正方形，椭圆，圆均可以由该数据生成
    QVector<QPointF> points;
    QString textString;
    QPointF textCenter;
    myShape shapeType;
    QPen pen = QPen(Qt::blue, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QFont font = QFont("Times", 10, QFont::Bold);
};
}

#endif // CIFEATURE_H
