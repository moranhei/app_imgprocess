#include "qimggraphicsview.h"

#include <QMouseEvent>

QImgGraphicsView::QImgGraphicsView(QWidget *parent)
{

}

void QImgGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos(); //QGraphicsView的坐标
    emit mouseMovePoint(point); //释放信号
    QGraphicsView::mouseMoveEvent(event);
}

void QImgGraphicsView::keyPressEvent(QKeyEvent *event)
{
    //! 按键事件
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}
