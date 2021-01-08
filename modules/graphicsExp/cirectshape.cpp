#include "cirectshape.h"

#include <QDebug>
#include <QPainter>
#include <QKeyEvent>

using namespace Modules;

CIRectShape::CIRectShape(const QPointF &pt1, const QPointF &pt2, const QPointF &pt3, const QPointF &pt4, const QColor &penColor, qreal penWidth)
{
    Q_UNUSED(pt2);
    setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
//    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setAcceptDrops(true);
//    setFlag(ItemIsFocusable, true);
//    setFlag(ItemIsMovable, true);
////    setFlag(ItemIsSelectable, true);
//    setAcceptedMouseButtons(Qt::LeftButton);
//    setFlag(QGraphicsItem::ItemIsSelectable);//必须加上这句，否则item无法获取到鼠标事件
//    setFlag(ItemSendsGeometryChanges, true);
//    setFlag(ItemSendsScenePositionChanges, true);
    isPainterPressed = false;
    isMovePressed = false;
    isScalePressed = false;
    rectBase = QRect(0, 0, 0, 0);
    emCurDirection = EmDirection::DIR_NONE;
    rectBase = QRectF(pt1, pt3);
}

void CIRectShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //! 辅助线采用白色虚线；其它全部采用绿色，中间填充采用半透明蓝色
    QString strPoint = QString("X:%0, Y:%1").arg(rectBase.x()).arg(rectBase.y());
    QString strSize = QString("W:%0, H:%1").arg(rectBase.width()).arg(rectBase.height());
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(rectBase.topLeft().x(), rectBase.topLeft().y() - 5, strSize);
    painter->drawText(rectBase.topLeft().x(), rectBase.topLeft().y() - 20, strPoint);

    painter->drawRect(rectBase);

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
        painter->drawRect(rectBase.topLeft().x(), rectBase.topLeft().y(), POINT_WIDTH, POINT_HEIGHT); //左上角
        painter->drawRect(rectBase.topLeft().x(), rectBase.topLeft().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //左边中心点
        painter->drawRect(rectBase.bottomLeft().x(), rectBase.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //左下角
        painter->drawRect(rectBase.topLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.topLeft().y(), POINT_WIDTH, POINT_HEIGHT);  //顶部中心
        painter->drawRect(rectBase.topLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.topLeft().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //中心点
        painter->drawRect(rectBase.bottomLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //底部中心点
        painter->drawRect(rectBase.topRight().x() - POINT_WIDTH, rectBase.topRight().y(), POINT_WIDTH, POINT_HEIGHT); //右上角
        painter->drawRect(rectBase.topRight().x() - POINT_WIDTH / 2, rectBase.topRight().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //右边中心点
        painter->drawRect(rectBase.bottomRight().x() - POINT_WIDTH, rectBase.bottomRight().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //右下角点
    }
//    qDebug() << u8"编辑框尺寸:" << rectBase;
//    this->acceptDrops();
//    this->setSelected(true);
}

QRectF CIRectShape::boundingRect() const
{
//    return this->boundingRect();
//    qDebug() << u8"rectBase尺寸:" << rectBase;
//    QRectF ret = QRectF(-9999, -9999, 99999, 99999);
//    return ret;
    return rectBase;
}

void CIRectShape::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        setSelected(true);
        EmDirection dir = mouseDirection(event->pos());
//        qCritical() << u8"当前鼠标的位置:" << event->pos();
        if (dir == DIR_MIDDLE) {
            //! 鼠标在图形内部
            this->setCursor(Qt::ClosedHandCursor);
            moveStartPoint.setX(event->pos().x());
            moveStartPoint.setY(event->pos().y());
            isMovePressed = true;
        } else if (dir == DIR_NONE) {
            //! 鼠标在图形外部
            this->setCursor(Qt::ArrowCursor);
            isPainterPressed = true;
            paintStartPoint.setX(event->pos().x());
            paintStartPoint.setY(event->pos().y());

            //! 经过验证，下述三个值相等，即Item的原点与Scene的重合
            QPointF itemPos_1, itemPos_2;
            itemPos_1 = mapToItem(this, event->pos().x(), event->pos().y()); //!< 将参数2和3定义的坐标转换到this对应的坐标系中，实现两个item之间点位置的互相转换
            itemPos_2 = mapFromScene(event->pos().x(), event->pos().y());    //!< 将当前Item对应的点转换到其所在的Scene的坐标系中
//            qDebug() << u8"QGraphicsSceneMouseEvent:" << event->pos().x() << event->pos().y();
//            qDebug() << u8"ItemPos_1:" << itemPos_1.x() << itemPos_1.y();
//            qDebug() << u8"ItemPos_2:" << itemPos_2.x() << itemPos_2.y();
        } else {
            moveStartPoint.setX(event->pos().x());
            moveStartPoint.setY(event->pos().y());
            isScalePressed = true;
            emCurDirection = dir;
        }
    }
    update();
}

void CIRectShape::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        //! 原来困扰我将近一个月的问题，居然是加上这一句程序就可以了，晕~~
        prepareGeometryChange();
        if (isPainterPressed) {
            paintShape(event->pos());
        } else if (isMovePressed) {
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

void CIRectShape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (rectBase.contains(event->pos())) {
        if (isMovePressed)
            this->setCursor(Qt::OpenHandCursor);
        else
            this->setCursor(Qt::ArrowCursor);
    }

    paintStartPoint = QPoint();
    isMovePressed = false;
    isPainterPressed = false;
    isScalePressed = false;
}

void CIRectShape::keyPressEvent(QKeyEvent *event)
{
//    prepareGeometryChange();
    if (event->key() == Qt::Key_Delete) {
        rectBase = QRect(0, 0, 0, 0);
        update();
    }
}

int CIRectShape::type() const
{
    return Type;
}

EmDirection CIRectShape::mouseDirection(const QPointF &point)
{
    //    QRectF rectBase(50, 50, 200, 200);
    int mouseX = point.x();
    int mouseY = point.y();

    QPointF shapeTopLeft = rectBase.topLeft();
    QPointF shapeBottomRight = rectBase.bottomRight();
    EmDirection dir = DIR_NONE;
//        qDebug() << u8"相关关键位置值:" << point << shapeTopLeft << shapeBottomRight;

    if (mouseX <= shapeTopLeft.x() + CORPADDING && mouseX >= shapeTopLeft.x() && \
            mouseY <= shapeTopLeft.y() + CORPADDING && mouseY >= shapeTopLeft.y()) {
        //!< 当鼠标靠近左上角点，且在区域内部，则变换鼠标形状
        this->setCursor(Qt::SizeFDiagCursor);
        dir = DIR_TOPLEFT;
    } else if (mouseX >= shapeBottomRight.x() - CORPADDING && mouseX <= shapeBottomRight.x() && \
               mouseY <= shapeTopLeft.y() + CORPADDING && mouseY >= shapeTopLeft.y()) {
        //!< 右上角点
        this->setCursor(Qt::SizeBDiagCursor);
        dir = DIR_TOPRIGHT;
    } else if (mouseX <= shapeTopLeft.x() + CORPADDING && mouseX >= shapeTopLeft.x() && \
               mouseY >= shapeBottomRight.y() - CORPADDING && mouseY <= shapeBottomRight.y()) {
        //!< 左下角点
        this->setCursor(Qt::SizeBDiagCursor);
        dir = DIR_BOTTOMLEFT;
    } else if (mouseX >= shapeBottomRight.x() - CORPADDING && mouseX <= shapeBottomRight.x() && \
               mouseY >= shapeBottomRight.y() - CORPADDING && mouseY <= shapeBottomRight.y()) {
        //!< 右下角点
        this->setCursor(Qt::SizeFDiagCursor);
        dir = DIR_BOTTOMRIGHT;
    } else if (mouseX >= shapeBottomRight.x() - EDGPADDING && mouseX <= shapeBottomRight.x() && \
               mouseY >= shapeTopLeft.y() && mouseY <= shapeBottomRight.y()) {
        //!< 右边
        this->setCursor(Qt::SizeHorCursor);
        dir = DIR_RIGHT;
    } else if (mouseX >= shapeTopLeft.x() && mouseX <= shapeBottomRight.x() && \
               mouseY <= shapeTopLeft.y() + EDGPADDING && mouseY >= shapeTopLeft.y()) {
        //!< 上边
        this->setCursor(Qt::SizeVerCursor);
        dir = DIR_TOP;
    } else if (mouseX >= shapeTopLeft.x() && mouseX <= shapeBottomRight.x() && \
               mouseY >= shapeBottomRight.y() - EDGPADDING && mouseY <= shapeBottomRight.y()) {
        //!< 下边
        this->setCursor(Qt::SizeVerCursor);
        dir = DIR_BOTTOM;
    } else if (mouseX <= shapeTopLeft.x() + EDGPADDING && mouseX >= shapeTopLeft.x() && \
               mouseY >= shapeTopLeft.y() && mouseY <= shapeBottomRight.y()) {
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

void CIRectShape::paintShape(const QPointF &point)
{
    this->setCursor(Qt::ArrowCursor);
    int width = point.x() - paintStartPoint.x(); //!< 相对于鼠标按下的起始点，当前鼠标移动的距离
    int height = point.y() - paintStartPoint.y();
    if (width < 0 && height < 0) {
        rectBase.setX(point.x());
        rectBase.setY(point.y());
    } else if (width < 0) {
        rectBase.setX(point.x());
        rectBase.setY(paintStartPoint.y());
    } else if (height < 0) {
        rectBase.setX(paintStartPoint.x());
        rectBase.setY(point.y());
    } else {
        rectBase.setX(paintStartPoint.x());
        rectBase.setY(paintStartPoint.y());
    }
    rectBase.setSize(QSize(abs(width), abs(height)));
}

void CIRectShape::scaleShape(const QPointF &mousePoint)
{
    QRectF newRect(rectBase.topLeft(), rectBase.bottomRight());
    int width = mousePoint.x() - moveStartPoint.x();   //移动的宽度
    int height = mousePoint.y() - moveStartPoint.y();  //移动的高度

    //根据当前的缩放状态来改变矩形的位置大小信息
    switch (emCurDirection) {
    case DIR_LEFT:
        newRect.setLeft(mousePoint.x());
        break;
    case DIR_RIGHT:
        newRect.setRight(mousePoint.x());
        break;
    case DIR_TOP:
        newRect.setTop(mousePoint.y());
        break;
    case DIR_BOTTOM:
        newRect.setBottom(mousePoint.y());
        break;
    case DIR_TOPLEFT:
        newRect.setTopLeft(mousePoint);
        break;
    case DIR_BOTTOMLEFT:
        newRect.setBottomLeft(mousePoint);
        break;
    case DIR_TOPRIGHT:
        newRect.setTopRight(mousePoint);
        break;
    case DIR_BOTTOMRIGHT:
        newRect.setBottomRight(mousePoint);
        break;
    }

    if (newRect.width() < MIN_WIDTH || newRect.height() < MIN_HEIGHT) {
        //缩放的大小限制
        return;
    }

    rectBase = newRect;
    moveStartPoint = mousePoint;  //更新鼠标的起始位置
}

void CIRectShape::moveShape(const QPointF &mousePoint)
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
