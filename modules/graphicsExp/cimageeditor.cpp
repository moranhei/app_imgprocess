#include <QDebug>

#include "cimageeditor.h"


using namespace Modules;

CImageEditor::CImageEditor()
{
    iScene = new CIScene();
//    iScene->setSceneRect(QRectF(-400, -400, 800, 800));
    this->setScene(iScene);
    this->setBackgroundBrush(QBrush(QColor(0, 0, 96, 255)));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //!< 关闭水平和竖直的滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true); //!< 如果鼠标追踪关闭，则只有按下鼠标移动时，才会触发鼠标移动事件
    this->setCursor(Qt::CrossCursor); //!< 设置鼠标样式为十字架
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setSceneRect(QRectF(-this->width() / 2, -this->height() / 2, this->width(), this->height())); //!< 固定视图中场景大小，第一第二个参数为视图原点在场景坐标系中的位置
    this->setFocus(); //!< 将界面的焦点设置到当前view控件
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); //!< 避免Item在移动时发生拖影
//    this->setInteractive(true);
}

CImageEditor::~CImageEditor()
{
}

void CImageEditor::updateImage(const QImage &image)
{
    inputImage = image;
    iScene->clear();
    iShapeList.clear();
    idList.clear();
    imageShape = new CIImageShape(&QPixmap::fromImage(image));
    iScene->setSceneRect(-inputImage.width() / 2, -inputImage.height() / 2, inputImage.width(), inputImage.height());
    iScene->addItem(imageShape);
    iShapeList.append(imageShape);

//    CIShape *itemShape = new CIShape;
//    itemShape->setShapeType(Ellipse);
//    itemShape->setAcceptDrops(true);
//    itemShape->setFlag(QGraphicsItem::ItemIsMovable);
//    iScene->addItem(itemShape);
}

void CImageEditor::fitImage()
{
    if (inputImage.isNull()) {
        qCritical() << u8"界面图像为空!";
        return; //! 没有选中的绘图项，或选中的多于1个
    }
    qreal tempWidth = this->width() * 1.0 / inputImage.width();
    qreal tempHeight = this->height() * 1.0 / inputImage.height();
    if (tempWidth > tempHeight) {
        imageShape->setScale(tempHeight);
    } else {
        imageShape->setScale(tempWidth);
    }
    imageShape->setPos(0, 0);
}

void CImageEditor::addRectShape(const QPointF &pt1, const QPointF &pt2, const QPointF &pt3, const QPointF &pt4, const QColor &penColor, qreal penWidth)
{
    shapeSelected = new CIRectShape(pt1, pt2, pt3, pt4, Qt::green, 1.0);
    iShapeList.append(shapeSelected);
    idList.append(0);
    iScene->addItem(shapeSelected);
}

void CImageEditor::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pointScene = mapToScene(event->pos());
    if (inputImage.isNull()) {
        qCritical() << u8"界面图像为空!";
        return; //! 没有选中的绘图项，或选中的多于1个
    }
    pointInItem = imageShape->mapFromScene(pointScene);
    pixelValue = inputImage.pixel(pointInItem.toPoint());
    QGraphicsView::mouseMoveEvent(event);
}

void CImageEditor::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void CImageEditor::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void CImageEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
        iScene->removeItem(imageShape);
    else if (event->key() == Qt::Key_Space)
        imageShape->setRotation(90 + imageShape->rotation());
    else if (event->key() == Qt::Key_PageUp) {
        if (imageShape->scale() >= 50)
            return;
        imageShape->setScale(1.1 * imageShape->scale());
    } else if (event->key() == Qt::Key_PageDown) {
        if (imageShape->scale() <= 0.00001)
            return;
        imageShape->setScale(0.9 * imageShape->scale());
    } else if (event->key() == Qt::Key_Left) {
        imageShape->setX(-1 + imageShape->x());
    } else if (event->key() == Qt::Key_Right) {
        imageShape->setX(1 + imageShape->x());
    } else if (event->key() == Qt::Key_Up) {
        imageShape->setY(-1 + imageShape->y());
    } else if (event->key() == Qt::Key_Down) {
        imageShape->setY(1 + imageShape->y());
    }
}
