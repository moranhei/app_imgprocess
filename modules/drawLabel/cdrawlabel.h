#ifndef CDRAWLABEL_H
#define CDRAWLABEL_H

#include <QLabel>
#include <QPen>

namespace Modules {

typedef enum myShape {
    Pen,
    Line,
    RectAngle,
    Square,
    Ellipse,
    Circle,
    Polygon
}myShape;

enum EmDirection {
    DIR_TOP,
    DIR_BOTTOM,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_TOPLEFT,
    DIR_BOTTOMLEFT,
    DIR_TOPRIGHT,
    DIR_BOTTOMRIGHT,
    DIR_MIDDLE,
    DIR_NONE
};

#define EDGPADDING       5        //四周边缘可拉伸宽度(即鼠标在该范围内才发生变化)
#define CORPADDING       6        //四角可拉伸宽度(即鼠标在该范围内才发生变化)

#define MIN_WIDTH        5        //可拉伸的最小宽度
#define MIN_HEIGHT       5        //可拉伸的最小高度

#define POINT_WIDTH      6        //边缘9点的宽度
#define POINT_HEIGHT     6        //边缘9点的高度

#define EDGE_WIDTH       3        //边框的宽度
#define MIDDLELINE_WIDTH 2        //辅助线的宽度

#define DRAW_TEN_POINT            //绘制十个点
#define DRAW_SUB_LINE             //绘制辅助线

class CDrawLabel : public QLabel
{
    Q_OBJECT
public:
    CDrawLabel(QWidget *parent = nullptr);
    ~CDrawLabel();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    void initViewer();
    EmDirection mouseDirection(const QPoint &point);
    void paintShape(const QPoint &point); //!< 形状绘制
    void scaleShape(const QPoint &mousePoint); //!< 形状缩放
    void moveShape(const QPoint &mousePoint); //!< 形状移动


    bool isPainterPressed; //!< 是否正在绘制
    bool isMovePressed; //!< 是否正在被移动
    bool isScalePressed; //!< 是否正在缩放大小
    //! 0:topLeft; 1:topMiddle; 2:topRight; 3:rightMiddlem; 4:bottomRight;
    //! 5:bottomMiddle; 6:bottomLeft; 7:leftMiddle; 8:center;
    QVector<QPoint> pointCoordinates = QVector<QPoint>(9, QPoint(0, 0)); //! 对任意形状按照顺时针定义了9个点位置
    EmDirection emCurDirection;
    myShape shapeType;
    QPen pen = QPen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QBrush brush = QBrush(QColor(0, 0, 200, 120));
    QFont font = QFont("Times", 10, QFont::Bold);
    QPoint paintStartPoint;
    QPoint moveStartPoint;
    QRect rectBase; //!< 矩形数据格式，通常的矩形，正方形，椭圆，圆均可以由该数据生成

public:
//    void setPen(QPen *inPen) {pen = inPen;}
//    void setBrush(QPen *inBrush) {brush = inBrush;}
//    void setFont(QPen *inFont) {font = inFont;}
    void setShapeType(myShape inShapeType);
};
}
#endif // CDRAWLABEL_H
