#include "ciscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QDebug>

using namespace GraphicsExp;

CIScene::CIScene()
{
//    clearFocus();
}

CIScene::~CIScene()
{

}

void CIScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void CIScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
//    qDebug() << this->selectedItems().size();
}

void CIScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}
