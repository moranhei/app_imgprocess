#ifndef CIMAGEEDITOR_H
#define CIMAGEEDITOR_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>

#include "ciscene.h"
#include "cishape.h"

namespace Modules {
class CImageEditor : public QGraphicsView
{
public:
    CImageEditor();
    ~CImageEditor();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    CIScene *iScene;
    QPointF pointInItem;
    QRgb pixelValue;
    CIShape *shapeSelected;
    QImage image;
};
}
#endif // CIMAGEEDITOR_H
