#ifndef GLOBALVAL_HPP
#define GLOBALVAL_HPP

namespace Modules {

typedef enum myShape {
    Pen,
    Line,
    RectAngle,
    Square,
    Ellipse,
    Circle,
    Polygon,
    Image,
    Text
};

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

}


#endif // GLOBALVAL_HPP
