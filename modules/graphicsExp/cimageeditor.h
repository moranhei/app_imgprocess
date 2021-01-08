#ifndef CIMAGEEDITOR_H
#define CIMAGEEDITOR_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>

#include "ciscene.h"
#include "cishape.h"
#include "ciimageshape.h"
#include "globalval.hpp"
#include "cirectshape.h"

namespace Modules {
class CImageEditor : public QGraphicsView
{
public:
    CImageEditor();
    ~CImageEditor();
    /**
     * @brief 加载图像
     * @param image:[in]输入图像
     */
    void updateImage(const QImage &image);
    /**
     * @brief 图像自适应窗口
     */
    void fitImage();
    /**
     * @brief 绘制矩形编辑框
     * @param pt1:[in]矩形左上角点坐标
     * @param pt2:[in]矩形右上角点坐标
     * @param pt3:[in]矩形右下角点坐标
     * @param pt4:[in]矩形左下角点坐标
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     */
    void addRectShape(const QPointF &pt1 = QPointF(0, 0), const QPointF &pt2 = QPointF(100, 0),
                      const QPointF &pt3 = QPointF(100, 100), const QPointF &pt4 = QPointF(0, 100),
                      const QColor &penColor = Qt::green, qreal penWidth = 1.0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    CIScene *iScene;
    QPointF pointInItem;
    QRgb pixelValue;
    CIRectShape *shapeSelected;
    QImage inputImage;
    CIImageShape *imageShape;
    QList<QGraphicsItem *> iShapeList; //!< 编辑框集合
    QList<qint32> idList; //!< 编辑框ID集合
};
}
#endif // CIMAGEEDITOR_H
