#ifndef CIMAGEEDITOR_H
#define CIMAGEEDITOR_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>

#include "ciscene.h"
#include "cishape.h"
#include "cifeature.h"
#include "ciimageshape.h"
#include "globalval.hpp"
#include "cirectshape.h"
#include "cicircleshape.h"

namespace GraphicsExp {
class CImageEditor : public QGraphicsView
{
public:
    CImageEditor(QWidget *parent = 0);
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
     * @brief 获取绘图区当前图像
     * @return 绘图区当前图像
     */
    QImage getImage() const;
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
    /**
     * @brief 绘制圆形编辑框
     * @param cpt:[in]圆形
     * @param r:[in]半径
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     */
    void addCircleShape(const QPointF &cpt = QPointF(50, 50), qreal r = 50,
                        const QColor &penColor = Qt::green, qreal penWidth = 1.0);
    /**
     * @brief 添加矩形特征
     * @param pt1:[in]矩形左上角点坐标，单位pixel
     * @param pt2:[in]矩形右下角点坐标，单位pixel
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     * @return 返回被添加的特征id
     */
    void addFeatureRect(const QPointF &pt1, const QPointF &pt2,
                        const QColor &penColor = Qt::blue, qreal penWidth = 1.0);
    /**
     * @brief 添加圆特征
     * @param cpt:[in]圆心坐标，单位pixel
     * @param r:[in]圆半径，单位pixel
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     * @return 返回被添加的特征id
     */
    void addFeatureCircle(const QPointF &cpt, qreal r,
                          const QColor &penColor = Qt::blue, qreal penWidth = 1.0);
    /**
     * @brief 添加多边形特征(同理可用于绘制直线，矩形等)
     * @param pts:[in]多边形按先后顺序各点坐标，单位pixel
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     * @return 返回被添加的特征id
     */
    void addFeaturePoly(const QVector<QPointF> &pts, const QColor &penColor = Qt::blue,
                        qreal penWidth = 1.0);
    /**
     * @brief 添加椭圆特征
     * @param pt1:[in]椭圆外接矩形左上角点坐标，单位pixel
     * @param pt2:[in]椭圆外接矩形右下角点坐标，单位pixel
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     * @return 返回被添加的特征id
     */
    void addFeatureEllipse(const QPointF &pt1, const QPointF &pt2,
                           const QColor &penColor = Qt::blue, qreal penWidth = 1.0);
    /**
     * @brief 添加文字
     * @param str:[in]文字信息
     * @param font:[in]文字字体
     * @param pt:[in]文字显示的位置(视场中的位置）
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     * @return
     */
    void addFeatureText(const QString &str,  const QPointF &pt = QPointF(0, 0),
                        const QFont &font = QFont("Times", 10, QFont::Bold),
                        const QColor &penColor = Qt::blue, qreal penWidth = 1.0);
    /**
     * @brief 添加点云特征
     * @param pts:[in]被添加的点云，单位pixel
     * @param penColor:[in]画笔颜色
     * @param penWidth:[in]画笔宽度
     * @param isAimPoint:[in]是否瞄准点, true:按照瞄准点形状绘制; false:按照普通点形状绘制
     * @return
     */
    void addFeaturePts(const QVector<QPointF> &pts, const QColor &penColor = Qt::blue,
                         qreal penWidth = 1.0, bool isAimPoint = false);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    CIScene *iScene;
    QImage inputImage;
    CIImageShape *imageShape;
    QPointF pointInItem;
    QRgb pixelValue;
    CIShape *shapeSelected;
    QList<CIShape *> iShapeList; //!< 编辑框集合
    QList<qint32> idList; //!< 编辑框ID集合
    CIFeature *featureSelected;
    QList<CIFeature *> iFeatureList; //!< 编辑框集合
};
}
#endif // CIMAGEEDITOR_H
