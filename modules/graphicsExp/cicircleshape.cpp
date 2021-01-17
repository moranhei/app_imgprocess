#include "cicircleshape.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

using namespace GraphicsExp;

CICircleShape::CICircleShape(const QPointF &cpt, qreal r, const QColor &penColor, qreal penWidth)
{
    setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    setAcceptDrops(true);
    isMovePressed = false;
    isScalePressed = false;
    emCurDirection = EmDirection::DIR_NONE;
    rectBase = QRectF(QPointF(cpt.x() - r, cpt.y() - r), QPointF(cpt.x() + r, cpt.y() + r));
}

void CICircleShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //! 辅助线采用白色虚线；其它全部采用绿色，中间填充采用半透明蓝色
    QString strPoint = QString("X:%0, Y:%1").arg(rectBase.center().x()).arg(rectBase.center().y());
    QString strRadius = QString("R:%0").arg(rectBase.width() / 2);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(rectBase.topLeft().x(), rectBase.topLeft().y() - 5, strRadius);
    painter->drawText(rectBase.topLeft().x(), rectBase.topLeft().y() - 20, strPoint);

    painter->drawEllipse(rectBase);

    if (rectBase.width() != 0 && rectBase.height() != 0) {
        //! 辅助线形状特征
        QPen penAux = QPen(Qt::white, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(penAux);
        //! 绘制辅助线
        painter->drawLine(rectBase.topLeft().x() + rectBase.width() / 2, rectBase.topLeft().y() + EDGE_WIDTH, \
                          rectBase.bottomRight().x() - rectBase.width() / 2, rectBase.bottomRight().y());
        painter->drawLine(rectBase.topLeft().x() + EDGE_WIDTH, rectBase.topLeft().y() + rectBase.height() / 2, \
                          rectBase.bottomRight().x(), rectBase.bottomRight().y() - rectBase.height() / 2);
        QBrush brushPoint = QBrush(QColor(0, 255, 0, 255));
        painter->setBrush(brushPoint);
        painter->setPen(pen);
        //! 绘制角点
        painter->drawRect(rectBase.topLeft().x(), rectBase.topLeft().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //左边中心点
        painter->drawRect(rectBase.topLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.topLeft().y(), POINT_WIDTH, POINT_HEIGHT);  //顶部中心
        painter->drawRect(rectBase.topLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.topLeft().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //中心点
        painter->drawRect(rectBase.bottomLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //底部中心点
        painter->drawRect(rectBase.topRight().x() - POINT_WIDTH / 2, rectBase.topRight().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //右边中心点
    }
}

QRectF CICircleShape::boundingRect() const
{
    return rectBase;
}

void CICircleShape::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setSelected(true);
        EmDirection dir = mouseDirection(event->pos());
        if (dir == DIR_MIDDLE) {
            //! 鼠标在图形内部
            this->setCursor(Qt::ClosedHandCursor);
            moveStartPoint.setX(event->pos().x());
            moveStartPoint.setY(event->pos().y());
            isMovePressed = true;
        } else if (dir == DIR_NONE) {
            //! 鼠标在图形外部
            this->setCursor(Qt::ArrowCursor);
            paintStartPoint.setX(event->pos().x());
            paintStartPoint.setY(event->pos().y());
        } else {
            moveStartPoint.setX(event->pos().x());
            moveStartPoint.setY(event->pos().y());
            isScalePressed = true;
            emCurDirection = dir;
        }
    }
    update();
}

void CICircleShape::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        //! 原来困扰我将近一个月的问题，居然是加上这一句程序就可以了，晕~~
        prepareGeometryChange();
        if (isMovePressed) {
            moveShape(event->pos());
        } else if (isScalePressed) {
            scaleShape(event->pos());
        }
        update();
        return;
    }

    EmDirection dir = mouseDirection(event->pos());
    if (dir == DIR_NONE)
        this->setCursor(Qt::ArrowCursor);
    else if (dir == DIR_MIDDLE)
        this->setCursor((Qt::OpenHandCursor));
}

void CICircleShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (rectBase.contains(event->pos())) {
        if (isMovePressed)
            this->setCursor(Qt::OpenHandCursor);
        else
            this->setCursor(Qt::ArrowCursor);
    }

    paintStartPoint = QPoint();
    isMovePressed = false;
    isScalePressed = false;
}

void CICircleShape::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        rectBase = QRect(0, 0, 0, 0);
        update();
    }
}

int CICircleShape::type() const
{
    return Type;
}

EmDirection CICircleShape::mouseDirection(const QPointF &point)
{
    int mouseX = point.x();
    int mouseY = point.y();

    QPointF shapeTopLeft = rectBase.topLeft();
    QPointF shapeBottomRight = rectBase.bottomRight();
    float radius = rectBase.width() / 2;
    EmDirection dir = DIR_NONE;

    if (mouseX >= shapeBottomRight.x() - EDGPADDING && mouseX <= shapeBottomRight.x() + EDGPADDING && \
            mouseY >= shapeTopLeft.y() + radius - EDGPADDING && mouseY <= shapeBottomRight.y() - radius + EDGPADDING) {
        //!< 右边
        this->setCursor(Qt::SizeHorCursor);
        dir = DIR_RIGHT;
    } else if (mouseX >= shapeTopLeft.x() + radius - EDGPADDING && mouseX <= shapeBottomRight.x() - radius + EDGPADDING && \
               mouseY <= shapeTopLeft.y() + EDGPADDING && mouseY >= shapeTopLeft.y() - EDGPADDING) {
        //!< 上边
        this->setCursor(Qt::SizeVerCursor);
        dir = DIR_TOP;
    } else if (mouseX >= shapeTopLeft.x() + radius - EDGPADDING && mouseX <= shapeBottomRight.x() - radius + EDGPADDING && \
               mouseY >= shapeBottomRight.y() - EDGPADDING && mouseY <= shapeBottomRight.y() + EDGPADDING) {
        //!< 下边
        this->setCursor(Qt::SizeVerCursor);
        dir = DIR_BOTTOM;
    } else if (mouseX <= shapeTopLeft.x() + EDGPADDING && mouseX >= shapeTopLeft.x() - EDGPADDING && \
               mouseY >= shapeTopLeft.y() + radius - EDGPADDING && mouseY <= shapeBottomRight.y() - radius + EDGPADDING) {
        //!< 左边
        this->setCursor(Qt::SizeHorCursor);
        dir = DIR_LEFT;
    } else if (rectBase.contains(point)) {
        //!< 中间
        dir = DIR_MIDDLE;
    } else {
        dir = DIR_NONE;
    }
    return dir;
}

void CICircleShape::scaleShape(const QPointF &mousePoint)
{
    QRectF newRect(rectBase.topLeft(), rectBase.bottomRight());
    int width = mousePoint.x() - moveStartPoint.x();   //移动的宽度
    int height = mousePoint.y() - moveStartPoint.y();  //移动的高度

    //根据当前的缩放状态来改变矩形的位置大小信息
    switch (emCurDirection) {
    case DIR_LEFT:
        newRect.setLeft(rectBase.left() + width);
        newRect.setTop(rectBase.top() + width);
        newRect.setRight(rectBase.right() - width);
        newRect.setBottom(rectBase.bottom() - width);
        break;
    case DIR_RIGHT:
        newRect.setLeft(rectBase.left() - width);
        newRect.setTop(rectBase.top() - width);
        newRect.setRight(rectBase.right() + width);
        newRect.setBottom(rectBase.bottom() + width);
        break;
    case DIR_TOP:
        newRect.setLeft(rectBase.left() + height);
        newRect.setTop(rectBase.top() + height);
        newRect.setRight(rectBase.right() - height);
        newRect.setBottom(rectBase.bottom() - height);
        break;
    case DIR_BOTTOM:
        newRect.setLeft(rectBase.left() - height);
        newRect.setTop(rectBase.top() - height);
        newRect.setRight(rectBase.right() + height);
        newRect.setBottom(rectBase.bottom() + height);
        break;
    }

    if (newRect.width() < MIN_WIDTH || newRect.height() < MIN_HEIGHT) {
        //缩放的大小限制
        return;
    }

    rectBase = newRect;
    moveStartPoint = mousePoint;  //更新鼠标的起始位置
}

void CICircleShape::moveShape(const QPointF &mousePoint)
{
    this->setCursor(Qt::ClosedHandCursor);

    int width = mousePoint.x() - moveStartPoint.x();
    int height = mousePoint.y() - moveStartPoint.y();

    QRectF ret;
    ret.setX(rectBase.x() + width);
    ret.setY(rectBase.y() + height);
    ret.setSize(rectBase.size());
    rectBase = ret;
    moveStartPoint = mousePoint;
}
