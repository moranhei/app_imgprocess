#include "cimageeditor.h"

#include <QDebug>

using namespace Modules;

CImageEditor::CImageEditor()
{
    iScene = new CIScene();
}

CImageEditor::~CImageEditor()
{

}

void CImageEditor::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pointScene = mapToScene(event->pos());
    if (iScene->selectedItems().count() != 1) {
        qCritical() << u8"界面中Shape为空!";
        return; //! 没有选中的绘图项，或选中的多于1个
    }
    shapeSelected = dynamic_cast<CIShape *>(iScene->selectedItems().at(0));
    pointInItem = shapeSelected->mapFromScene(pointScene);
    pixelValue = image.pixel(pointInItem.toPoint());
}

void CImageEditor::mousePressEvent(QMouseEvent *event)
{

}

void CImageEditor::mouseReleaseEvent(QMouseEvent *event)
{

}

void CImageEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
        iScene->removeItem(shapeSelected);
    else if (event->key() == Qt::Key_Space)
        shapeSelected->setRotation(90 + shapeSelected->rotation());
    else if (event->key() == Qt::Key_PageUp) {
        if (shapeSelected->scale() >= 50)
            return;
        shapeSelected->setScale(1.1 * shapeSelected->scale());
    } else if (event->key() == Qt::Key_PageDown) {
        if (shapeSelected->scale() <= 0.00001)
            return;
        shapeSelected->setScale(0.9 * shapeSelected->scale());
    } else if (event->key() == Qt::Key_Left) {
        shapeSelected->setX(-1 + shapeSelected->x());
    } else if (event->key() == Qt::Key_Right) {
        shapeSelected->setX(1 + shapeSelected->x());
    } else if (event->key() == Qt::Key_Up) {
        shapeSelected->setY(-1 + shapeSelected->y());
    } else if (event->key() == Qt::Key_Down) {
        shapeSelected->setY(1 + shapeSelected->y());
    }
}
