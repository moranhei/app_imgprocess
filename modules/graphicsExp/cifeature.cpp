#include "cifeature.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

using namespace GraphicsExp;

CIFeature::CIFeature(const QVector<QPointF> &pts)
{
    points = pts;
    if (pts.size() >= 2)
        rectBase = QRectF(pts.at(0), pts.at(1));
}

CIFeature::CIFeature(const QString &str, const QPointF &pt)
{
    textString = str;
    textCenter = pt;
}

void CIFeature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(pen);
    switch (shapeType) {
    case RectAngle:
        painter->drawRect(rectBase);
        break;
    case Ellipse:
        painter->drawEllipse(rectBase);
        break;
    case Polygon:
        painter->drawPolygon(QPolygonF(points), Qt::OddEvenFill);
        break;
    case Text:
        painter->setFont(font);
        painter->drawText(textCenter, textString);
    case Image:
//        painter->drawPixmap(&QPixmap::fromImage(qImg));
        break;
    case Points:
        painter->drawPoints(QPolygonF(points));
        break;
    default:
        break;
    }
}

QRectF CIFeature::boundingRect() const
{
    return rectBase;
}

void CIFeature::setShapeType(myShape inShapeType)
{
    shapeType = inShapeType;
}

void CIFeature::setPenWidth(qreal penWidth)
{
    pen.setWidth(penWidth);
}

void CIFeature::setPenColor(QColor penColor)
{
    pen.setColor(penColor);
}

void CIFeature::setTextFont(QFont textFont)
{
    font = textFont;
}
