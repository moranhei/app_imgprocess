#include "cdrawlabel.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

using namespace Modules;

CDrawLabel::CDrawLabel(QWidget *parent) : QLabel(parent)
{
    this->initViewer();
}

CDrawLabel::~CDrawLabel()
{

}

void CDrawLabel::paintEvent(QPaintEvent *event)
{
//    QPainter painter;
//    QPolygon a;
//    QRect p;

//    painter.drawPolygon(a);
//    painter.drawEllipse(p);

    //! 辅助线采用白色虚线；其它全部采用绿色，中间填充采用半透明蓝色
    QLabel::paintEvent(event);
    QString strPoint = QString("X:%0, Y:%1").arg(rectBase.x()).arg(rectBase.y());
    QString strSize = QString("W:%0, H:%1").arg(rectBase.width()).arg(rectBase.height());

    QPainter painter;
    painter.begin(this);
    painter.setBrush(brush);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(rectBase.topLeft().x(), rectBase.topLeft().y() - 5, strSize);
    painter.drawText(rectBase.topLeft().x(), rectBase.topLeft().y() - 20, strPoint);
    painter.drawRect(rectBase);

    if (rectBase.width() != 0 && rectBase.height() != 0) {
        //! 辅助线形状特征
        QPen penAux = QPen(Qt::white, 2, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(penAux);
        //! 绘制辅助线
        painter.drawLine(rectBase.topLeft().x() + rectBase.width() / 2, rectBase.topLeft().y() + EDGE_WIDTH, \
                         rectBase.bottomRight().x() - rectBase.width() / 2, rectBase.bottomRight().y());
        painter.drawLine(rectBase.topLeft().x() + EDGE_WIDTH, rectBase.topLeft().y() + rectBase.height() / 2, \
                         rectBase.bottomRight().x(), rectBase.bottomRight().y() - rectBase.height() / 2);
        QBrush brushPoint = QBrush(QColor(0, 255, 0, 255));
        painter.setBrush(brushPoint);
        painter.setPen(pen);
        //! 绘制角点
        painter.drawRect(rectBase.topLeft().x(), rectBase.topLeft().y(), POINT_WIDTH, POINT_HEIGHT); //左上角
        painter.drawRect(rectBase.topLeft().x(), rectBase.topLeft().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //左边中心点
        painter.drawRect(rectBase.bottomLeft().x(), rectBase.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //左下角
        painter.drawRect(rectBase.topLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.topLeft().y(), POINT_WIDTH, POINT_HEIGHT);  //顶部中心
        painter.drawRect(rectBase.topLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.topLeft().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //中心点
        painter.drawRect(rectBase.bottomLeft().x() + rectBase.width() / 2 - POINT_WIDTH / 2, rectBase.bottomLeft().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //底部中心点
        painter.drawRect(rectBase.topRight().x() - POINT_WIDTH, rectBase.topRight().y(), POINT_WIDTH, POINT_HEIGHT); //右上角
        painter.drawRect(rectBase.topRight().x() - POINT_WIDTH / 2, rectBase.topRight().y() + rectBase.height() / 2 - POINT_WIDTH / 2, POINT_WIDTH, POINT_HEIGHT); //右边中心点
        painter.drawRect(rectBase.bottomRight().x() - POINT_WIDTH, rectBase.bottomRight().y() - POINT_WIDTH, POINT_WIDTH, POINT_HEIGHT); //右下角点
    }
    painter.end();
    qDebug() << rectBase;
}

void CDrawLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
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
            isPainterPressed = true;
            paintStartPoint.setX(event->pos().x());
            paintStartPoint.setY(event->pos().y());
        } else {
            moveStartPoint.setX(event->pos().x());
            moveStartPoint.setY(event->pos().y());
            isScalePressed = true;
            emCurDirection = dir;
        }
    }
}

void CDrawLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
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

void CDrawLabel::mouseReleaseEvent(QMouseEvent *event)
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

void CDrawLabel::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete) {
        rectBase = QRect(0, 0, 0, 0);
        update();
    }
}

void CDrawLabel::initViewer()
{
    isPainterPressed = false;
    isMovePressed = false;
    isScalePressed = false;
    rectBase = QRect(0, 0, 0, 0);
    emCurDirection = EmDirection::DIR_NONE;
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);
}

EmDirection CDrawLabel::mouseDirection(const QPoint &point)
{
    int mouseX = point.x();
    int mouseY = point.y();

    QPoint shapeTopLeft = rectBase.topLeft();
    QPoint shapeBottomRight = rectBase.bottomRight();
    EmDirection dir = DIR_NONE;

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

void CDrawLabel::paintShape(const QPoint &point)
{
    this->setCursor(Qt::ArrowCursor);
    int width = point.x() - paintStartPoint.x(); //!< 相对于鼠标按下的起始点，当前鼠标移动的距离
    int height = point.y() - paintStartPoint.y();
    switch (shapeType) {
    case RectAngle: {
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
        break;
    }
    default:
        break;
    }
}

void CDrawLabel::scaleShape(const QPoint &mousePoint)
{
    QRect newRect(rectBase.topLeft(), rectBase.bottomRight());
    int width = mousePoint.x() - moveStartPoint.x();   //移动的宽度
    int height = mousePoint.y() - moveStartPoint.y();  //移动的高度

    //根据当前的缩放状态来改变矩形的位置大小信息
    switch (emCurDirection)
    {
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

    if (newRect.width() < MIN_WIDTH || newRect.height() < MIN_HEIGHT)
    {
        //缩放的大小限制
        return;
    }

    rectBase = newRect;
    moveStartPoint = mousePoint;  //更新鼠标的起始位置
}

void CDrawLabel::moveShape(const QPoint &mousePoint)
{
    this->setCursor(Qt::ClosedHandCursor);

    int width = mousePoint.x() - moveStartPoint.x();
    int height = mousePoint.y() - moveStartPoint.y();

    QRect ret;
    ret.setX(rectBase.x() + width);
    ret.setY(rectBase.y() + height);
    ret.setSize(rectBase.size());
    rectBase = ret;
    moveStartPoint = mousePoint;
}

void CDrawLabel::setShapeType(myShape inShapeType)
{
    shapeType = inShapeType;
}
